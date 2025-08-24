#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_args(int argc, char** argv, cli_command_t* result) {
  result->cmd  = 0;
  result->scp  = 0;
  result->args = NULL;
  result->argc = 0;
  for (int i = 0; i < argc; i++) {
    if (i == 0) {
      result->cmd = extract_cmd(argv[0]);
    } else if (i == 1) {
      result->scp = extract_scp(argv[1]);
    } else if (i >= 2) {
      result->args = &argv[2];
      result->argc = argc - 2;
    }
  }
  return EXIT_SUCCESS;
}

cmd_type_t extract_cmd(char* cmd) {
  if (!(strcmp("help", cmd))) {
    return CMD_HELP;
  }
  if (!(strcmp("version", cmd))) {
    return CMD_VERSION;
  }
  if (!(strcmp("init", cmd))) {
    return CMD_INIT;
  }
  if (!(strcmp("add", cmd))) {
    return CMD_ADD;
  }
  if (!(strcmp("delete", cmd))) {
    return CMD_DELETE;
  }
  if (!(strcmp("list", cmd))) {
    return CMD_LIST;
  }
  if (!(strcmp("backup", cmd))) {
    return CMD_BACKUP;
  }
  return CMD_UNKNOWN;
}

scp_type_t extract_scp(char* scp) {
  if (!(strcmp("dot", scp))) {
    return SCP_DOT;
  }
  if (!(strcmp("dep", scp))) {
    return SCP_DEP;
  }
  if (!(strcmp("pkg", scp))) {
    return SCP_PKG;
  }
  return SCP_UNKNOWN;
}

int cmd_help(cli_command_t cmd) {
  if (cmd.scp == 0) {
    printf("Use without arguments");
  }

  printf("Usage: dotman <command> [subcommand] [options]\n\n");

  printf("Commands:\n");
  printf("  help        Show this help message\n");
  printf("  version     Show the program version\n");
  printf("  init        Initialize on new system\n");
  printf("  add         Add a new resource (requires subcommand)\n");
  printf("  delete      Delete a resource (requires subcommand)\n");
  printf("  list        List resources (requires subcommand)\n");
  printf("  backup      Backup the dotfile (requires name of dotfile)\n\n");

  printf("Subcommands (for add/delete/list):\n");
  printf("  dot         Operate on dot files\n");
  printf("  pkg         Operate on packages\n");
  printf("  dep         Operate on dependencies\n\n");

  return EXIT_SUCCESS;
}

int cmd_version(cli_command_t cmd) {
  if (cmd.scp == 0) {
    printf("%s\n", VER);
  }
  return EXIT_SUCCESS;
}

int execute_cmd(cli_command_t cmd) {
  switch (cmd.cmd) {
    case CMD_HELP:
      cmd_help(cmd);
      break;
    case CMD_VERSION:
      cmd_version(cmd);
      break;
    case CMD_INIT:
      cmd_init(cmd);
      break;
    case CMD_ADD:
      cmd_add(cmd);
      break;
    case CMD_DELETE:
      cmd_delete(cmd);
      break;
    case CMD_LIST:
      cmd_list(cmd);
      break;
    case CMD_BACKUP:
      cmd_backup(cmd);
      break;
    case CMD_UNKNOWN:
      cmd_unkonwn(cmd);
      break;
  }
  return EXIT_SUCCESS;
}
