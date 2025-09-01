#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>
#include <stdio.h>

#include "cli.h"
#include "strarr.h"

#define INITAL_FIELD_LEN 128

typedef struct ConfigLine {
    ScpType scp;
    StrArr  fields;
    StrArr  array;
} ConfigLine;

bool ensure_capacity(char **buf, size_t *cap, size_t needed);
bool read_file(ConfigLine **lines, FILE *file_p);
bool parse_config(ConfigLine *result, const char *file);

#endif
