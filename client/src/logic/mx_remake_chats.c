 #include "client.h"
 
 void mx_remake_chats(char *paket){
    char *length = get_value_by_key(paket,"LENGTH");
    int len = atoi(length);
    int i = 0;
    t_s_glade *guinumber = (t_s_glade *)malloc(sizeof(t_s_glade));
    guinumber->paket = paket;
    guinumber->paket = mx_strdup(guinumber->paket);
    guinumber->number = client_context->gui;
    GtkWidget *scroll = gtk_widget_get_parent(listbox);
    while (len > i && !gtk_events_pending()){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_create_row, guinumber, 0);
        i++;
    }
 }
