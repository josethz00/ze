#include "./shell.h"

void shell() {
  for(;;) {
    printf("\033[1;32mze>  \033[0m");
    tuple input = read_stdin();
    run(input.a.strval, input.b.ival, "<stdin>");
  }
}
