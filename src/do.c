#include "include/syntax.h"
#include "include/lexer.h"
#include "include/io.h"
#include "include/ast.h"
#include <stdio.h>
#include <stdbool.h>

bool silent = false;
#define DEBUG 1

char c;
int col,row;

int main(int argc,char** argv){
    Ast A = NULL;
    char* fp = "";

    if ( argc == 2){
        fp = argv[1];
    }

    init_syntax(fp);
    interpret(&A);
    Ast_print(A);
    lexer_terminate();
}
