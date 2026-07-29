/*
        Sup? Today's CLI Fuckery is man clone...since I've been using it since I've started coding and now I wanna 
        pay my respects to it

        Thought about calling it 'boy' since yk...man is a grown-ass one and mine is just a clone but calling it 
        my man would be funnier like 'tell me what setvbuf does my man' like a stoner

        and I won't add flags for man pages this time I'll just display the man pages in man-db or something (and I just did...)


        and for reference this is how I replicate man x on bash zcat signal.2.gz | groff -Tutf8 -mandoc | less -R

        I realized something...I am fucking too bad at parsing CLI arguments how can I improve that skill is that even a skill? 
        Doesn't chage the fact that I am bad it but a question it is
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>

#define MAX_PATHS       64
#define MAX_PATH_LEN    512
#define MAX_SECTIONS    32

static const char *default_sections[] = {
    "1", "n", "l", "8", "3", "0", "2", "3type", "5", "4", "9", "6", "7", NULL
};


static void build_manpath(void);
static char *man_paths[MAX_PATHS];
static int   path_count = 0;

static int run_pipeline(const char *page_path, const char *compressor);

static char *find_manpage(const char *name, const char *section, const char **compressor);


int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [section] name\n", argv[0]);
        fprintf(stderr, "   or: %s name.section\n", argv[0]);
        return(13);
    }

    const char *name = NULL;
    const char *section = NULL;

    if (argc == 2) {
        char *dot = strrchr(argv[1], '.');
        if (dot && dot != argv[1] && *(dot+1)) {

            int looks_like_section = 1;
            for (char *p = dot+1; *p; p++) {
                if (!(*p >= '0' && *p <= '9') && *p != 'n' && *p != 'l') {
                    looks_like_section = 0;
                    break;
                }
            }
            if (looks_like_section) {
                *dot = '\0';
                name = argv[1];
                section = dot + 1;
            } else {
                name = argv[1];
            }
        } else {
            name = argv[1];
        }
    } else {
        /* classic "man 2 signal" style */
        section = argv[1];
        name    = argv[2];
    }

    build_manpath();

    if (path_count == 0) {
        fprintf(stderr, "No man paths found. Your system is weird as fuck.\n");
        return(-13);
    }

    const char *compressor = NULL;
    char *page = find_manpage(name, section, &compressor);

    if (!page) {
        fprintf(stderr, "No manual entry for %s", name);
        if (section) fprintf(stderr, " in section %s", section);
        fprintf(stderr, "\n");
        return(-13);
    }



    int rc = run_pipeline(page, compressor);
    free(page);

    for (int i = 0; i < path_count; i++)
    {
        free(man_paths[i]);
        man_paths[i] = NULL;
    }
    return(rc);
}






static int path_exists(const char *p)
{
    struct stat st;
    return(stat(p, &st) == 0 && S_ISDIR(st.st_mode));
}

static void add_path(const char *p)
{
    if (!p || !*p || path_count >= MAX_PATHS){ return; }
    if (!path_exists(p)){ return; }

    /* avoid duplicates */
    for (int i = 0; i < path_count; i++)
        if (strcmp(man_paths[i], p) == 0){ return; }

    man_paths[path_count++] = strdup(p);
}

static void parse_config(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f){ return; }

    char line[1024];
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#' || *p == '\n' || *p == '\0'){ continue; }

        char *tok = strtok(p, " \t\n");
        if (!tok){ continue; }

        if (strcmp(tok, "MANDATORY_MANPATH") == 0) {
            tok = strtok(NULL, " \t\n");
            if (tok){ add_path(tok); }
        }    
    }

    fclose(f);
}

static void build_manpath(void)
{

    const char *env = getenv("MANPATH");
    if (env && *env) {
        char *copy = strdup(env);
        char *tok = strtok(copy, ":");
        while (tok) {
            if (*tok) add_path(tok);
            tok = strtok(NULL, ":");
        }

        free(copy);
        copy = NULL;
        if (path_count > 0){ return; }            /* $MANPATH wins */
    }


    parse_config("/etc/manpath.config");
    parse_config("/etc/man_db.conf");
    parse_config("/usr/local/etc/man_db.conf");

    if (path_count == 0) {
        add_path("/usr/share/man");
        add_path("/usr/local/share/man");
        add_path("/usr/man");
        add_path("/usr/local/man");
    }
}


static int file_exists(const char *path)
{
    struct stat st;
    return (stat(path, &st) == 0 && S_ISREG(st.st_mode));
}


static char *find_manpage(const char *name, const char *section,
                          const char **compressor)
{
    *compressor = NULL;
    char candidate[MAX_PATH_LEN];

    const char *sections[MAX_SECTIONS];
    int nsec = 0;

    if (section && *section) {
        sections[nsec++] = section;
    } else {
        for (int i = 0; default_sections[i]; i++)
            sections[nsec++] = default_sections[i];
    }
    sections[nsec] = NULL;

    const char *exts[] = { ".gz", ".xz", ".bz2", "", NULL };
    const char *cmds[] = { "zcat", "xzcat", "bzcat", NULL, NULL };

    for (int p = 0; p < path_count; p++) {
        for (int s = 0; sections[s]; s++) {
            for (int e = 0; exts[e]; e++) {
                snprintf(candidate, sizeof candidate,
                         "%s/man%s/%s.%s%s",
                         man_paths[p], sections[s], name, sections[s], exts[e]);

                if (file_exists(candidate)) {
                    *compressor = cmds[e];
                    return(strdup(candidate));
                }
            }
        }
    }
    return(NULL);
}

static int run_pipeline(const char *page_path, const char *compressor)
{
    int zcat_groff[2];
    int groff_less[2];

    if (pipe(zcat_groff) == -1 || pipe(groff_less) == -1) {
        perror("pipe");
        return(-13);
    }


    pid_t pid1 = fork();
    if (pid1 == -1) { perror("fork"); return(-13); }

    if (pid1 == 0) {
        dup2(zcat_groff[1], STDOUT_FILENO);
        close(zcat_groff[0]);
        close(zcat_groff[1]);
        close(groff_less[0]);
        close(groff_less[1]);

        if (compressor) {
            execlp(compressor, compressor, page_path, (char *)NULL);
        } else {
            execlp("cat", "cat", page_path, (char *)NULL);
        }
        perror("exec decompressor");
        _exit(127);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        kill(pid1, SIGTERM);
        waitpid(pid1, NULL, 0);
        return(-13);
    }

    if (pid2 == 0) {
        dup2(zcat_groff[0], STDIN_FILENO);
        dup2(groff_less[1], STDOUT_FILENO);

        close(zcat_groff[0]);
        close(zcat_groff[1]);
        close(groff_less[0]);
        close(groff_less[1]);

        execlp("groff", "groff", "-Tutf8", "-mandoc", (char *)NULL);
        perror("exec groff");
        _exit(127);
    }


    pid_t pid3 = fork();
    if (pid3 == -1) {
        kill(pid1, SIGTERM);
        kill(pid2, SIGTERM);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return(-13);
    }

    if (pid3 == 0) {
        dup2(groff_less[0], STDIN_FILENO);

        close(zcat_groff[0]);
        close(zcat_groff[1]);
        close(groff_less[0]);
        close(groff_less[1]);

        execlp("less", "less", "-R", (char *)NULL);
        perror("exec less");
        _exit(127);     //Unix command not found thing 
    }

    /* parent */
    close(zcat_groff[0]);
    close(zcat_groff[1]);
    close(groff_less[0]);
    close(groff_less[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return(0);
}
