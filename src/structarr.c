#include "structarr.h"

#include <stdlib.h>

StructArr* structarr_create(size_t element_size) {
    if (element_size == 0) {
        return nullptr;
    }
    StructArr* arr = malloc(sizeof(StructArr));
    if (!arr) {
        return nullptr;
    }

    arr->data = malloc(INITIAL_CAPACITY * element_size);
    if (!arr->data) {
        free(arr);
        return nullptr;
    }

    arr->length       = 0;
    arr->capacity     = INITIAL_CAPACITY;
    arr->element_size = element_size;

    arr->add    = structarr_add_fn;
    arr->pop    = structarr_pop_fn;
    arr->delete = structarr_delete_fn;

    return arr;
}

void structarr_destroy(StructArr* arr) {
    if (!arr) {
        return;
    }
    free(arr->data);
    free(arr);
}
