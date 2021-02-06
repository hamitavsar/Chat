#include "client.h"

client_context_t *client_context;

gboolean mx_registration_system(void *data) {
    char *packet = (char *)data;
    char *status = get_value_by_key(packet, "STATUS");
    client_context->username = get_value_by_key(packet,"TO");

    if (!strcmp(status, "success")) {
        gtk_widget_destroy(grid);
        mx_main_menu(); 
    }
    return 0;
}
