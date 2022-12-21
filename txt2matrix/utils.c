//
//  utils.c
//  txt2matrix
//
//  Created by mahdi farnia on 9/30/1401 AP.
//

#include "utils.h"

#include <stdlib.h>

void *realloc_safe(void *restrict ptr, size_t size, char const *restrict fn_name) {
    void *temp = realloc(ptr, size);

    if(temp) return temp;
    
    perror(fn_name);
    exit(EXIT_FAILURE);
}
