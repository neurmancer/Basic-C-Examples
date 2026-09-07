#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    sqlite3 *db = NULL;
    sqlite3_stmt *res = NULL;
    int rc = 0;
    char cwd[1024] = { 0 };
    
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error");
        return(-1);
    }
    strcat(cwd, "/test.db");
    

    rc = sqlite3_open(cwd, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "DB Fucked up: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(-1);
    }


    const char *sql = "SELECT Id, Name FROM People;";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Lulz: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(-1);
    }


    printf("%-5s | %-20s\n", "ID", "Name");
    printf("-------------------------------\n");

    while (sqlite3_step(res) == SQLITE_ROW) {
        // Sütun indeksleri 0'dan başlar (0 = Id, 1 = Name)
        int id = sqlite3_column_int(res, 0);
        const unsigned char *name = sqlite3_column_text(res, 1);
        
        printf("%-5d | %-20s\n", id, name);
    }
        //FUCK YEAH IT  WORKS!!!! 
    sqlite3_finalize(res);
    sqlite3_close(db);
    return(0);
}
