#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
    char* self;
    size_t len;
    size_t n; // allocation size
} string;


string creastr(char* str);
string* copystr(string* s1, string* s2);
int samestr(string s1, string s2);
string itos(int n);
void printstr(string s);

#endif
