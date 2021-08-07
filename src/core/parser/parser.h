#ifndef PARSER
#define PARSER

#include "../lexer/lexer.h"

typedef struct {
    Token token;
    int isInitialized;
} NumberNode;

void createNumberNode(NumberNode * node, Token token);

char * reprNumberNode(NumberNode node);

struct GenericNode;

typedef struct {
    struct GenericNode * leftNode;
    Token operatorToken;
    struct GenericNode * rightNode;
    int isInitialized;
} BinaryOpertionNode;

struct GenericNode 
{
    NumberNode numericNode;
    BinaryOpertionNode * binaryOpertionNode;
};

void createBinaryOpertionNode(BinaryOpertionNode * node, struct GenericNode * leftNode, Token operatorToken, struct GenericNode * rightNode);

char * reprBinaryOpertionNode(BinaryOpertionNode node);

struct Parser {
    TokensList list;
    int tokenIndex;
    Token currentToken;
};  

Token advanceParser(struct Parser * parser);

void createParser(struct Parser * parser, TokensList tokens);

struct GenericNode factorParser(struct Parser * parser);

struct GenericNode termParser(struct Parser * parser);

BinaryOpertionNode exprParser(struct Parser * parser);

#endif
