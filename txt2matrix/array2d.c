#include "array2d.h"
#include <stdarg.h>
#include "utils.h"

#define ARRAY_2D_BASE_SIZE 5

array2d_t *array2d_create() {
    array2d_t *array = malloc(sizeof(array2d_t));
    
    array->size = 0;
    array->data = malloc(sizeof(array_int_t *[ARRAY_2D_BASE_SIZE]));
    
    return array;
}

size_t array2d_push(array2d_t *restrict array, array_int_t const *restrict item) {
    array->data[array->size++] = item;
    
    // array size exceeded
    if (array->size % 5 == 0)
        array->data = realloc_safe(array->data, sizeof(array_int_t *) * (array->size + ARRAY_2D_BASE_SIZE), __func__);

    return array->size;
}

extern inline void array2d_print(array2d_t *);

extern inline void array2d_free(array2d_t *);
