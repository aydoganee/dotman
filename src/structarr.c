#include "structarr.h"

#include <stdlib.h>
#include <string.h>

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

int structarr_add_fn(StructArr* arr, void* element) {
    if (!arr || !element) {
        return 0;
    }

    if (arr->capacity == arr->length) {
        size_t new_capacity = arr->capacity * 2;
        void*  new_data     = realloc(arr->data, arr->element_size * new_capacity);
        if (!new_data) {
            return 0;
        }
        arr->data     = new_data;
        arr->capacity = new_capacity;
    }
    memcpy((unsigned char*) arr->data + (arr->length * arr->element_size), element,
           arr->element_size);
    arr->length++;

    return 1;
}

void structarr_pop_fn(StructArr* arr, void* out) {
    if (!arr || !out || arr->length == 0) {
        return;
    }
    arr->length--;
    unsigned char* src = (unsigned char*) arr->data + (arr->length * arr->element_size);
    memcpy(out, src, arr->element_size);
    memset(src, 0, arr->element_size);
}
