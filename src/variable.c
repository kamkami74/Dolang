#include "include/variable.h"


void assign_var(t_var* v,VarType t,void* val){
    v->type = t;
    switch(t){
        case VAL_INT:
            v->ival = *(int*)val;
            break;
        case VAL_FLT:
            v->ival = *(float*)val;
            break;
        case VAL_STR:
            v->str = creastr(val);
            break;
        default:
            break;
    } 
}

void print_var(t_var v){
    switch(v.type){
        case VAL_INT:
            printf("%d",v.ival);
            break;
        case VAL_FLT:
            printf("%f",v.fval);
            break;
        case VAL_STR:
            printstr(v.str);
            break;
        default:
            break;
    } 
}
