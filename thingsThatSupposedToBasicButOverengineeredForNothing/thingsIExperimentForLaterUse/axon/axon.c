/*
    'Sup? This file is where I'll experiment with libalpm for my custom package manager wrapper/front-end axon 

    So this is not a project or finished product just an experiment 

*/


#include <stdio.h>
#include <alpm.h>
#include <stdlib.h>

int main(void)
{

    alpm_errno_t err_no;    //To prevent namespace collison with BSD err.h  

    //Init startes here
    alpm_handle_t *handler = alpm_initialize("/", "/var/lib/pacman", &err_no);

    if (handler == NULL) {
        fprintf(stderr, "Libalpm just died...: %s\n", alpm_strerror(err_no));
        return(-13);
    }

    printf("Lib alpm ver: %s\n",alpm_version());

    alpm_db_t *db = alpm_get_localdb(handler);

    if (db) {
        printf("alpm successeded to load the db...\n");
    }

    //Life ends here and shit happens in the middle
    if(alpm_release(handler))
    {
        fprintf(stderr, "Couldn't handle the release of the db...\n");
        return(-13);    
    }

    printf("Db free'd\n");
    handler = NULL;

    

    return(0);
}