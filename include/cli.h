#pragma once
#include <stddef.h>
const char* VER = "v0.1";
typedef enum {
  CMD_HELP = 1,
  CMD_VERSION,
  CMD_INIT,
  CMD_ADD,
  CMD_DELETE,
  CMD_LIST,
  CMD_BACKUP,
  CMD_UNKNOWN,
} cmd_type_t;

typedef enum {
  SCP_DOT = 1,
  SCP_PKG,
  SCP_DEP,
  SCP_UNKNOWN,
} scp_type_t;

typedef struct {
  cmd_type_t cmd;
  scp_type_t scp;
  char**     args;
  size_t     argc;
} cli_command_t;

int        parse_args(int argc, char** argv, cli_command_t* result);
cmd_type_t extract_cmd(char* cmd);
scp_type_t extract_scp(char* scp);
int        extract_args(char* args, cli_command_t* result);

int cmd_help(cli_command_t cmd);
int cmd_version(cli_command_t cmd);
int cmd_init(cli_command_t cmd);
int cmd_add(cli_command_t cmd);
int cmd_delete(cli_command_t cmd);
int cmd_list(cli_command_t cmd);
int cmd_backup(cli_command_t cmd);
int cmd_unkonwn(cli_command_t cmd);

int execute_cmd(cli_command_t cmd);
