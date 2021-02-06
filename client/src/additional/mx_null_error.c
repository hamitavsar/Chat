#include "client.h"

//Boş veri girişini engelleme
void mx_null_error(char *msg) {
	write(2, msg, (int)strlen(msg));
	exit(1);
}
