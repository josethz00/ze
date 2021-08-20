#include "./types.h" 

// CharList functions *********************************************************

/**
 * Initializes a CharList
 * @param l the CharList to be initialized
*/
void initCharList(CharList *l) {
  size_t initialSize = 10;
  l->list = (char*)malloc((initialSize+1) * sizeof(char)); 
  l->used = 0;
  l->size = initialSize;
}

/**
 * Appends new elements to a CharList
 * @param l the CharList to be appended to
 * @param element the char to be appended
*/
void appendCharList(CharList *l, char element) {
  if (l->used == l->size) {
    l->size += 2;
    l->list = realloc(l->list, l->size);
  }
  l->list[l->used++] = element;
  l->list[l->used] = '\0';
}

/**
 * Appends multiple characters by once to a CharList
 * @param l the CharList to be appended to
 * @param element the string to be appended
*/
void appendStringCharList(CharList *l, char elements[], int arr_length) {
  if (l->used + arr_length >= l->size) {
    l->size += arr_length + 1;
    l->list = realloc(l->list, l->size * sizeof(char *) + 1);
  }
  for (int i = 0; i < arr_length; i++) {
    l->list[l->used++] = elements[i];
    l->list[l->used] = '\0';
  }
}

/**
 * Frees the memory allocated to a CharList
 * @param l the CharList to be freed 
 * */
void freeCharList(CharList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

// StringList functions *******************************************************

/**
 * Initializes a StringList
 * @param l the StringList to be initialized
*/
void initStringList(StringList *l) {
  size_t initialSize = 10;
  l->list = malloc((initialSize + 1) * sizeof(char *));
  l->used = 0;
  l->size = initialSize;
}

/**
 * Appends string (char[]) to a StringList
 * @param l the StringList to be appended to
 * @param elements the string to be appended
*/
void appendStringList(StringList *l, char element[]) {
  if (l->used == l->size) {
    l->size += 1;
    l->list = realloc(l->list, l->size * sizeof(char *) + 1);
  }
  l->list[l->used++] = element;
}

/**
 * Frees the memory allocated to a StringList
 * @param l the StringList to be freed 
 * */
void freeStringList(StringList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

// Position functions *********************************************************

/**
 * Initializes a Position
 * @param position the Position to be initialized
 * @param index the index of the Position
 * @param ln the line number of the Position
 * @param col the column number of the Position
 * @param filename[] the filename of the Position
 * @param fileText the text of the file
 * @param fileTextLength the length of the file text
*/
void createPosition(Position *position, int index, int ln, int col, char filename[], char fileText[], int fileTextLength) {
  position->index = index;
  position->ln = ln;
  position->col = col;
  position->fileTextLength = fileTextLength;
  strcpy(position->filename, filename);
  initCharList(&position->fileText);
  appendStringCharList(&position->fileText, fileText, position->fileTextLength);
}

/**
 * Advances the position to next char, column and line
 * @param position the Position to be advanced
 * @param currentChar the current char
 * @returns the advanced Position
*/
Position * advancePosition(Position *position, char currentChar) {
  position->index += 1;
  position->col += 1;

  if (currentChar == '\n') {
    position->ln += 1;
    position->col = 0;
  }
  return position;
}

/**
 * Copies the position and returns it
 * @param position the Position to be copied
 * @returns the copied Position
*/
Position copyPosition(Position * position) {
  Position positionCopy;
  createPosition(&positionCopy, position->index, position->ln, position->col, position->filename, position->fileText.list, position->fileTextLength);
  return positionCopy;
}

// Error functions ************************************************************

/**
 * Initializes an Error
 * @param error the Error to be initialized
 * @param positionStart the start position of the Error
 * @param positionEnd the end position of the Error
 * @param errorName the name of the Error
 * @param details the details of the Error
*/
void createError(Error *error, Position positionStart, Position positionEnd, char errorName[], char details[]) {
  error->positionStart = positionStart;
  error->positionEnd = positionEnd;
  strcpy(error->errorName, errorName);
  strcpy(error->details, details);
}

/**
 * Represent an Error as a string
 * @param error the Error to be represented
 * @returns a char pointer that is the representation of the Error 
*/
char *reprAsStringError(Error error) {
  const int totalStructSize = sizeof(Error);
  char *returnValue = (char *) malloc((totalStructSize+1) * sizeof(char));
  sprintf(returnValue, "%s: %s \n at file %s and line %d", error.errorName, error.details, error.positionStart.filename, error.positionStart.ln + 1);
  return returnValue;
}

// Token functions ************************************************************

/**
 * Initializes a Token
 * @param token the Token to be initialized
 * @param type the type of the Token
 * @param value the value of the Token
*/
void createToken(Token *token, const char * type, char * value) {
  strcpy(token->type, type);
  strcpy(token->value, value);
}

/**
 * Represents a Token as a string
 * @param token the Token to be represented
 * @returns a char pointer that is the representation of the Token
*/
char * reprToken(Token token) {
  const int typeFieldSize = sizeof(token.type);
  const int valueFieldSize = sizeof(token.value);
  const int totalStructSize = typeFieldSize + valueFieldSize;
  char * returnValue = (char*)malloc((totalStructSize+1) * sizeof(char));
  if (strlen(token.value) == 0) {
    sprintf(returnValue, "%s, %s", token.type, token.value);
    return returnValue;
  }
  sprintf(returnValue, "%s, %s", token.type, token.value);
  return returnValue;
}

// TokensList functions *******************************************************

/**
 * Initializes a TokensList
 * @param l the TokensList to be initialized
*/
void initTokensList(TokensList *l) {
  size_t initialSize = 10;
  l->list = (Token*)malloc((initialSize + 1) * sizeof(Token));
  l->used = 0;
  l->size = initialSize;
}

/**
 * Appends a Token to a TokensList
 * @param l the TokensList to be appended to
 * @param element the Token to be appended
*/
void appendTokensList(TokensList *l, Token element) {
  if (l->used == l->size) {
    l->size += 1;
    l->list = realloc(l->list, l->size * sizeof(Token) + 1);
  }
  l->list[l->used++] = element;
}

/**
 * Frees the memory allocated to a TokensList
 * @param l the TokensList to be freed
*/
void freeTokensList(TokensList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

/**
 * Prints the entire TokensList (iterates over the list and prints each Token)
 * @param l the TokensList to be printed
 * @param tokensListLen the length of the TokensList
*/
void printTokensList(TokensList *l, size_t tokensListLen) {
  size_t listIndex;
  for (listIndex = 0; listIndex < tokensListLen; listIndex++) {
    printf("[ %s ] ", reprToken(l->list[listIndex]));
  }
  printf("\n");
}

// AST functions **************************************************************

/**
 * Initializes an AST
 * @param type the integer enum type of the AST
 * @returns the initialized AST
*/
AST createAST(int type){
  AST * ast = (AST*)malloc(1 * sizeof(struct AST_STRUCT));
  ast->type = type;

  /*if (type == AST_COMPOUND)
    ast->children = init_list(sizeof(struct AST_STRUCT*));*/

  return *ast;
}