#include "include/lexer.h"
#include "include/io.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

extern bool silent;

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

/* ------------------------------ */

static lexeme_t Cl; // current lexeme
static char cc; // current character
static char msg[256]; // error message buffer
static State s;

static void recognize_lexeme();
static void recognize_number();
static void recognize_float();
static void recognize_symbol();
static void recognize_id();

static void push_char();
static void reset_lexeme();

static int is_whitespace(char c);
static int is_symbol(char c);

static void lexical_error(const char* msg);

static Character_type char_type(char c);

/* ------------------------------ */

void init_lexer(char* filepath){
    s = S_INIT;
    init_file(filepath);
    Cl.str = malloc(sizeof(char) * 256);
    cc = consume_char();
}

void lexer_analyse(char* filepath){
    init_lexer(filepath);
    while( !lexer_done() ){
        lexer_advance();
    }
    free(Cl.str);
}


void lexer_advance(void){
    reset_lexeme();
    recognize_lexeme();
}

lexeme_t current_lexeme(void){
    return Cl;
}

int lexer_done(void){
    return cc == EOF;
}

void lexeme_print(void){
    switch(Cl.type){
        case TOKEN_INT:
            printf("<%s>\tstring: %s, value: %d\n",
                    token_to_str(Cl.type),
                    Cl.str,
                    Cl.ival);
        break;
        case TOKEN_FLOAT:
            printf("<%s>\tstring: %s, value: %f\n",
                    token_to_str(Cl.type),
                    Cl.str,
                    Cl.fval);
        break;
        default:
            printf("<%s>\tstring: %s\n",
                    token_to_str(Cl.type),
                    Cl.str);
        break;
    }
}

void lexer_terminate(void){
    free(Cl.str);
    close_file();
    exit(1);
}

/* ------------------------------ */


static void recognize_lexeme(){

    while ( is_whitespace(cc) ){
        cc = consume_char();
    }

    while( s != S_FINAL ){
        switch(s){
            case S_INIT:
                switch(char_type(cc)){
                    case CT_DIGIT:
                        s = S_NUMBER;

                        Cl.type = TOKEN_INT;
                        Cl.row = get_row();
                        Cl.col = get_col();
                        break;
                    case CT_EOF:
                        Cl.type = TOKEN_EOF;
                        s = S_FINAL;
                        break;
                    case CT_SYMBOL:
                        push_char();
                        Cl.row = get_row();
                        Cl.col = get_col();
                        recognize_symbol();
                        break;
                    case CT_LETTER:
                        Cl.row = get_row();
                        Cl.col = get_col();
                        Cl.type = TOKEN_ID;
                        push_char();
                        cc = consume_char();
                        s = S_ID;
                    break;
                    default:
                        sprintf(msg, "Unexpected character '%c'",cc);
                        s = S_ERROR;
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
                Cl.row = get_row();
                Cl.col = get_col();
                lexical_error(msg);
                lexer_terminate();
                return;
            case S_ID:
                recognize_id();
                break;
            default:
                s = S_FINAL;
            break;
        }
    }
    if ( !silent ) 
        lexeme_print();
}

static void recognize_number(){
    switch(char_type(cc)){
        case CT_DIGIT:
            push_char();
            Cl.ival = Cl.ival * 10 + cc - '0';
            cc = consume_char();
            break;
        case CT_LETTER:
            sprintf(msg,"Unexpected character '%c' after number %d",cc,Cl.ival);
            s = S_ERROR;
            break;
        case CT_SYMBOL:
            if ( cc == '.' ){
                push_char();
                Cl.type = TOKEN_FLOAT;
                Cl.fval = (float) Cl.ival;
                cc = consume_char();
                s = S_FLOAT;
                return;
            }
            s = S_FINAL;
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
            push_char();
            Cl.fval = Cl.fval + (float) ( cc - '0' ) * decimal;
            decimal /= 10;
            cc = consume_char();
            break;
        case CT_LETTER:
            if ( literal_count == 0 && (cc == 'f' || cc == 'F') ){
                literal_count ++;
                cc = consume_char();
                break;
            }
            sprintf(msg,"Unexpected character '%c' after number %f",cc,Cl.fval);
            s = S_ERROR;
            break;
        default:
            literal_count = 0;
            s = S_FINAL;
            break;
    }
}

static void recognize_symbol(){
    switch(cc){
        case '+':
            Cl.type = TOKEN_PLUS;
            cc = consume_char();
            if ( cc == '+' ){
                Cl.type = TOKEN_INCR;
                push_char();
                cc = consume_char();
            }
            s = S_FINAL;
        break;
        case '-':
            Cl.type = TOKEN_MINUS;
            cc = consume_char();
            if ( cc == '-' ){
                Cl.type = TOKEN_DECR;
                push_char();
                cc = consume_char();
            }
            s = S_FINAL;
        break;
        case '*':
            Cl.type = TOKEN_MUL;
            cc = consume_char();
            s = S_FINAL;
        break;
        case '/':
            Cl.type = TOKEN_DIV;
            cc = consume_char();
            s = S_FINAL;
        break;
        case '(':
            Cl.type = TOKEN_OPAR;
            cc = consume_char();
            s = S_FINAL;
        break;
        case ')':
            Cl.type = TOKEN_CPAR;
            cc = consume_char();
            s = S_FINAL;
        break;
        default:
            s = S_FINAL;
            break;
    }
}


static void recognize_id(){
    switch(char_type(cc)){
        case CT_DIGIT:
        case CT_LETTER:
            push_char();
            cc = consume_char();
            s = S_ID;
            break;
        case CT_SYMBOL:
            sprintf(msg,"Unexpected char '%c' after '%s'",cc,Cl.str);
            s = S_ERROR;
            break;
        default:
            s = S_FINAL;
            break;
    }
}

static void reset_lexeme(){
    s = S_INIT;
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
           c == '.' ||
           c == '(' ||
           c == ')' ;
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
   printf("\t%s\n",Cl.str);     
   printf("\t^^^\n");     
   printf("\tin line %d, ",Cl.row);     
   printf("col %d\n" ,Cl.col);     
   printf("\tin file \"%s\"\n",get_filename());     
}
