#include "./run.h"
#include "../core/parser.h"

void run(char * text, int textLength, char filename[]) {
    struct Lexer lexer;
    createLexer(&lexer, text, textLength, filename);
    tuple lexerGeneratedTokensResult = makeTokensLexer(&lexer);

    if (lexerGeneratedTokensResult.b.strval[0] == 'E') {
        printf("\033[0;31m%s \n", lexerGeneratedTokensResult.b.strval);
        exit(0);
    }

    printTokensList(&lexerGeneratedTokensResult.a.tlval, lexerGeneratedTokensResult.a.tlval.used);

    // Generate AST (Abstract Syntax Tree)
    struct Parser parser;
    createParser(&parser, lexerGeneratedTokensResult.a.tlval);
    // freeTokensList(&lexerGeneratedTokensResult.a.tlval);

    AST ast = createAST(AST_NULL);
    ast = runParser(&parser);

    // lexerGeneratedTokensResult.a.ast = &ast;
}