#ifndef CLI_H
#define CLI_H

#include <stdbool.h>
#include <stddef.h>

#include "strarr.h"

#define DOTMAN_VERSION "v0.1.0"
typedef enum {
    CMD_NONE = 0,
    CMD_HELP,
    CMD_VERSION,
    CMD_INIT,
    CMD_ADD,
    CMD_DELETE,
    CMD_LIST,
    CMD_BACKUP,
    CMD_UNKNOWN,
} CmdType;

typedef enum {
    SCP_NONE = 0,
    SCP_DOT,
    SCP_PKG,
    SCP_DEP,
    SCP_UNKNOWN,
} ScpType;

typedef struct {
    CmdType cmd;
    ScpType scp;
    StrArr* args;
    size_t  argc;
} CliCmd;

bool    parse_args(int argc, char** argv, CliCmd* result);
CmdType extract_cmd(const char* cmd);
ScpType extract_scp(const char* scp);

bool cmd_help(CliCmd* cmd);
bool cmd_version(CliCmd* cmd);
bool cmd_init(CliCmd* cmd);
bool cmd_sync(CliCmd* cmd);
bool cmd_add(CliCmd* cmd);
bool cmd_delete(CliCmd* cmd);
bool cmd_list(CliCmd* cmd);
bool cmd_backup(CliCmd* cmd);
bool cmd_unkonwn();

bool execute_cmd(CliCmd* cmd);

#endif  // !CLI_H
