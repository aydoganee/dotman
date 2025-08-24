#include <cli.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no argument passed");
    return -1;
  }
  cli_command_t cmd;
  parse_args(argc - 1, &argv[1], &cmd);
  execute_cmd(cmd);
  return EXIT_SUCCESS;
}
