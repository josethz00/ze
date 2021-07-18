#include "./keywords-constants.h"
#include <stdio.h>
#include <string.h>

const char * KW_NUMBER = "number";
const char * KW_BOOLEAN = "boolean";
const char * KW_STRING = "string";
const char * KW_UNDEFINED = "undefined";

int isKeyword(char * value) {

  // if strcmp returns a falsy value the strings are equal
  while (
    !strcmp(value, KW_NUMBER) ||
    !strcmp(value, KW_BOOLEAN) ||
    !strcmp(value, KW_STRING) ||
    !strcmp(value, KW_UNDEFINED)
  ) {
    return 1;
  }
  return 0;
}