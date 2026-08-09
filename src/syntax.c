#include "include/syntax.h"


void rec_expr(Ast*);

void rec_term(Ast*);
void rec_factor(Ast*);

void rec_seq_term(Ast*);
void rec_suite_seq_term(Ast*,Ast);

void rec_seq_factor(Ast*);
void rec_suite_seq_factor(Ast*,Ast);

int rec_op1(OperationType*);
int rec_op2(OperationType*);

static void syntax_error(const char* msg);


void init_syntax(char* filename){
    init_lexer(filename);
    lexer_advance();
}


void interpret(Ast* A){
    rec_expr(A);
    if ( !lexer_done() ){
        syntax_error("Program didn't terminate correctly");
    }
}

void rec_expr(Ast* A){
    rec_seq_term(A);
}

void rec_term(Ast* A){
    rec_seq_factor(A);
}

void rec_seq_term(Ast* A){
    Ast A1 = NULL;
    rec_term(&A1); rec_suite_seq_term(A,A1);
}

void rec_suite_seq_term(Ast* A, Ast Al){
    OperationType op;
    Ast A1 = NULL, Ar = NULL;
    if ( !rec_op1(&op) ){
        *A = Al;
        return;
    }
    rec_term(&Ar);
    A1 = create_operation(op,Al,Ar);
    rec_suite_seq_term(A,A1);
}


void rec_factor(Ast* A){
    int i; float f;
    switch( current_lexeme().type ){
        case TOKEN_INT:
            i = current_lexeme().ival;
            *A = create_const(VAL_INT,&i);
            lexer_advance();
            break;
        case TOKEN_FLOAT:
            f = current_lexeme().fval;
            *A = create_const(VAL_FLT,&f);
            lexer_advance();
            break;
        default:
            syntax_error("Unexpected token");
            break;
    }
}

void rec_seq_factor(Ast* A){
    Ast A1 = NULL;
    rec_factor(&A1); rec_suite_seq_factor(A,A1);
}

void rec_suite_seq_factor(Ast* A, Ast Al){
    OperationType op;
    Ast A1 = NULL, Ar = NULL;
    if ( !rec_op2(&op) ){
        *A = Al;
        return;
    }
    rec_factor(&Ar);
    A1 = create_operation(op,Al,Ar);
    rec_suite_seq_factor(A,A1);
}

int rec_op1(OperationType* op){
    switch(current_lexeme().type){
        case TOKEN_PLUS:
            *op = OP_ADD;
            break;
        case TOKEN_MINUS:
            *op = OP_SUB;
            break;
        default:
            return 0;
    }
    lexer_advance();
    return 1;
}

int rec_op2(OperationType* op){
    switch(current_lexeme().type){
        case TOKEN_MUL:
            *op = OP_MUL;
            break;
        case TOKEN_DIV:
            *op = OP_DIV;
            break;
        default:
            return 0;
    }
    lexer_advance();
    return 1;
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
