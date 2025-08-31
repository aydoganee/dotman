#ifndef STRUCTARR_H
#define STRUCTARR_H

#include <stddef.h>
#include <stdbool.h>
#define INITIAL_CAPACITY 10

typedef struct StructArr {
    void*  data;
    size_t length;
    size_t capacity;
    size_t element_size;
    bool (*add)(struct StructArr* self, const void* element);
    bool (*pop)(struct StructArr* self, void* out);
    bool (*del)(struct StructArr* self, size_t index);
} StructArr;

StructArr* structarr_create(size_t element_size);
void       structarr_destroy(StructArr* arr);

bool structarr_add_fn(StructArr* arr, const void* element);
bool structarr_pop_fn(StructArr* arr, void* out);
bool structarr_del_fn(StructArr* arr, size_t index);

#endif
