#include "client.h"

gboolean mx_create_message_system(void *data){
    char *message_from_user = mx_get_text_of_textview(newmessedgentry);
    if (mx_strcmp(message_from_user,"")!= 0) {
    char *processed_msg_from_user = mx_change_offensive_words(message_from_user);
    char *all_users = client_context->tumkullanicilar;
    char  *paket_str = NULL;
    cJSON *paket = cJSON_CreateObject();
    cJSON *type   = cJSON_CreateString("add_msg_c");
    cJSON *type2  = cJSON_CreateString("string");
    char *current_time = mx_get_time();
    cJSON *time        = cJSON_CreateString(current_time);
    cJSON *msg         = cJSON_CreateString(processed_msg_from_user);
    cJSON *allusers    = cJSON_CreateString(all_users);
    cJSON *message_id  = cJSON_CreateString("0");
    int chat_id_client = client_context->indexrow; 
    cJSON *chat_id     = cJSON_CreateString(client_context->mas[client_context->indexrow]);
    cJSON *kullaniciadi    = cJSON_CreateString(client_context -> kullaniciadi);
    cJSON_AddItemToObject(paket, "TYPE", type);
    cJSON_AddItemToObject(paket, "TYPE2", type2);
    cJSON_AddItemToObject(paket, "MESSAGEID", message_id);
    cJSON_AddItemToObject(paket, "TIME", time);
    cJSON_AddItemToObject(paket, "TO", allusers);
    cJSON_AddItemToObject(paket, "MESSAGE", msg);
    cJSON_AddItemToObject(paket, "CHATID", chat_id);
    cJSON_AddItemToObject(paket, "SENDER", kullaniciadi);
    gtk_text_buffer_set_text (GTK_TEXT_BUFFER(textbuffer),"",-1);
    paket_str = mx_string_copy(cJSON_Print(paket));
    char *paket_str1 =  packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, paket_str1, (int)strlen(paket_str1), 0);
    free(paket_str);
    free(paket_str1);
    }
    return 0;
}
