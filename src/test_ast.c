#include "include/ast.h"
#include <stdio.h>
#include <assert.h>

static void test_init(Ast* A);
static void test_free(Ast A);

static void test_init(Ast* A){
    puts("Test creation Ast");
    *A = Ast_init();
    assert(*A);
    puts("Ast created");
}

static void test_append(Ast* A,int n){
    if ( n <= 1 )
        return;
    *A = Ast_init();
    assert(*A);
    test_append(&((*A)->left),n/2);
    test_append(&((*A)->right),n/2);
}

static void check_ast(Ast A){
    if ( A == NULL ){
        puts("");
        return;
    }
    assert(A);
    check_ast(A->left);
    printf(" ");
    check_ast(A->right);
    if ( A->left ){
        printf("/");
    }
    if ( A->right ){
        printf("\\");
    }
}

static void test_free(Ast A){
    puts("Test freeing up memory");
    Ast_free(A);
    puts("Memory freed up");
}

int main(void){
    Ast A;
    test_init(&A); 
    Ast_free(A);

    test_append(&A,8);
    check_ast(A);
    puts("");

    test_free(A);
    return 0;
}
