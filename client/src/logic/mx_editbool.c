#include "client.h"

void mx_editbool (GtkWidget* widget,gpointer data){ 
    client_context->ara = 0;
    gtk_widget_destroy(widget);
}
