#include "server.h"

void mx_dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        mx_write_to_log(msg, 2);
        sqlite3_close(db); 
        exit(1);
    }
}
