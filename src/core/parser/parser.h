#ifndef PARSER
#define PARSER

#include "../lexer/lexer.h"

void createNumberNode(NumberNode * node, Token token);

char * reprNumberNode(NumberNode node);
void createBinaryOperationNode(BinaryOperationNode * node, struct GenericNode * leftNode, Token operatorToken, struct GenericNode * rightNode);

char * reprBinaryOperationNode(BinaryOperationNode node);

struct Parser {
    TokensList list;
    int tokenIndex;
    Token currentToken;
};  

Token advanceParser(struct Parser * parser);

void createParser(struct Parser * parser, TokensList tokens);

struct GenericNode factorParser(struct Parser * parser);

struct GenericNode termParser(struct Parser * parser);

BinaryOperationNode exprParser(struct Parser * parser);
BinaryOperationNode runParser(struct Parser * parser);

#endif
