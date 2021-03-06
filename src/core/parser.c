#include "./parser.h"

Token advanceParser(struct Parser * parser) {
  parser->tokenIndex += 1;
  if (parser->tokenIndex < parser->list.used) {
    parser->currentToken = parser->list.list[parser->tokenIndex];
  }
  return parser->currentToken;
}

void createParser(struct Parser * parser, TokensList tokens) {
  initTokensList(&parser->list);
  parser->list = tokens;
  parser->tokenIndex = -1;
  advanceParser(parser);
}

AST factorParser(struct Parser * parser) {
  AST astFactor = createAST(AST_NULL);
  Token token = parser->currentToken;
  if (
    !strcmp(parser->currentToken.type, TT_INT) || 
    !strcmp(parser->currentToken.type, TT_FLOAT)
  ) {
    printf("\n value -> %s \n", token.value);
    advanceParser(parser);
    astFactor.type = !strcmp(token.type, TT_INT) ? AST_INT : AST_FLOAT;
    astFactor.numericValue = token.value;
  }
  return astFactor;
}

AST termParser(struct Parser * parser) {
  AST left = createAST(AST_NULL);
  left = factorParser(parser);

  Token token = parser->currentToken;

  while(
    !strcmp(parser->currentToken.type, TT_MUL) ||
    !strcmp(parser->currentToken.type, TT_DIV)
  ) {
    advanceParser(parser);
    AST right = createAST(AST_NULL); 
    right = factorParser(parser);
    left.left = &left;
    left.operatorValue = token.value;
    left.right = &right;
  }
  return left;
}

AST exprParser(struct Parser * parser) {
  AST left = createAST(AST_NULL); 
  left = termParser(parser);

  Token token = parser->currentToken;

  while(
    !strcmp(parser->currentToken.type, TT_PLUS) ||
    !strcmp(parser->currentToken.type, TT_MINUS)
  ) {
    advanceParser(parser);
    AST right = createAST(AST_NULL); 
    right = termParser(parser);
    left.left = &left;
    left.operatorValue = token.value;
    left.right = &right;
  }

  return left;
}

AST runParser(struct Parser * parser) {
  return exprParser(parser);
}
