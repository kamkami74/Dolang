#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

#define MIN_STR_SIZE 256

typedef struct {
    char* self;
    size_t len;
    size_t n; // allocation size
} t_string;

t_string* newstr();

void strjoin(t_string* str);





#endif
