#ifndef VAR_H
#define VAR_H

#include <stdint.h>
#include <stdlib.h>
#include "string.h"

typedef enum{
    VAL_INT,
    VAL_STR,
    VAL_FLT
} VarType;

typedef struct {
    VarType type;
    union {
        int32_t ival;
        float fval;
        string str;
    };
    size_t n;
} t_var;


void assign_var(t_var* v,VarType t,void* val);
void print_var(t_var v);


#endif
