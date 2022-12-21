//
//  utils.h
//  txt2matrix
//
//  Created by mahdi farnia on 9/30/1401 AP.
//

#pragma once

#include <stdio.h>

#define eprintf(msg, ...) fprintf(stderr, msg, __VA_ARGS__)

void *realloc_safe(void *restrict, size_t, char const *restrict);
