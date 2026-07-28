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
        t_string str;
    };
    size_t t;
} t_var;


#endif
