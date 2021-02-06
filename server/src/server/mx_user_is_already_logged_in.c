#include "server.h"


int mx_user_is_already_logged_in(connected_client_list_t *list, char *user_login) {
    
    for (connected_client_list_t *p = list; p != NULL; p = p->next) {
        if (!strcmp(p->login, user_login))
            return 1;
    }
    return 0;
}
