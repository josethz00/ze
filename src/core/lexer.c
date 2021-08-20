#include "./lexer.h"

void advanceLexer(struct Lexer * lexer) {
    advancePosition(&lexer->position, lexer->currentChar);
    lexer->currentChar = (char) ((lexer->position.index < lexer->text.used) ? lexer->text.list[lexer->position.index] : '\0');
}

void createLexer(struct Lexer * lexer, char text[], int arrLength, char filename[]) {
    initCharList(&lexer->text);
    appendStringCharList(&lexer->text, text, arrLength);
    strcpy(lexer->filename, filename);
    createPosition(&lexer->position, -1, 0, -1, lexer->filename, lexer->text.list, arrLength);
    advanceLexer(lexer);
}

Token makeNumberLexer(struct Lexer *lexer) {
    CharList numberString;
    unsigned int dotCount = 0;
    size_t ttDigitsLen = strlen(DIGITS);
    Token numericToken;

    char * TT_DIGITS_WITH_DOT = malloc((ttDigitsLen + 1 + 1) * sizeof(char));

    strcpy(TT_DIGITS_WITH_DOT, DIGITS);
    TT_DIGITS_WITH_DOT[ttDigitsLen] = '.';
    TT_DIGITS_WITH_DOT[ttDigitsLen + 1] = '\0';

    initCharList(&numberString);

    while (lexer->currentChar != '\0' &&
           strchr(TT_DIGITS_WITH_DOT, lexer->currentChar) != NULL
            ) {
        if (lexer->currentChar == '.') {
            if (dotCount == 1) {
                break;
            }
            dotCount +=1;
            appendCharList(&numberString, lexer->currentChar);
        } else {
            appendCharList(&numberString, lexer->currentChar);
        }
        advanceLexer(lexer);
    }
    if (dotCount == 0) {
        createToken(&numericToken, TT_INT, numberString.list);
        return numericToken;
    }
    createToken(&numericToken, TT_INT, numberString.list);

    free(TT_DIGITS_WITH_DOT);
    TT_DIGITS_WITH_DOT = NULL;

    return numericToken;
}

Token makeIdentifierLexer(struct Lexer *lexer) {
    CharList identifierString;
    size_t ttLettersLen = strlen(LETTERS);
    size_t ttDigitsLen = strlen(DIGITS);
    Token numericToken;

    char * IDENTIFIER_CHARACTERS = (char *)malloc((ttDigitsLen + ttLettersLen + 1 + 1) * sizeof(char));

    sprintf(IDENTIFIER_CHARACTERS, "%s%s%c%c", LETTERS, DIGITS, '_', '\0');

    initCharList(&identifierString);

    while (
        lexer->currentChar != '\0' 
        && 
        strchr(IDENTIFIER_CHARACTERS, lexer->currentChar) != NULL
    ) {
        appendCharList(&identifierString, lexer->currentChar);
        advanceLexer(lexer);
    }

    char tokenType[20];

    if (isKeyword(identifierString.list)) {
        strcpy(tokenType, TT_KEYWORD);
    } else {
        strcpy(tokenType, TT_IDENTIFIER);
    }

    createToken(&numericToken, tokenType, identifierString.list);

    free(IDENTIFIER_CHARACTERS);
    IDENTIFIER_CHARACTERS = NULL;

    return numericToken;
}

tuple makeTokensLexer(struct Lexer * lexer) {
    TokensList tokens;
    initTokensList(&tokens);
    Token lToken;
    Error lexError;
    tuple lexTokensReturn;

    while (lexer->currentChar != '\0') {
        if (lexer->currentChar == ' ' || lexer->currentChar == '\t') {
            advanceLexer(lexer);
        } else if (strchr(DIGITS, lexer->currentChar) != NULL) {
            appendTokensList(&tokens, makeNumberLexer(lexer));
        } else if (strchr(LETTERS, lexer->currentChar) != NULL) {
		    appendTokensList(&tokens, makeIdentifierLexer(lexer));
        } else if(lexer->currentChar == '=') {
            createToken(&lToken, TT_EQUAL, "=");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == '+') {
            createToken(&lToken, TT_PLUS, "+");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == ',') {
            createToken(&lToken, TT_COMA, ",");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == '-') {
            createToken(&lToken, TT_MINUS, "-");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == '*') {
            createToken(&lToken, TT_MUL, "*");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == '/') {
            createToken(&lToken, TT_DIV, "*");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == '(') {
            createToken(&lToken, TT_LPAREN, "(");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == ')') {
            createToken(&lToken, TT_RPAREN, ")");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if (lexer->currentChar == ':') {
            createToken(&lToken, TT_COLON, ":");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else if(lexer->currentChar == '>') {
            createToken(&lToken, TT_RIGHT, ">");
            appendTokensList(&tokens, lToken);
            advanceLexer(lexer);
        } else {
            Position positionStart = copyPosition(&lexer->position);
            const char errorMsg[] = "Error <Illegal Character>" ;
            size_t errorMsgLen = sizeof(errorMsg) / sizeof(* errorMsg);
            char * stringError = (char *)malloc(errorMsgLen * sizeof(char) + 1 + 1);

            sprintf(stringError, "%s %c", errorMsg, lexer->currentChar);
            createError(&lexError, positionStart, positionStart, stringError, "No details for this error");
            strcpy(lexTokensReturn.b.strval, reprAsStringError(lexError));
            
            free(stringError);

            return lexTokensReturn;
        }
    }
    lexTokensReturn.a.tlval = tokens;
    return lexTokensReturn;
}

tuple read_stdin () {
    char *userInput = (char *)malloc(1 * sizeof(char));
    int c;
    int length = 0;
    while((c = getchar()) != '\n' && c != EOF)
    {
        userInput = realloc(userInput, length+1);
        userInput[length++] = c;
    }
    userInput[length] = '\0';

    tuple returnValue;
    strcpy(returnValue.a.strval, userInput);
    returnValue.b.ival = length;

    free(userInput);

    return returnValue;
}