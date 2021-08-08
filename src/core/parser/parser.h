#ifndef PARSER
#define PARSER

#include "../lexer/lexer.h"

typedef struct {
    Token token;
    int isInitialized;
} NumberNode;

void createNumberNode(NumberNode * node, Token token);
char * reprNumberNode(NumberNode node);

typedef struct BIN_OP_NODE BinaryOperationNode;

typedef struct BIN_OP_NODE {
    BinaryOperationNode * leftNode;
    Token operatorToken;
    BinaryOperationNode * rightNode;
    NumberNode numericNode;
    int isInitialized;
} BinaryOperationNode;

void createBinaryOperationNode(BinaryOperationNode * node, BinaryOperationNode * leftNode, Token operatorToken, BinaryOperationNode * rightNode);
char * reprBinaryOperationNode(BinaryOperationNode node);

struct Parser {
    TokensList list;
    int tokenIndex;
    Token currentToken;
};

Token advanceParser(struct Parser * parser);
void createParser(struct Parser * parser, TokensList tokens);

#endif
