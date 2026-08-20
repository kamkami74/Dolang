#ifndef LIST_H
#define LIST_H

#include "variable.h"

typedef struct list {
    string id;
    t_var val;
    struct list* next;
} t_list;

t_list* create_list(void);

int list_push(t_list** l,t_var val, string id);
void list_update(t_list** l, t_var val, string id);

t_list* list_lookup(t_list* l,string s);
void list_print(t_list* l);

int list_pop(t_list** l);

void free_list(t_list** l);

#endif
