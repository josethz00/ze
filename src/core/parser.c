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
  parser->tokenIndex = 1;
  advanceParser(parser);
}
