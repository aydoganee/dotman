#include "cli.h"

#include <stdio.h>
#include <string.h>

#include "strarr.h"

bool parse_args(int argc, char** argv, CliCmd* result) {
    if (!result) {
        return false;
    }
    result->cmd  = CMD_NONE;
    result->scp  = SCP_NONE;
    result->args = nullptr;
    result->argc = 0;

    for (int i = 1; i < argc; i++) {
        if (i == 1) {
            result->cmd = extract_cmd(argv[i]);
        } else if (i == 2) {
            result->scp = extract_scp(argv[i]);
        } else if (i == 3) {
            result->args = strarr_create();
            if (!result->args) {
                return false;
            }
            result->args->add(result->args, argv[i]);
            result->argc++;
        } else if (i > 3) {
            result->args->add(result->args, argv[i]);
            result->argc++;
        }
    }
    return true;
}

CmdType extract_cmd(const char* cmd) {
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

ScpType extract_scp(const char* scp) {
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

bool cmd_help(CliCmd* cmd) {
    if (cmd->scp != SCP_NONE) {
        fprintf(stderr, "Help per-scope not implemented\n");
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

    return true;
}

bool cmd_version(CliCmd* cmd) {
    if (cmd->scp != 0) {
        fprintf(stderr, "Use without scope.\n");
        return false;
    }
    printf("%s\n", DOTMAN_VERSION);
    return true;
}

bool cmd_init(CliCmd* cmd) {
    if (cmd->scp != SCP_NONE) {
        fprintf(stderr, "Use without scope.\n");
        return false;
    }
    printf("cmd_init function executed\n");
    return true;
}

bool cmd_add(CliCmd* cmd) {
    if (cmd->scp == 0) {
        fprintf(stderr, "Use with a scope");
        return false;
    }
    printf("cmd_add function executed. Scope: %d\n", cmd->scp);
    return true;
}

bool cmd_delete(CliCmd* cmd) {
    if (cmd->scp == 0) {
        fprintf(stderr, "Use with a scope");
        return false;
    }
    printf("cmd_delete function executed. Scope: %d\n", cmd->scp);
    return true;
}
bool cmd_list(CliCmd* cmd) {
    if (cmd->scp == 0) {
        printf("cmd_list function executed. Used with no scope");
        return false;
    }
    printf("cmd_list function executed. Scope: %d\n", cmd->scp);
    return true;
}
bool cmd_backup(CliCmd* cmd) {
    if (cmd->scp != SCP_NONE) {
        fprintf(stderr, "Use without scope.\n");
        return false;
    }
    printf("cmd_backup function executed\n");
    return true;
}
bool cmd_unkonwn() {
    fprintf(stderr, "Unkown command.\n");
    printf("Check help.\n");
    return true;
}

bool execute_cmd(CliCmd* cmd) {
    switch (cmd->cmd) {
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
            cmd_unkonwn();
            break;
        case CMD_NONE:
            break;
    }
    return true;
}
