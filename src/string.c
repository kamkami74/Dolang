#include "include/string.h"

string creastr(char* str){
    string s;
    int len = 0;

    while ( str[len] != '\0' ) len ++;

    s.self = str;
    s.len = len;
    s.n = 0;
    return s;
}

int samestr(string s1, string s2){
    if ( s1.len != s2.len )
        return 0;
    for ( int i = 0; i < s1.len; i ++ ){
        if ( s1.self[i] != s2.self[i] ) 
            return 0;
    }
    return 1;
}

string* copystr(string* s1, string* s2){
    if ( s2->self == NULL ) 
        return NULL;
    s1->self = malloc( sizeof(char) * s2->len );
    for ( int i = 0; i < s2->len; i ++ ){
        s1->self[i] = s2->self[i];
    }
    s1->len = s2->len;
    s1->n = s1->len;
    return s1;
}

string itos(int n){
    string s;
    int i = n; int p = 0; 
    while ( i > 0 ){
        i /= 10;
        p ++;
    }
    printf("%d >= (10^%d)",n,p);
    char* str = malloc( sizeof(char) * (p+1) );

    i = n; int c = 0;
    while( i > 0 ){
        str[(p-1)-c] = (i % 10) + '0' ;
        i /= 10;
        c++;
    }
    
    s.self = str;
    s.len = p; s.n = p;

    puts("");
    return s; 
}

void appstr(string* s,char c){
    if ( s->n == 0 ){
        copystr(s,s); 
    }
}

void printstr(string s){
    puts(s.self);
}

