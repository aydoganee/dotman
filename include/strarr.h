#ifndef STRARR_H
#define STRARR_H

#include <stddef.h>
#include <stdbool.h>
#define INITIAL_CAPACITY 10

typedef struct StrArr {
    char **data;
    size_t length;
    size_t capacity;
    bool (*add)(struct StrArr *self, const char *str);
    bool (*del)(struct StrArr *self, size_t index);
    char *(*pop)(struct StrArr *self);
} StrArr;

StrArr *strarr_create();
void    strarr_destroy(StrArr *arr);

bool   strarr_add_fn(StrArr *arr, const char *str);
bool   strarr_del_fn(StrArr *arr, size_t index);
char *strarr_pop_fn(StrArr *arr);

#endif
