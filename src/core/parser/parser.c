#include "./parser.h"

void createNumberNode(NumberNode *node, Token token) {
    node->token = token;
    node->isInitialized = 1;
}
char * reprNumberNode(NumberNode node) {
    return reprToken(node.token);
}
void createBinaryOperationNode(BinaryOperationNode * node, BinaryOperationNode * leftNode, Token operatorToken, BinaryOperationNode * rightNode) {
    node = (BinaryOperationNode*)malloc(sizeof(&rightNode) 
            + sizeof(&operatorToken) 
            + sizeof(&leftNode));
    node->leftNode = leftNode;
    node->operatorToken = operatorToken;
    node->rightNode = rightNode;
    node->isInitialized = 1;
}
char * reprBinaryOperationNode(BinaryOperationNode node) {
    char * returnValue = (char*)malloc(sizeof(node.rightNode) 
            + sizeof(node.operatorToken) 
            + sizeof(node.leftNode) + 1);
    sprintf(
            returnValue, "%s %s %s", 
            reprToken(node.leftNode->numericNode.token), 
            reprToken(node.operatorToken), 
            reprToken(node.rightNode->numericNode.token)
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
    initTokensList(&parser->list);
    parser->list = tokens;
    parser->tokenIndex = 1;
    advanceParser(parser);
}