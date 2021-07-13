#include "./parser.h"

void createNumberNode(NumberNode * node, Token token) {
   node->token = token;
   node->isInitialized = 1;
}

char * reprNumberNode(NumberNode node) {
    return reprToken(node.token);
}

void createBinaryNode(BinaryNode * node, struct GenericNode * leftNode, Token operatorToken, struct GenericNode * rightNode) {
    node->leftNode = leftNode;
    node->operatorToken = operatorToken;
    node->rightNode = rightNode;
    node->isInitialized = -1;
}

char * reprBinaryNode(BinaryNode node) {
    char * returnValue = (char*)malloc(sizeof(node.rightNode) 
            + sizeof(node.operatorToken) 
            + sizeof(node.leftNode));
    sprintf(
            returnValue, "%s %s %s", 
            reprToken(node.leftNode.numericNode.token), 
            reprToken(node.operatorToken), 
            reprToken(node.rightNode.numericNode.token)
    );
    return returnValue;
}

Token advanceParser(struct Parser * parser) {
    parser->tokenIndex += 1;
    if (parser->tokenIndex < parser->list.used) {
        parser->currentToken = parser->list.list[parser->tokenIndex];
    }
    return parser->currentToken;
}

void createParser(struct Parser * parser, TokensList tokens) {
    parser->list = tokens;
    parser->tokenIndex = 1;
    advanceParser(parser);
}

struct GenericNode factorParser(struct Parser * parser) {
    struct GenericNode newNumNode;
    if (parser->currentToken.type == TT_INT || parser->currentToken.type == TT_FLOAT) {
        advanceParser(parser); 
        createNumberNode(&newNumNode, parser->currentToken);
        return newNumNode;
    }
    return newNumNode;
}

struct GenericNode termParser(struct Parser * parser) {
    struct GenericNode left = factorParser(parser);
    struct GenericNode term;
    if (left.numericNode.isInitialized) {
        while (parser->currentToken.type == TT_MUL || parser->currentToken.type == TT_DIV) {
            Token operatorToken = parser->currentToken;
            advanceParser(parser);
            struct GenericNode right = factorParser(parser);
            if (right.numericNode.isInitialized) {
                createBinaryNode(&term, left, operatorToken, right);
            }
        }
    }
    return term;
}

BinaryNode exprParser(struct Parser * parser) {
    struct GenericNode left = termParser(parser);
    BinaryNode term;
    if (left.binaryNode.isInitialized || left.numericNode.isInitialized) {
        while (parser->currentToken.type == TT_PLUS || parser->currentToken.type == TT_MINUS) {
            Token operatorToken = parser->currentToken;
            advanceParser(parser);
            struct GenericNode right = factorParser(parser);
            if (right.binaryNode.isInitialized || right.numericNode.isInitialized) {
                createBinaryNode(&term, left, operatorToken, right);
            }
        }
    }
    return term;
}
