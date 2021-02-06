#include "client.h"
               
void mx_change_password_system(GtkWidget* widget, gpointer data){
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(widget));

    char *paket_str = NULL;
    cJSON *paket     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("change_password_c");
    cJSON_AddItemToObject(paket, "TYPE", json_value);
    json_value = cJSON_CreateString(password);
    cJSON_AddItemToObject(paket, "TO", json_value);
    json_value = cJSON_CreateString(client_context->kullaniciadi);
    cJSON_AddItemToObject(paket, "LOGIN", json_value);
    paket_str = cJSON_Print(paket);
    char *packet_with_prefix = packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, packet_with_prefix, (int)strlen(packet_with_prefix), 0);
    mx_close_window(editwindow);

}
