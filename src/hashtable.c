#include "include/hashtable.h"

t_ht* init_hash(void){
    int n = HT_SIZE; 
    t_ht* ht = malloc( sizeof(t_ht) * n );
    return ht;
}

int hash_func(char* str){
    int hash = 0, prime = 31;
    for ( int i = 0; i < strlen(str) ; i ++ ){
        hash += (str[i] * prime) % HT_SIZE;
    }

    return hash;
}

int ht_lookup(t_ht** ht,char* str){
    int hash = hash_func(str);

    if ( ht[hash] == NULL ){
        printf("Key %s not found\n",str);
        return 1;
    }

    if ( ht[hash]->arr != NULL ){
        

    }


    return 0;
}

void ht_insert(t_ht* ht,char* id,void* val){

}
