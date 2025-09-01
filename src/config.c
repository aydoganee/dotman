#include "config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

bool ensure_capacity(char **buf, size_t *cap, size_t needed) {
    if (!buf || !*buf || !cap) {
        return false;
    }
    if (needed < *cap) {
        return true;
    }
    size_t new_cap = (*cap) * 2;
    while (new_cap <= needed) {
        new_cap *= 2;
    }
    char *tmp = realloc(*buf, new_cap);
    if (!tmp) {
        return false;
    }
    *buf = tmp;
    *cap = new_cap;
    return true;
}
