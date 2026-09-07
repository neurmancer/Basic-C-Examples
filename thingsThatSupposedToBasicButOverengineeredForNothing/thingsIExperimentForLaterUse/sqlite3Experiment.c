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
        return(-1);
    }
    strcat(cwd, "/test.db");
    
    rc = sqlite3_open(cwd, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Veritabanı açılamadı: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(-1);
    }
    const char *create_sql = "CREATE TABLE IF NOT EXISTS People(Id INT, Name TEXT);";
    rc = sqlite3_exec(db, create_sql, 0, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Tablo oluşturma hatası: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(-1);
    }

    const char *sql = "INSERT INTO People(Id, Name) VALUES(?, ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, 1);
        sqlite3_bind_text(res, 2, "Thea", -1, SQLITE_STATIC);
    }
    else {
        fprintf(stderr, "Sorgu hazırlanamadı: %s (Kod: %d)\n", sqlite3_errmsg(db), rc);
        sqlite3_close(db); 
        return(-1);
    }

    rc = sqlite3_step(res);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Ekleme başarısız: %s (Kod: %d)\n", sqlite3_errmsg(db), rc);
    } else {
        printf("Veri başarıyla eklendi!\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return(0);
}
