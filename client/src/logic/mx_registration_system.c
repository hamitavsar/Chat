#include "client.h"

client_context_t *client_context;

gboolean mx_registration_system(void *data) {
    char *paket = (char *)data;
    char *status = get_value_by_key(paket, "STATUS");
    client_context->kullaniciadi = get_value_by_key(paket,"TO");

    if (!strcmp(status, "success")) {
        gtk_widget_destroy(grid);
        mx_main_menu(); 
    }
    return 0;
}
