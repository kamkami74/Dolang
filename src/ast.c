#include "include/ast.h"

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

Ast create_const(VarType t,void* val){
    Ast a = Ast_init();
    a->type = AST_CONST;
    assign_var(&a->var,t,val);
    return a;
}

static void Op_print(OperationType op){
    switch(op){
        case OP_ADD:
            printf("+");
        break;
        case OP_SUB:
            printf("-");
        break;
        case OP_MUL:
            printf("*");
        break;
        case OP_DIV:
            printf("/");
        break;
    }
}




static void rec_print(Ast A){
    if ( A == NULL ){
        return;
    }
    switch(A->type){
        case AST_MATH:
            printf("(");
            rec_print(A->left);
            Op_print(A->op);
            rec_print(A->right);
            printf(")");
        break;
        case AST_CONST:
            print_var(A->var);
        break;
    }
}

void Ast_print(Ast A){
    rec_print(A);
    puts("");
}


void Ast_free(Ast A){
    if ( A == NULL )
        return;
    Ast_free(A->left);
    Ast_free(A->right);
    free(A);
}
