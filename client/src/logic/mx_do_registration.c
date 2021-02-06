#include "client.h"

#define OKEY                      0
#define PASS_FORBIDDEN_SYMBOLS    1
#define PASS_DIFFERENT            2
#define NICK_FORBIDDEN_SYMBOLS    3
#define LOGIN_FORBIDDEN_SYMBOLS   4
#define NICKNAME_IS_EMPTY         5
#define LOGIN_IS_EMPTY            6
#define PASSWORD_1_IS_EMPTY       7
#define PASSWORD_2_IS_EMPTY       8
#define PASSWORD_TOO_SHORT        9


static int login_validator(char *input_login) {
    char *forbidden_symbols = " :";
    
    if (mx_symbols_in_str(input_login, forbidden_symbols))
        return LOGIN_FORBIDDEN_SYMBOLS;

    if ((int)strlen(input_login) == 0)
        return LOGIN_IS_EMPTY;
    return OKEY;
}

static int nick_validator(char *input_nick) {
    char *forbidden_symbols = " :";

    if (mx_symbols_in_str(input_nick, forbidden_symbols))
        return NICK_FORBIDDEN_SYMBOLS;
    if ((int)strlen(input_nick) == 0)
        return NICKNAME_IS_EMPTY;
    return OKEY;
}


static int pass_validator(char *password_1, char *password_2) {
    char *forbidden_symbols = " :";

    if (mx_symbols_in_str(password_1, forbidden_symbols))
        return PASS_FORBIDDEN_SYMBOLS;
    if (strcmp(password_1, password_2) != 0)
        return PASS_DIFFERENT;
    if ((int)strlen(password_1) == 0)
        return PASSWORD_1_IS_EMPTY;
    if ((int)strlen(password_2) == 0)
        return PASSWORD_2_IS_EMPTY;
    if ((int)strlen(password_1) < 8)
        return PASSWORD_TOO_SHORT;
    return OKEY;
}


static int validate(char *input_login, char *input_nick, char *input_password, char *input_password_confirm) {
    int validate_login_status = login_validator(input_login);
    int validate_nick_status  = nick_validator(input_nick);
    int validate_pass_status  = pass_validator(input_password, input_password_confirm);

    if (validate_login_status != OKEY)
        return validate_login_status;
    else if (validate_nick_status != OKEY)
        return validate_nick_status;
    else if (validate_pass_status != OKEY)
        return validate_pass_status;
    return OKEY;
}

static char *make_paket(char *input_login, char *input_nick, char *input_password) {
    char *paket_str = NULL;
    cJSON *paket     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("reg_c");
    cJSON_AddItemToObject(paket, "TYPE", json_value);
    json_value = cJSON_CreateString(input_login);
    cJSON_AddItemToObject(paket, "LOGIN", json_value);
    json_value = cJSON_CreateString(mx_rsa_encrypt(crypt(input_password, "X07")));
    cJSON_AddItemToObject(paket, "PASSWORD", json_value);
    json_value = cJSON_CreateString(input_nick);
    cJSON_AddItemToObject(paket, "NICKNAME", json_value);
    paket_str = cJSON_Print(paket);

    return paket_str;
}

void mx_do_registration(GtkWidget *Registration, client_context_t *client_context) {
    char *input_login            = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    char *input_nick             = (char *)gtk_entry_get_text(GTK_ENTRY(nickname));
    char *input_password         = (char *)gtk_entry_get_text(GTK_ENTRY(Password));
    char *input_password_confirm = (char *)gtk_entry_get_text(GTK_ENTRY(SecondPassword));

    // Yanış veri girişi
    int status = validate(input_login, input_nick, input_password, input_password_confirm);
    if (status != OKEY) {
        write(2, "Error while validate\n", 22);
            
    }
    
    else {
        char *paket             = make_paket(input_login, input_nick, input_password);
        char *packet_with_prefix = packet_len_prefix_adder(paket);
         // Sunucuya kayıt verilerini gönderiyor
        send(client_context->soketfd, packet_with_prefix, (int)strlen(packet_with_prefix), 0);
        free(paket);
        free(packet_with_prefix);
    }
}
