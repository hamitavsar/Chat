#include "client.h"

gboolean mx_mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  	char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(minientry));
  	cJSON *paket = cJSON_CreateObject();
    char  *paket_str = NULL;
  	cJSON *type = cJSON_CreateString("find_user_c");
    cJSON *user = cJSON_CreateString(editbuff);
    cJSON *nick = cJSON_CreateString(client_context->kullaniciadi);

    cJSON_AddItemToObject(paket, "TYPE", type);
    cJSON_AddItemToObject(paket, "USER", user);
    cJSON_AddItemToObject(paket, "TO", nick);
    paket_str = mx_string_copy(cJSON_Print(paket));
    paket_str =  packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, paket_str, (int)strlen(paket_str), 0);
    return FALSE;
}
