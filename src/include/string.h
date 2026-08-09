#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN_STR_SIZE 16

typedef struct {
    char* self;
    size_t len;
    size_t n; // allocation size
} string;


string creastr(char* str);
string* newstr(size_t n);
string* copystr(string* s1, string* s2);
void printstr(string* s);
void strfree(string* s);

#endif
