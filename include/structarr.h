#ifndef STRUCTARR_H
#define STRUCTARR_H

#include <stddef.h>
#define INITIAL_CAPACITY 10

typedef struct StructArr {
    void*  data;
    size_t length;
    size_t capacity;
    size_t element_size;
    int (*add)(struct StructArr* self, void* element);
    void (*pop)(struct StructArr* self, void* out);
    int (*delete)(struct StructArr* self, size_t index);
} StructArr;

StructArr* structarr_create(size_t element_size);
void       structarr_destroy(StructArr* arr);

int  structarr_add_fn(StructArr* arr, void* element);
void structarr_pop_fn(StructArr* arr, void* out);
int  structarr_delete_fn(StructArr* arr, size_t index);

#endif
