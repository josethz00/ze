#include "./keywords-constants.h"
#include <stdio.h>
#include <string.h>

const char * KW_NUMBER = "number";
const char * KW_BOOLEAN = "boolean";
const char * KW_STRING = "string";
const char * KW_UNDEFINED = "undefined";
const char * KW_FN = "fn";
const char * KW_PRINT = "print";
const char * KW_DO = "do";
const char * KW_END = "end";

int isKeyword(char * value) {

  // if strcmp returns a falsy value the strings are equal
  while (
    !strcmp(value, KW_NUMBER) ||
    !strcmp(value, KW_BOOLEAN) ||
    !strcmp(value, KW_STRING) ||
    !strcmp(value, KW_UNDEFINED) ||
    !strcmp(value, KW_FN) ||
    !strcmp(value, KW_PRINT) ||
    !strcmp(value, KW_DO) ||
    !strcmp(value, KW_END)
  ) {
    return 1;
  }
  return 0;
}