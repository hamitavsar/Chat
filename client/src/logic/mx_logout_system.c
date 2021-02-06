#include "client.h"
               
void mx_logout_system(GtkWidget *widget, gpointer data){
    mx_close_window(editwindow);
    client_context->duzenle = 0;
    if (client_context->ara == 1){
        gtk_widget_destroy(miniwindow);
        client_context-> ara = 0;
    }
  
    gtk_widget_destroy(fixed);
    g_idle_add ((int (*)(void *))show_widget, window);
    fixed = gtk_fixed_new();
    char *paket_str = NULL;
    cJSON *paket     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("logout_c");
    cJSON_AddItemToObject(paket, "TYPE", json_value);
    paket_str = cJSON_Print(paket);
    char *paket_with_prefix = packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, paket_with_prefix, (int)strlen(paket_with_prefix), 0);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    mx_main_menu();
}
