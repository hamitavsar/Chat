#include "client.h"

gboolean mx_add_new_friend(GtkWidget *widget, gpointer data) {
   char  *login = g_object_get_data(G_OBJECT(widget),"name user");

  	cJSON *paket = cJSON_CreateObject();
    char  *paket_str = NULL;
  	cJSON *type = cJSON_CreateString("add_contact_c");
    cJSON *user = cJSON_CreateString(login);
    cJSON *nick = cJSON_CreateString(client_context->kullaniciadi);

    cJSON_AddItemToObject(paket, "TYPE", type);
    cJSON_AddItemToObject(paket, "USER", user);
    cJSON_AddItemToObject(paket, "TO", nick);
    paket_str = mx_string_copy(cJSON_Print(paket));
    char *paket_str1 =  packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, mx_strdup(paket_str1), (int)strlen(paket_str1), 0);
    return FALSE;
}
