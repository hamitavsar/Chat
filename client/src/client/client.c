#include "client.h"

client_context_t *client_context;

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}


static void guinumber(int argc, char **argv, client_context_t *client_context) {
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path (provider,"./media/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(provider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    fixed = gtk_fixed_new();
    gtk_widget_set_name(fixed,"fixedd");
    gtk_container_add(GTK_CONTAINER(window), fixed); 
    
    mx_main_menu();

    gtk_main(); 
}

static struct sockaddr_in client_address_describer(int port,  char *address) { 
    /*
      1.Sunucu Adresi
      2. ip version AF_INET = IPv4
      3. Sunucuya ait port numfindsı.
     */
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr(address); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    return client_addr; 
}

void client_context_init(int sockfd) {
    client_context = (client_context_t *)malloc(sizeof(client_context_t));
    if (client_context == NULL)
        error("Client context malloc error", -1);
    client_context->soketfd = sockfd;
}

static void received_packet_analyzer(char *packet_type, char *paket) {
    if (!mx_strcmp(packet_type, "reg_s"))
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_registration_system, (void *)mx_strdup(paket), 0);
    else if (!mx_strcmp(packet_type, "login_s")){
        if(mx_strcmp(get_value_by_key(paket, "STATUS"), "false") != 0)
            mx_login_system(client_context, paket);
    }
    else if (!mx_strcmp(packet_type, "find_user_s")){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_draw_list_box_system, (void *)mx_strdup(paket), 0);
    }
    else if (!mx_strcmp(packet_type, "add_new_user_s")) {

       if(mx_strcmp(get_value_by_key(paket, "STATUS"), "false") != 0)
            mx_remake_chats(paket);
    }
    else if (!mx_strcmp(packet_type, "msg_s"))
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_create_row_system, (void *)mx_strdup(paket), 0);
     else if (!mx_strcmp(packet_type, "add_msg_s")) {
        mx_create_row_system_new(client_context, paket);
    }

}

/*
  Sunucudan gelen paketler alınız.
  Alınan paketler analiz edilir.
  Yapılan değişiklikler grafik ekrana yansıtılır
 */
static void *server_communication(void *pfindm) {
    fd_set read_descriptors;
    struct timeval tv = wait_time(1, 0);
    int status;
    char *paket;
    char *paket_type;
    while(1) {
        FD_ZERO(&read_descriptors);
        FD_SET(client_context->soketfd, &read_descriptors);
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        if (status <= 0) continue;
        // Sunucudan Gelen Paketler.
        paket      = packet_receive(client_context->soketfd);
        if (paket == NULL || !mx_strcmp(paket, "")) {
            char *msg = "get_value_by_key error in server_communication";
            write(2, msg, (int)strlen(msg));
            exit(1);
        }

        paket_type = get_value_by_key(paket, "TYPE");
        if (paket_type == NULL){
            char *msg = "get_value_by_key error in server_communication";
            write(2, msg, (int)strlen(msg));
            exit(1);
        }
        received_packet_analyzer(paket_type, paket);
        free(paket_type);
        free(paket);
    }
    return NULL;
}

int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port                       = atoi(argv[2]);
    int sockfd                     = mx_socket();
    struct sockaddr_in client_addr = client_address_describer(port, argv[1]);

    // Servera Bağlanma
    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);

    client_context_init(sockfd);
    pthread_t client_thread;
    int err = pthread_create(&client_thread, NULL, server_communication, NULL);
    error("Error while creating new thread.", err);

    // Grafik findyüz Başlatma
    guinumber(argc, argv, client_context);
    free(client_context);
    return 0;
}





