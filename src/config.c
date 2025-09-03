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

bool parse_line(ConfigLine *line, FILE *file_p) {
    if (!line || !file_p) {
        fprintf(stderr, "Error: Null parameter passed to read_line");
        return false;
    }

    size_t field_cap = INIT_FIELD_CAP;
    size_t elm_cap   = INIT_ARR_CAP;
    char  *field     = malloc(field_cap);
    char  *elm       = malloc(elm_cap);
    int    chr;
    bool   scp_parsed = false;
    bool   is_arr     = false;
    size_t len        = 0;

    chr = fgetc(file_p);
    while (chr != ';') {
        while (chr != ':') {
            ensure_capacity(&field, &field_cap, len + 3);
            if (chr == ',') {
                is_arr = true;
            }
            field[len++] = (char) chr;
            chr          = fgetc(file_p);
        }
        field[len] = '\0';
        if (!scp_parsed) {
            line->scp  = extract_scp(field);
            scp_parsed = true;
            chr        = fgetc(file_p);
            len        = 0;
            continue;
        }
        if (is_arr) {
            size_t fin = 0;
            size_t ein = 0;
            while (field[fin] != '\0') {
                ensure_capacity(&elm, &elm_cap, ein + 3);
                if (field[fin] == ',') {
                    elm[ein] = '\0';
                    line->array.add(&line->array, elm);
                    ein = 0;
                    fin++;
                }
                elm[ein++] = field[fin++];
            }
            is_arr = false;
            chr    = fgetc(file_p);
            len    = 0;
            continue;
        }
        line->fields.add(&line->fields, field);
        len = 0;
        chr = fgetc(file_p);
    }

    free(field);
    free(elm);
    return true;
}

