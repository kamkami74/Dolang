#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/io.h"

static FILE* File;
static char* Filename;
static char c;
static int row, col;

void init_file(char* fp){
    row = 1;
    col = 0;
    if ( strlen(fp) != 0 ){
        File = fopen(fp,"r");

        if (!File){
            printf("File %s doesn't exist\n",fp);
            fclose(File);
            exit(1);
        };

        Filename = fp;
        return;
    } 
    File = stdin;
    Filename = "stdin";
}

char consume_char(void){
    FILE* fp = File;

    if (!feof(fp)){
        c = fgetc(fp);
        if ( c == '\n' ){
            col = 1;
            row ++;
        } else{
            col ++;
        }
    } else c = EOF;

    return c;
}

int get_row(void){
    return row;
}

int get_col(void){
    return col;
}

void close_file(void){
    fclose(File);
}

char* get_filename(void){
    return Filename;
}
