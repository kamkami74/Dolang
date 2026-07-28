#include "include/lexer.h"
#include "include/utils.h"
#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>

static void rec_expr();
static void rec_seq_term();
static void rec_seq_factor();
static void rec_term();
static void rec_factor();
static void rec_suite_seq_term();
static void rec_suite_seq_factor();
static int rec_op1(token_t* t);
static int rec_op2(token_t* t);

static void syntax_error(const char* msg);

static char msg[256];

void init_syntax(char* filename){
    init_lexer(filename);
    lexer_advance();
}

void interpret(){
    rec_expr();
}

static void rec_expr(){
    rec_seq_term();
}

static void rec_seq_term(){
    rec_term(); rec_suite_seq_term();
}

static void rec_term(){
    rec_seq_factor();
}

static void rec_seq_factor(){
    rec_factor(); rec_suite_seq_factor();
}

static void rec_factor(){
    switch( current_lexeme().type ){
        case TOKEN_FLOAT:
        case TOKEN_INT:
            lexer_advance();
            break;
        case TOKEN_OPAR:
            lexer_advance(); rec_expr();
            if ( current_lexeme().type == TOKEN_CPAR ){
                lexer_advance();
                return;
            }
            syntax_error("No closing parentheses");
            break;
        default:
            syntax_error("Unexpected token");
            break;
    }
}

static void rec_suite_seq_term(){
    token_t t;
    if ( !rec_op1(&t) )
        return;
    rec_term(); rec_suite_seq_term();
}

static void rec_suite_seq_factor(){
    token_t t;
    if ( !rec_op2(&t) )
        return;
    rec_factor(); rec_suite_seq_factor();
}

static int rec_op1(token_t* t){
    switch( current_lexeme().type ){
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            *t = current_lexeme().type;
            lexer_advance();
            return 1;
        default:
            return 0;
    }
}

static int rec_op2(token_t* t){
    switch( current_lexeme().type ){
        case TOKEN_MUL:
        case TOKEN_DIV:
            *t = current_lexeme().type;
            lexer_advance();
            return 1;
        default:
            return 0;
    }
}


static void syntax_error(const char* msg){
   FG_RED; 
   printf("Syntax error");
   FG_BG_RESET;
   printf(": \"%s\"\n",msg);
   printf("\t%s\n",current_lexeme().str);     
   printf("\t^^^\n");     
   printf("\tin line %d, ",current_lexeme().row);     
   printf("col %d\n" ,current_lexeme().col);     
   printf("\tin file \"%s\"\n",get_filename());     

   lexer_terminate();
}
