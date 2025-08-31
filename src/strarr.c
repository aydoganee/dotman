#include "strarr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StrArr *strarr_create() {
    StrArr *arr = malloc(sizeof(StrArr));
    if (!arr) {
        return nullptr;
    }

    arr->data = (char **) malloc(sizeof(char *) * INITIAL_CAPACITY);
    if (!arr->data) {
        free(arr);
        return nullptr;
    }

    arr->length   = 0;
    arr->capacity = INITIAL_CAPACITY;

    arr->add = strarr_add_fn;
    arr->del = strarr_del_fn;
    arr->pop = strarr_pop_fn;

    return arr;
}

void strarr_destroy(StrArr *arr) {
    if (!arr) {
        return;
    }
    for (size_t i = 0; i < arr->length; i++) {
        free(arr->data[i]);
    }
    free((void *) arr->data);
    free(arr);
}

bool strarr_add_fn(StrArr *arr, const char *str) {
    if (!arr || !str) {
        return false;
    }
    if (arr->capacity == arr->length) {
        size_t new_capacity = arr->capacity * 2;
        char **new_data     = (char **) realloc((void *) arr->data, sizeof(char *) * new_capacity);
        if (!new_data) {
            return false;
        }
        arr->data     = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->length] = strdup(str);
    if (!arr->data[arr->length]) {
        return false;
    }
    arr->length++;
    return true;
}

char *strarr_pop_fn(StrArr *arr) {
    if (!arr || arr->length == 0) {
        return nullptr;
    }
    arr->length--;
    char *str              = arr->data[arr->length];
    arr->data[arr->length] = nullptr;

    return str;
}

bool strarr_del_fn(StrArr *arr, size_t index) {
    if (!arr || index >= arr->length) {
        return false;
    }

    free(arr->data[index]);
    size_t tail = arr->length - index - 1;  // elements after index
    if (tail) {
        memmove((void *) arr->data[index], (const void *) arr->data[index + 1],
                tail * sizeof *arr->data);
    }

    arr->length--;
    arr->data[arr->length] = nullptr;

    return true;
}
