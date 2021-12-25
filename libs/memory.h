#pragma once

#include "utils.h"

void byte_mem_cpy(byte* src, byte* dest, unsigned int num_of_bytes) {

    for (int i = 0; i < num_of_bytes; i++) {
        dest[i] = src[i];
    }
        //*(dest + i) = *(src + i);
}

void short_mem_cpy(short* src, short* dest, unsigned int num_of_bytes) {

    for (int i = 0; i < num_of_bytes; ++i)
        *(dest + i) = *(src + i);
}