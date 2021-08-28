#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
// CharList type **************************************************************

typedef struct {
  char * list;
  size_t used;
  size_t size;
} CharList;

void initCharList(CharList *l);
void appendCharList(CharList *l, char element);
void appendStringCharList(CharList *l, char elements[], int arr_length);
void freeCharList(CharList *l);

// StringList type ************************************************************

typedef struct {
  char ** list;
  size_t used;
  size_t size;
} StringList;

void initStringList(StringList *l);
void appendStringList(StringList *l, char element[]);
void freeStringList(StringList *l);

// Position type **************************************************************

typedef struct {
  int index;
  int ln;
  int col;
  char filename[200];
  CharList fileText;
  int fileTextLength;
} Position;

void createPosition(Position *position, int index, int ln, int col, char filename[], char fileText[], int fileTextLength);
Position * advancePosition(Position *position, char currentChar);
Position copyPosition(Position * position);

// Error type *****************************************************************

typedef struct {
    char errorName[30];
    char details[100];
    Position positionStart;
    Position positionEnd;
} Error;

void createError(Error *error, Position positionStart, Position positionEnd, char errorName[], char details[]);
char * reprAsStringError(Error error);

// Token type *****************************************************************

typedef struct {
  char type[20];
  char value[100];
} Token;

void createToken(Token *token, const char * type, char * value);

// TokensList type ************************************************************

typedef struct {
  Token * list;
  size_t used;
  size_t size;
} TokensList;

void initTokensList(TokensList *l);
void appendTokensList(TokensList *l, Token element);
char * reprToken(Token token);
void printTokensList(TokensList *l, size_t tokensListLen);
void freeTokensList(TokensList *l);

// AST type *******************************************************************

typedef struct AST_STRUCT {
  enum {
    AST_COMPOUND,
    AST_FUNCTION,
    AST_CALL_FUNCTION,
    AST_ASSIGNMENT,
    AST_DEFINITION_TYPE,
    AST_VARIABLE,
    AST_STATEMENT_RETURN,
    AST_INT,
    AST_FLOAT,
    AST_BIN_OP_NODE,
    AST_NULL,
  } type;
  struct AST_STRUCT * value;
  struct AST_STRUCT * left;
  struct AST_STRUCT * right;
  char * operatorValue;
  char * numericValue;
} AST;

AST createAST(int type);

// tuple type *****************************************************************

typedef struct 
{
  union {
    int ival;
    float fval;
    char cval;
    char strval[200];
    TokensList tlval;
    AST * ast;
  } a;
  union {
    int ival;
    float fval;
    char cval;
    char strval[200];
    TokensList tlval;
    AST * ast;
  } b;
} tuple;

#endif