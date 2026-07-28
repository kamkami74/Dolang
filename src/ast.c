#include "include/ast.h"
#include <stdlib.h>

Ast Ast_init(){
    Ast a = malloc(sizeof(t_ast));
    a->left = NULL; a->right = NULL;
    return a;
}

Ast create_operation(OperationType op,Ast A1,Ast A2){
    Ast a = Ast_init();
    a->type = AST_MATH;
    a->op = op;
    a->left = A1;
    a->right = A2;
    return a;
}

void Ast_free(Ast A){
    if ( A == NULL )
        return;
    Ast_free(A->left);
    Ast_free(A->right);
    free(A);
}
