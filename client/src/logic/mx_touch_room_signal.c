#include "client.h"

void mx_touch_room_signal(GtkWidget *listbox, void *socket){
    client_context->saydir = 0;
    GtkListBoxRow *selectedrow = gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    int indexrow = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(selectedrow));
    client_context->indexrow =indexrow;
    GList *gl = gtk_container_get_children(GTK_CONTAINER(selectedrow));
    GtkGrid *gridchild = gl->data;
    GtkWidget *lab = gtk_grid_get_child_at(gridchild,1,0);
    if( client_context->bayrak == FALSE){
        scrollnewmess = gtk_scrolled_window_new(0,0);
        gtk_fixed_put(GTK_FIXED (fixed), scrollnewmess, 300,718);
        gtk_widget_set_size_request(scrollnewmess,724,50);
        downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0); 
        gtk_widget_set_size_request(downbox,724,50);
        gtk_widget_set_name(downbox,"downbox");
        gtk_container_add(GTK_CONTAINER(scrollnewmess), downbox);
        screp = gtk_button_new();
        gtk_box_pack_end(GTK_BOX(downbox), screp, FALSE, FALSE, 0);
        GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/send.jpeg",NULL); 
        iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
        icon = gtk_image_new_from_pixbuf(iconn);
        gtk_button_set_image (GTK_BUTTON (screp), icon);
        g_signal_connect(screp, "clicked", G_CALLBACK(mx_create_message_system), NULL);
      
        textbuffer = gtk_text_buffer_new(NULL);
        scrollm = gtk_scrolled_window_new(0,0);
        gtk_box_pack_start(GTK_BOX(downbox),scrollm, TRUE, TRUE, 0);
        newmessedgentry = gtk_text_view_new_with_buffer(textbuffer);
        gtk_widget_set_name(newmessedgentry,"newmessedgentry");
        gtk_container_add(GTK_CONTAINER(scrollm),newmessedgentry);
        scrollmess = gtk_scrolled_window_new(0,0);
        gtk_fixed_put(GTK_FIXED (fixed), scrollmess, 300,50);
        gtk_widget_set_name(scrollmess,"scrollmess");
        gtk_widget_set_size_request(GTK_WIDGET(scrollmess),724,668);
        listboxmess = gtk_list_box_new();
        gtk_widget_set_name(listboxmess,"listboxmess");
        gtk_container_add(GTK_CONTAINER(scrollmess), listboxmess);
         g_idle_add ((int (*)(void *))show_widget, window);
        client_context->bayrak = TRUE;
    }
    int *test = (int *)socket;
    char *chat_name = client_context->kullaniciadi;
    char chat_id[40];
    bzero(chat_id, 40);
    sprintf(chat_id, "CHATID:%d", ++indexrow);
    char* chat_id_str = mx_strjoin("CHATIDFROMDB:", client_context->mas[client_context->indexrow]);
    char *paket_str = NULL;
    cJSON *paket     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("msg_c");
    cJSON_AddItemToObject(paket, "TYPE", json_value);
    json_value = cJSON_CreateString(chat_name);
    cJSON_AddItemToObject(paket, "CHATNAME", json_value);
    json_value = cJSON_CreateString(mx_itoa(++indexrow));
    cJSON_AddItemToObject(paket, "CHATID", json_value);
    json_value = cJSON_CreateString("0");
    cJSON_AddItemToObject(paket, "FROMMSG", json_value);
    json_value = cJSON_CreateString("15");
    cJSON_AddItemToObject(paket, "TOMSG", json_value);
    json_value = cJSON_CreateString(client_context->mas[client_context->indexrow]);
    cJSON_AddItemToObject(paket, "CHATIDFROMDB", json_value);
    paket_str = cJSON_Print(paket);
    char *paket_with_prefix = packet_len_prefix_adder(paket_str);
    send(client_context->soketfd, paket_with_prefix, (int)strlen(paket_with_prefix), 0);
}
