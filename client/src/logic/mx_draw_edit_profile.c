#include "client.h"

void mx_draw_edit_profile(GtkWidget *widget, gpointer data){
    if (client_context->edit == 0) {
        client_context->edit = 1;
        editwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_resizable (GTK_WINDOW(editwindow), FALSE);
        gtk_window_set_transient_for (GTK_WINDOW(editwindow),GTK_WINDOW(window));
        g_signal_connect(editwindow,"delete-event",G_CALLBACK(mx_editbool),NULL);
        gtk_window_set_title(GTK_WINDOW(editwindow),"Settings");
        gtk_widget_set_size_request(GTK_WIDGET(editwindow),300,500);
        editfixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(editwindow), editfixed);
        editgrid = gtk_grid_new();
        gtk_fixed_put(GTK_FIXED(editfixed),editgrid,25,100);
        gtk_widget_set_name(editgrid,"editgrid");
        themelabel = gtk_label_new("Set New Password");
        gtk_grid_attach(GTK_GRID(editgrid),themelabel, 0, 0, 1, 1);
        changepassword = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(changepassword),"");
        gtk_grid_attach(GTK_GRID(editgrid),changepassword, 0, 4, 2, 1);
        g_signal_connect(changepassword,"activate", G_CALLBACK(mx_change_password_system), NULL);
        logout = gtk_button_new_with_label("logout");
         gtk_grid_attach(GTK_GRID(editgrid),logout, 0, 5, 1, 1);
        g_signal_connect(logout,"clicked", G_CALLBACK(mx_logout_system), NULL);
        g_idle_add ((int (*)(void *))show_widget, editwindow);
    }
}
