#include "./types.h" 

void initCharList(CharList *l) {
  size_t initialSize = 10;
  l->list = (char*)malloc((initialSize+1) * sizeof(char)); 
  l->used = 0;
  l->size = initialSize;
}

void appendCharList(CharList *l, char element) {
  if (l->used == l->size) {
    l->size += 2;
    l->list = realloc(l->list, l->size);
  }
  l->list[l->used++] = element;
  l->list[l->used] = '\0';
}

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

void freeCharList(CharList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

void initStringList(StringList *l) {
  size_t initialSize = 10;
  l->list = malloc((initialSize + 1) * sizeof(char *));
  l->used = 0;
  l->size = initialSize;
}

void appendStringList(StringList *l, char element[]) {
  if (l->used == l->size) {
    l->size += 1;
    l->list = realloc(l->list, l->size * sizeof(char *) + 1);
  }
  l->list[l->used++] = element;
}

void freeStringList(StringList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

void createPosition(Position *position, int index, int ln, int col, char filename[], char fileText[], int fileTextLength) {
  position->index = index;
  position->ln = ln;
  position->col = col;
  position->fileTextLength = fileTextLength;
  strcpy(position->filename, filename);
  initCharList(&position->fileText);
  appendStringCharList(&position->fileText, fileText, position->fileTextLength);
}

Position * advancePosition(Position *position, char currentChar) {
  position->index += 1;
  position->col += 1;

  if (currentChar == '\n') {
    position->ln += 1;
    position->col = 0;
  }
  return position;
}

Position copyPosition(Position * position) {
  Position positionCopy;
  createPosition(&positionCopy, position->index, position->ln, position->col, position->filename, position->fileText.list, position->fileTextLength);
  return positionCopy;
}

void createError(Error *error, Position positionStart, Position positionEnd, char errorName[], char details[]) {
  error->positionStart = positionStart;
  error->positionEnd = positionEnd;
  strcpy(error->errorName, errorName);
  strcpy(error->details, details);
}

char *reprAsStringError(Error error) {
  const int totalStructSize = sizeof(Error);
  char *returnValue = (char *) malloc((totalStructSize+1) * sizeof(char));
  sprintf(returnValue, "%s: %s \n at file %s and line %d", error.errorName, error.details, error.positionStart.filename, error.positionStart.ln + 1);
  return returnValue;
}

void createToken(Token *token, const char * type, char * value) {
  strcpy(token->type, type);
  strcpy(token->value, value);
}

void initTokensList(TokensList *l) {
  size_t initialSize = 10;
  l->list = (Token*)malloc((initialSize + 1) * sizeof(Token));
  l->used = 0;
  l->size = initialSize;
}

void appendTokensList(TokensList *l, Token element) {
  if (l->used == l->size) {
    l->size += 1;
    l->list = realloc(l->list, l->size * sizeof(Token) + 1);
  }
  l->list[l->used++] = element;
}

void freeTokensList(TokensList *l) {
  free(l->list);
  l->list = NULL;
  l->used = l->size = 0;
}

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

void printTokensList(TokensList *l, size_t tokensListLen) {
  size_t listIndex;
  for (listIndex = 0; listIndex < tokensListLen; listIndex++) {
    printf("[ %s ] ", reprToken(l->list[listIndex]));
  }
  printf("\n");
}

AST createAST(int type){
  AST * ast = (AST*)malloc(1 * sizeof(struct AST_STRUCT));
  ast->type = type;

  /*if (type == AST_COMPOUND)
    ast->children = init_list(sizeof(struct AST_STRUCT*));*/

  return *ast;
}