#include "include/string.h"

string* newstr(size_t n){
    string* s = malloc(sizeof(string));
    s->self = malloc(sizeof(char) * n);
    //s->self[0] = '\0';
    s->n = n; s->len = 0;
    return s;
}

string creastr(char* str){
    string s;
    int n = MIN_STR_SIZE; int len = strlen(str);
    while ( len >= n )
        n *= 2;
    s.self = str;
    s.len = len;
    return s;
}

string* copystr(string* s1, string* s2){
    if ( s2 == NULL ){
        puts("source string doesn't exist");
        return NULL;
    } 

    if ( s2->self == NULL ){
        return NULL;
    }

    s1 = newstr(s2->n);

    size_t i;
    for ( i = 0; i < s2->len; i ++ ){
        s1->self[i] = s2->self[i];
    }

    return s1;
}

void printstr(string* s){
    puts(s->self);
}

void strfree(string* s){
    free(s);
}
