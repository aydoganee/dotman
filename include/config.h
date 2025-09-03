#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>
#include <stdio.h>

#include "cli.h"
#include "strarr.h"
#include "structarr.h"

#define INIT_FIELD_CAP 64
#define INIT_ARR_CAP 32

typedef struct ConfigLine {
    ScpType scp;
    StrArr *fields;
    StrArr *array;
} ConfigLine;

bool ensure_capacity(char **buf, size_t *cap, size_t needed);
bool parse_line(ConfigLine *line, FILE *file_p);
bool parse_config(StructArr *lines, const char *file);

#endif
