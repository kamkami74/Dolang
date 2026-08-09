#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include "variable.h"

typedef enum {
    AST_MATH,
    AST_CONST
} AstType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
} OperationType;

typedef struct ast{
    AstType type;
    OperationType op;
    t_var var;
    struct ast* left;
    struct ast* right;
} t_ast;

typedef t_ast* Ast;

Ast Ast_init();

Ast create_operation(OperationType op,Ast A1,Ast A2);
Ast create_const(VarType t,void* val);

void Ast_print(Ast A);
 
void Ast_free(Ast A);


#endif
