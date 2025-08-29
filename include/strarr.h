#ifndef STRARR_H
#define STRARR_H

#include <stddef.h>
#define INITIAL_CAPACITY 10

typedef struct StrArr {
    char **data;
    size_t length;
    size_t capacity;
    int (*add)(struct StrArr *self, const char *str);
    int (*delete)(struct StrArr *self, size_t index);
    char *(*pop)(struct StrArr *self);
} StrArr;

StrArr *strarr_create();
void    strarr_destroy(StrArr *arr);

int   strarr_add_fn(StrArr *arr, const char *str);
char *strarr_pop_fn(StrArr *arr);
int   strarr_delete_fn(StrArr *arr, size_t index);

#endif
