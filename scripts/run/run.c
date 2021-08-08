#include "./run.h"
#include "../../src/core/parser/parser.h"

tuple run(char * text, int textLength, char filename[]) {
    struct Lexer lexer;
    createLexer(&lexer, text, textLength, filename);
    tuple lexerGeneratedTokensResult = makeTokensLexer(&lexer);

    if (lexerGeneratedTokensResult.b.strval[0] == 'E') {
        printf("\033[0;31m%s \n", lexerGeneratedTokensResult.b.strval);
    }

    // Generate AST (Abstract Syntax Tree)
    struct Parser parser;
    createParser(&parser, lexerGeneratedTokensResult.a.tlval);
    BinaryOperationNode ast = runParser(&parser);

    lexerGeneratedTokensResult.a.ast = ast;

    return lexerGeneratedTokensResult;
}