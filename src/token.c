#include "include/token.h"


char* token_to_str(token_t t){

    switch(t){
        case TOKEN_ID:
            return "ID";
        case TOKEN_INT: 
            return "INT";
        case TOKEN_FLOAT:
            return "FLOAT";
        case TOKEN_PLUS:
            return "PLUS";
        case TOKEN_MINUS:
            return "MINUS";
        case TOKEN_MUL:
            return "MUL";
        case TOKEN_DIV:
            return "DIV";
        case TOKEN_INCR:
            return "INCR";
        case TOKEN_DECR:
            return "INCR";
        case TOKEN_EOF:
            return "EOF";
        default:
            return "ERROR";
    }
}
