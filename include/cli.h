#pragma once
#include <stddef.h>
typedef enum
{
  CMD_HELP = 0,
  CMD_VERSION,
  CMD_INIT,
  CMD_ADD,
  CMD_DELETE,
  CMD_LIST,
  CMD_BACKUP,
  CMD_UNKNOWN,
} cmd_type_t;

typedef enum
{
  SCP_DOT = 0,
  SCP_PKG,
  SCP_DEP,
  SCP_UNKNOWN,
} scp_type_t;

typedef struct
{
  cmd_type_t cmd;
  scp_type_t scp;
  char**     args;
  size_t     argc;
} cli_arg_t;

int        parse_args(int argc, char** argv, cli_arg_t* result);
cmd_type_t extract_cmd(char* cmd);
scp_type_t extract_scp(char* scp);
int        extract_args(char* args, cli_arg_t* result);
