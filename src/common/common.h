#ifndef _BALU_COMMON_H
#define _BALU_COMMON_H

#include <stdint.h>

int imax(int a, int b);

int imin(int a, int b);

int str_to_i32(const char* src, uint32_t len, int32_t* value);

int str_to_float(const char* src, uint32_t len, float* value);

#endif
