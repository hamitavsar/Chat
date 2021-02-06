#include "client.h"

void mx_login_system(client_context_t *client_context, char *paket) {
    char *length = get_value_by_key(paket,"LENGTH");
    client_context->kullaniciadi = get_value_by_key(paket,"TO");
    int len = atoi(length);
    free(length);
    t_s_glade *guinumber = (t_s_glade *)malloc(sizeof(t_s_glade));
    guinumber->paket = paket;
    guinumber->paket = mx_strdup(guinumber->paket);
    guinumber->number = 0;
    client_context->mas = mx_new_strarr(len + 1000);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_draw_message_menu, guinumber, 0);
    int i = 0;
    while (len > i && !gtk_events_pending()){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_create_row, guinumber, 0);
        i++;
    }
}
