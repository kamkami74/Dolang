#include "include/linked_list.h"

t_list* create_list(void){
    t_list* l = malloc(sizeof(t_list));
    l->next = NULL; 
    return l;
}

int list_push(t_list** l, t_var val, string id){
    t_list* head = create_list();
    head->val = val;
    head->id = id;
    head->next = *l;
    *l = head;
    return 0;
}

int list_pop(t_list** l){
    if ( l == NULL ){
        return 1;
    }
    if ( *l == NULL ){
        return 0;
    }
    t_list* l1 = *l;
    *l = (*l)->next;
    free(l1);
    return 0;
}


void free_list(t_list** l){
    if ( l == NULL )
        return;
    if ( *l == NULL )
        return;
    list_pop(l);
    free_list(&((*l)->next));
}
