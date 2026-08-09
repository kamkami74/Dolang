#include "include/string.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_create(string* s,char* str){
    puts("creating string");
    *s = creastr(str);
    assert( s->self ); printstr(s);
    puts("string created");
}

void test_copy(string* s1,string* s2){
    puts("copying string");
    s1 = copystr(s1,s2);
    assert(s1);
    assert(s1->self && s1->self != s2->self );
    assert(s1->len == s2->len && s1->n == s2->n );
    puts("string created");
}

int main(void){
    string s1; string s2;
    test_create(&s1,"Hello World!");
    test_copy(&s2,&s1);
    test_copy(&s1,&s2);
    return 0;
}
