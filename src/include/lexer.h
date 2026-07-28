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

void lexer_advance(void);
int lexer_done(void);

void init_lexer(char* filepath);
void lexer_analyse(char* filepath);

void lexeme_print(void);

lexeme_t current_lexeme(void);

void lexer_terminate(void);

#endif
