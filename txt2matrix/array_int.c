#include "array2d.h"
#include "utils.h"

#define ARRAY_BASE_SIZE 5

array_int_t *array_int_create() {
    array_int_t *array = malloc(sizeof(array_int_t));
    
    array->size = 0;
    array->data = malloc(sizeof(int64_t[ARRAY_BASE_SIZE]));
    
    return array;
}

size_t array_int_push(array_int_t *array, int64_t item) {
    array->data[array->size++] = item;
    
    // array size exceeded
    if (array->size % 5 == 0)
        array->data = realloc_safe(array->data, sizeof(int64_t) * (array->size + ARRAY_BASE_SIZE), __func__);

    return array->size;
}

extern inline void array_int_print(array_int_t *);

extern inline void array_int_free(array_int_t *);
