#ifndef STRARR_H
#define STRARR_H

#include <stddef.h>

typedef struct {
    char **data;
    size_t length;
    size_t capacity;
} StrArr;

StrArr *strarr_create(size_t initial_capacity);
void    strarr_destroy(StrArr *arr);

int   strarr_add(StrArr *arr, const char *str);
char *strarr_pop(StrArr *arr);
int   strarr_delete(StrArr *arr, size_t index);

#endif
