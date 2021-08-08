#include "./parser.h"

void createNumberNode(NumberNode * node, Token token) {
   node->token = token;
   node->isInitialized = 1;
}

char * reprNumberNode(NumberNode node) {
    return reprToken(node.token);
}

void createBinaryOperationNode(BinaryOperationNode * node, struct GenericNode * leftNode, Token operatorToken, struct GenericNode * rightNode) {
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
            + sizeof(node.leftNode));
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

struct GenericNode factorParser(struct Parser * parser) {
    struct GenericNode newNumNode;
    if (!strcmp(parser->currentToken.type, TT_INT) || !strcmp(parser->currentToken.type, TT_FLOAT)) {
        advanceParser(parser); 
        createNumberNode(&newNumNode.numericNode, parser->currentToken);
        printf("\n factor initialized \n");
        return newNumNode;
    }
    return newNumNode;
}

struct GenericNode termParser(struct Parser * parser) {
    struct GenericNode left = factorParser(parser);
    struct GenericNode term;
    if (left.numericNode.isInitialized) {
        while (!strcmp(parser->currentToken.type, TT_MUL) || !strcmp(parser->currentToken.type, TT_DIV)) {
            Token operatorToken = parser->currentToken;
            advanceParser(parser);
            struct GenericNode right = factorParser(parser);
            if (right.numericNode.isInitialized) {
                createBinaryOperationNode(term.binaryOperationNode, &left, operatorToken, &right);
            }
            printf("\n term initialized \n");
        }
    }
    if (term.binaryOperationNode->isInitialized) {
        printf("\n aaaaaauuuuuu \n");
        return term;
    }
    printf("\n aaaaaauuuuuu \n");
    return left;
}

BinaryOperationNode exprParser(struct Parser * parser) {
    struct GenericNode left = termParser(parser);
    BinaryOperationNode term;
    if (left.binaryOperationNode->isInitialized || left.numericNode.isInitialized) {
        while (!strcmp(parser->currentToken.type, TT_PLUS) || !strcmp(parser->currentToken.type, TT_MINUS)) {
            Token operatorToken = parser->currentToken;
            advanceParser(parser);
            struct GenericNode right = factorParser(parser);
            if (right.binaryOperationNode->isInitialized || right.numericNode.isInitialized) {
                createBinaryOperationNode(&term, &left, operatorToken, &right);
                printf("\n expr initialized \n");
            }
        }
    }
    return term;
}

BinaryOperationNode runParser(struct Parser * parser) {
    BinaryOperationNode result = exprParser(parser);
    return result;
}
