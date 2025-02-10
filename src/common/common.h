#ifndef _BALU_COMMON_H
#define _BALU_COMMON_H

#include <stdint.h>

/**
 * @brief Find the bigger integer.
 *
 * @param a - int 
 * @param b - int 
 *
 * @return int the bigger number
 */
int imax(int a, int b);

/**
 * @brief Find the smaller integer.
 *
 * @param a - int 
 * @param b - int 
 *
 * @return int the smaller number
 */
int imin(int a, int b);

/**
 * @brief Covert string to an integer value.
 *
 * @param src - const char* pointer to the string.
 * @param len - uint32_t length of the string.
 * @param value - int32_t pointer where the result is stored.
 *
 * @return int indicating error or success. Upon success returns 0.
 *
 */
int str_to_i32(const char* src, uint32_t len, int32_t* value);

/**
 * @brief Covert string to a float value.
 *
 * @param src - const char* pointer to the string.
 * @param len - uint32_t length of the string.
 * @param value - float pointer where the result is stored.
 *
 * @return int indicating error or success. Upon success returns 0.
 */
int str_to_float(const char* src, uint32_t len, float* value);

#endif
