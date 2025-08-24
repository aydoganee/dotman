#include "cli.h"

#include <string.h>

int parse_args(int argc, char** argv, cli_arg_t* result) {
  result->cmd  = extract_cmd(argv[1]);
  result->scp  = extract_scp(argv[2]);
  result->args = &argv[3];
  result->argc = argc - 2;
  return 0;
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
