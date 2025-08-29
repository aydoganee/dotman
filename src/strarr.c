#include "strarr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StrArr *strarr_create(size_t initial_capacity) {
    StrArr *arr = malloc(sizeof(StrArr));
    if (!arr) {
        return nullptr;
    }

    arr->data = (char **) malloc(sizeof(char *) * initial_capacity);
    if (!arr->data) {
        free(arr);
        return nullptr;
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

int strarr_add(StrArr *arr, const char *str) {
    if (!arr || !str) {
        return 0;
    }
    if (arr->capacity == arr->length) {
        size_t new_capacity = arr->capacity * 2;
        char **new_data     = (char **) realloc((void *) arr->data, sizeof(char *) * new_capacity);
        if (!new_data) {
            return 0;
        }
        arr->data     = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->length] = strdup(str);
    if (!arr->data[arr->length]) {
        return 0;
    }
    arr->length++;
    return 1;
}

char *strarr_pop(StrArr *arr) {
    if (!arr || arr->length == 0) {
        return nullptr;
    }
    arr->length--;
    char *str = arr->data[arr->length];
    free(arr->data[arr->length]);

    return str;
}

int strarr_delete(StrArr *arr, size_t index) {
    if (!arr || index <= arr->length) {
        return 0;
    }
    free(arr->data[index]);

    for (size_t i = index; i < arr->length - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    free(arr->data[arr->length - 1]);
    arr->length--;

    return 1;
}
