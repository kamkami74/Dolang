#include "include/syntax_analyser.h"
#include "include/io.h"
#include <stdio.h>
#include <stdbool.h>

bool silent = false;

char c;
int col,row;

int main(int argc,char** argv){
    char* fp = "";

    if ( argc == 2){
        fp = argv[1];
    }

    init_syntax(fp);
    interpret();
    close_file();
}
