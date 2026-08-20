#ifndef HASHTABLE_H
#define HASHTABLE_H


#define HT_SIZE 100

#include "linked_list.h"
#include <string.h>


typedef struct {
    size_t len, n;
    t_list* arr;
}t_ht; // hash table for short


t_ht* init_hash(void);

void ht_insert(t_ht* ht,char* id,void* val);

#endif
