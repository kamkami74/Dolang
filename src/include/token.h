#ifndef TOKEN_H
#define TOKEN_H

typedef enum token {
    TOKEN_ID,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_PLUS = 10,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EOF,
    TOKEN_ERROR
} token_t;

char* token_to_str(token_t t);

#endif
