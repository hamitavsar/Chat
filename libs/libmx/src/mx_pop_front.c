#include "libmx.h"

void mx_pop_front(t_list **head){
    t_list *node_to_delete = *head;
    *head = node_to_delete->next;
    free(node_to_delete);
    free(node_to_delete->data);
}

