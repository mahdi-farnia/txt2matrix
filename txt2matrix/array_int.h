#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct array_int_t {
    size_t size;
    int64_t *data;
} array_int_t;

array_int_t *array_int_create(void);

size_t array_int_push(array_int_t *array, int64_t item);

inline void array_int_print(array_int_t *array) {
    printf("[ ");
    for (size_t i = 0; i < array->size; ++i)
        printf("%lld ", array->data[i]);
    printf("]\n");
}

inline void array_int_free(array_int_t *array) {
    free(array->data);
    free(array);
}
