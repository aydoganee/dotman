#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h>
#define INITIAL_CAPACITY 10

typedef struct StructApp {
    void*  data;
    size_t length;
    size_t capacity;
    size_t element_size;
} StructArr;

StructArr* structarr_create(size_t element_size);
void       structarr_destroy(StructArr* arr);

int   structarr_add_fn(StructArr* arr, void* element);
void* structarr_pop_fn(StructArr* arr);
int   structarr_delete_fn(StructArr* arr, size_t index);

#endif  // !STRUCT_H
