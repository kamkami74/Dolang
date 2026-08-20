#include "include/string.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_create(string* s,char* str){
    printf("creating string: ");
    *s = creastr(str);
    assert( s->self );
    puts("done");
}

void test_compare_same(string s1, string s2){
    printf("comparing strings: ");
    int same = samestr(s1,s2);
    assert( same == 1 );
    puts("done");
}

void test_compare_different(string s1, string s2){
    printf("comparing strings: ");
    int same = samestr(s1,s2);
    assert( same == 0 );
    puts("done");
}

int main(void){
    string s1, s2; 
    test_create(&s1,"Hello World!");
    test_create(&s2,"Hello World!");

    string i = itos(15213);
    printstr(i);


    //test_compare_different(s1,s2);

    return 0;
}
