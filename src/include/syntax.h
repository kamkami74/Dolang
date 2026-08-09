#ifndef SYNTAX_H
#define SYNTAX_H

#include "lexer.h"
#include "utils.h"
#include "io.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void init_syntax(char* filename);

void interpret(Ast* A);

#endif
