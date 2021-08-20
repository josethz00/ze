#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/tokens-constants.h"
#include "../constants/lexer-constants.h"
#include "../constants/keywords-constants.h"
#include "../utils/types.h"

struct Lexer {
  CharList text;
  Position position;
  char currentChar;
  char filename[];
};

void advanceLexer(struct Lexer * lexer);
void createLexer(struct Lexer * lexer, char text[], int arrLength, char filename[]);

Token makeNumberLexer(struct Lexer *lexer);
tuple makeTokensLexer(struct Lexer * lexer);
tuple read_stdin ();

#endif
