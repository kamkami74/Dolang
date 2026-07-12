#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct lexeme {
    token_t type;
    char* str;
    union {
        float fval;
        int ival;
    };
    int row, col;
} lexeme_t;

void init_lexer(char* filepath);
void lexer_advance();
int lexer_done();


void lexer_analyse(char* filepath);

void lexeme_print();

#endif
