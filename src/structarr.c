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

    arr->add = structarr_add_fn;
    arr->pop = structarr_pop_fn;
    arr->del = structarr_del_fn;

    return arr;
}

void structarr_destroy(StructArr* arr) {
    if (!arr) {
        return;
    }
    free(arr->data);
    free(arr);
}

bool structarr_add_fn(StructArr* arr, const void* element) {
    if (!arr || !element) {
        return false;
    }

    if (arr->capacity == arr->length) {
        size_t new_capacity = arr->capacity * 2;
        void*  new_data     = realloc(arr->data, arr->element_size * new_capacity);
        if (!new_data) {
            return false;
        }
        arr->data     = new_data;
        arr->capacity = new_capacity;
    }
    memcpy((unsigned char*) arr->data + (arr->length * arr->element_size), element,
           arr->element_size);
    arr->length++;

    return true;
}

bool structarr_pop_fn(StructArr* arr, void* out) {
    if (!arr || !out || arr->length == 0) {
        return EXIT_FAILURE;
    }
    arr->length--;
    memcpy(out, (unsigned char*) arr->data + (arr->length * arr->element_size), arr->element_size);
    return EXIT_SUCCESS;
}

bool structarr_del_fn(StructArr* arr, size_t index) {
    if (!arr || index >= arr->length) {
        return false;
    }
    size_t trailing = arr->length - 1 - index;
    if (trailing > 0) {
        unsigned char* base = (unsigned char*) arr->data;
        unsigned char* dest = base + (index * arr->element_size);
        unsigned char* src  = dest + arr->element_size;
        memmove(dest, src, trailing * arr->element_size);
    }
    arr->length--;

    return true;
}
