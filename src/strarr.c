#include "strarr.h"

#include <stdlib.h>

StrArr *strarr_create(size_t initial_capacity) {
    StrArr *arr = malloc(sizeof(StrArr));
    if (!arr) {
        return NULL;
    }

    arr->data = (char **) malloc(sizeof(char *) * initial_capacity);
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->length   = 0;
    arr->capacity = initial_capacity;

    return arr;
}

void strarr_destroy(StrArr *arr) {
    for (size_t i = 0; i < arr->length; i++) {
        free(arr->data[i]);
    }
    free((void *) arr->data);
    free(arr);
}
