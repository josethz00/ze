#ifndef PARSER
#define PARSER

#include "./lexer.h"

struct Parser {
    TokensList list;
    int tokenIndex;
    Token currentToken;
};

void createParser(struct Parser * parser, TokensList tokens);
AST factorParser(struct Parser * parser);
AST termParser(struct Parser * parser);
AST exprParser(struct Parser * parser);
AST runParser(struct Parser * parser);

#endif
