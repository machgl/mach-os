#pragma once

typedef unsigned long size_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char byte;

size_t strlen(const char* string) {

    size_t length;

    while(string[length] != '\0') length++;

    return length;
}

byte port_byte_in(unsigned short port) {

    byte result; 
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, byte data) {

    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port) {

    unsigned short result; 
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data) {

    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}