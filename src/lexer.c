#include "include/lexer.h"
#include "include/io.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    S_INIT,
    S_NUMBER,
    S_FLOAT,
    S_ID,
    S_FINAL,
    S_ERROR,
} State;

typedef enum {
    CT_NONE = 0,
    CT_SYMBOL,
    CT_LETTER,
    CT_DIGIT,
    CT_EOF,
} Character_type;

static lexeme_t Cl; // current lexeme
static char cc; // current character
static char msg[256];  
static State s;

static void recognize_lexeme();
static void recognize_number();
static void recognize_float();

static void push_char();
static void reset_lexeme();

static int is_whitespace(char c);
static int is_symbol(char c);

static void lexical_error(const char* msg);

static Character_type char_type(char c);


void lexer_analyse(char* filepath){
    init_lexer(filepath);
    while( !lexer_done() ) 
        lexer_advance();
    close_file();
}

void init_lexer(char* filepath){
    s = S_INIT;
    init_file(filepath);
    Cl.str = malloc(sizeof(char) * 256);
}


void lexer_advance(){
    s = S_INIT;
    recognize_lexeme();
}

lexeme_t current_lexeme(){
    return Cl;
}

int lexer_done(){
    return cc == EOF;
}

void lexeme_print(){
    switch(Cl.type){
        case TOKEN_INT:
            printf("<%s>, string: %s,\t value: %d\n",
                    token_to_str(Cl.type),
                    Cl.str,
                    Cl.ival);
        break;
        case TOKEN_FLOAT:
            printf("<%s>, string: %s,\t value: %f\n",
                    token_to_str(Cl.type),
                    Cl.str,
                    Cl.fval);
        break;
        default:
            printf("<%s>, string: %s\n",
                    token_to_str(Cl.type),
                    Cl.str);
        break;
    }
}

static void recognize_lexeme(){
    cc = consume_char();
    if ( char_type(cc) == CT_EOF )
        return;

    while ( is_whitespace(cc) ){
        cc = consume_char();
    }

    while( s != S_FINAL ){
        push_char();
        switch(s){
            case S_INIT:
                switch(char_type(cc)){
                    case CT_DIGIT:
                        Cl.type = TOKEN_INT;
                        Cl.row = get_row();
                        Cl.col = get_col();
                        Cl.ival = cc - '0';
                        s = S_NUMBER;
                        cc = consume_char();
                        break;
                    case CT_EOF:
                        Cl.type = TOKEN_EOF;
                        s = S_FINAL;
                        break;
                    default:
                        s = S_FINAL;
                        break;
                }
                break;
            case S_NUMBER:
                recognize_number();
                break;
            case S_FLOAT:
                recognize_float();
                break;
            case S_ERROR:
                close_file();
                exit(1);
                break;
            default:
                s = S_FINAL;
            break;
        }
    }
    lexeme_print();
    reset_lexeme();
}

static void recognize_number(){
    switch(char_type(cc)){
        case CT_DIGIT:
            Cl.ival = Cl.ival * 10 + cc - '0';
            cc = consume_char();
            break;
        case CT_LETTER:
            s = S_ERROR;
            sprintf(msg,"Unexpected character '%c' after number %d",cc,Cl.ival);
            lexical_error(msg);
            break;
        case CT_SYMBOL:
            if ( cc != '.' ){
                s = S_ERROR;
                sprintf(msg,"Unexpected symbol '%c' after number %d",cc,Cl.ival);
                lexical_error(msg);
                break;
            }


            s = S_FLOAT;
            Cl.type = TOKEN_FLOAT;
            Cl.fval = (float) Cl.ival;
            cc = consume_char();

            break;
        default:
            s = S_FINAL;
            break;
    }
}

static float decimal = 0.1f;
static int literal_count = 0;

static void recognize_float(){
    switch(char_type(cc)){
        case CT_DIGIT:
            Cl.fval = Cl.fval + (float) ( cc - '0' ) * decimal;
            decimal /= 10;
            cc = consume_char();
            break;
        case CT_LETTER:
            if ( literal_count == 0 && cc == 'f' ){
                literal_count ++;
                cc = consume_char();
                break;
            }
            s = S_ERROR;
            sprintf(msg,"Unexpected character '%c' after number %f",cc,Cl.fval);
            lexical_error(msg);
            break;
        case CT_SYMBOL:
            s = S_ERROR;
            sprintf(msg,"Unexpected symbol '%c' after number %f",cc,Cl.fval);
            lexical_error(msg);
            break;
        default:
            literal_count = 0;
            s = S_FINAL;
            break;
    }
}

static void reset_lexeme(){
    Cl.ival = 0;
    Cl.str[0] = '\0';
    Cl.type = 0;
}

static void push_char(){
    int len = strlen(Cl.str);
    Cl.str[len] = cc;
    Cl.str[++len] = '\0';
}

static int is_whitespace(char c){
    return c == ' ' || c == '\n' || c == '\t' ;
}

static int is_symbol(char c){
    return c == '+' || 
           c == '-' ||
           c == '*' || 
           c == '/' ||
           c == '.' ;
}

static Character_type char_type(char c){
    if ( isdigit(c) ) return CT_DIGIT;
    if ( isalpha(c) ) return CT_LETTER;
    if ( is_symbol(c) ) return CT_SYMBOL;
    if ( c == EOF ) return CT_EOF;
    return CT_NONE;
}

static void lexical_error(const char* msg){
   FG_RED; 
   printf("Lexical error");
   FG_BG_RESET;
   printf(": \"%s\"\n",msg);
   printf("\tin line %d\n",Cl.row);     
   printf("\tin file \"%s\"\n",get_filename());     
}

