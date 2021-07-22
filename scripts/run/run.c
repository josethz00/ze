#include "./run.h"

tuple run(char * text, int textLength, char filename[]) {
    struct Lexer lexer;
    createLexer(&lexer, text, textLength, filename);
    tuple lexerGeneratedTokensResult = makeTokensLexer(&lexer);
    return lexerGeneratedTokensResult;
}
