#include "./shell.h"

void shell() {
  for(;;) {
    printf("\033[1;32mze>  \033[0m");
    tuple input = read_stdin();
    tuple lexerGeneratedTokensResult = run(input.a.strval, input.b.ival, "<stdin>");

    if (lexerGeneratedTokensResult.b.strval[0] == 'E') {
      printf("\033[0;31m%s \n", lexerGeneratedTokensResult.b.strval);
    } else {
      printTokensList(&lexerGeneratedTokensResult.a.tlval, lexerGeneratedTokensResult.a.tlval.used);
    }
    freeTokensList(&lexerGeneratedTokensResult.a.tlval);
  }
}
