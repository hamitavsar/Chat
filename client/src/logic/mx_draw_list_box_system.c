#include "client.h"

gboolean mx_draw_list_box_system(void *data){
    char *paket = (char *)data;
    char *len_str = get_value_by_key(paket,"LENGTH");
	int len = atoi(len_str);
	gtk_widget_destroy(miniscroll);
	miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);
    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
	for (int i = 0; i < len; i++){
        char *nicknamex = mx_strjoin("NICKNAME",mx_itoa(i));
		char *nickname = get_value_by_key(paket, nicknamex);
        char *loginx = mx_strjoin("LOGIN",mx_itoa(i));
		char *login = get_value_by_key(paket, loginx);
        t_s_glade *paket = (t_s_glade *)malloc(sizeof(t_s_glade));
        paket->number = i;
        paket->login = login;
        paket->login = mx_string_copy(paket->login);
        paket->nickname = nickname;
        paket->nickname = mx_string_copy(paket->nickname);
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_draw_list_box, paket, 0);
	}
    return 0;
}
