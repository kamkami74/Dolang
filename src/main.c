#include <stdio.h>
#include "include/lexer.h"
#include "include/io.h"

char c;
int col,row;

int main(int argc,char** argv){
    char* fp = "";

    printf("%d\n",argc);

    if ( argc == 2){
        fp = argv[1];
        puts(fp);
    }

    lexer_analyse(fp);
}
