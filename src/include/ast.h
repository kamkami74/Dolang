#ifndef AST_H
#define AST_H

typedef enum {
    AST_MATH
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
    struct ast* left;
    struct ast* right;
} t_ast;

typedef t_ast* Ast;

Ast Ast_init();

Ast create_operation(OperationType op,Ast A1,Ast A2);
 
void Ast_free(Ast A);


#endif
