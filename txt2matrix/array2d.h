#pragma once

#include "array_int.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct array2d_t {
    size_t size;
    array_int_t const **data;
} array2d_t;

array2d_t *array2d_create(void);

size_t array2d_push(array2d_t *restrict, array_int_t const *restrict);

inline void array2d_print(array2d_t *array) {
    for (size_t i = 0; i < array->size; ++i)
        array_int_print((array_int_t *)array->data[i]);
}

inline void array2d_free(array2d_t *array) {
    for (size_t i = 0; i < array->size; ++i)
        array_int_free((array_int_t *)array->data[i]);
    free(array->data);
    free(array);
}
