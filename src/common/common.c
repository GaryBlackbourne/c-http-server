
#include "common.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int imin(int a, int b) {
    return (a < b) ? a : b;
}

int imax(int a, int b) {
    return (a > b) ? a : b;
}

int str_to_i32(const char *src, uint32_t len, int32_t *value) {
    assert(src != NULL);
    assert(value != NULL);

    if (len == 0) { return -1; }

    int      answer      = 0;
    int32_t place_value = 1;

    for(int32_t idx = len-1; idx > -1; idx --) {
        // check if character is an actual number
        int num = (src[idx] >= '0' && src[idx] <= '9') ? (src[idx] - '0') : -1;
        if (num == -1) { // bad character (non numeric) -> error
            errno = EINVAL;
            return -1;
        }
        answer += (num) * place_value; // shift number into place (decimal)
        place_value *= 10;             // 
    }

    (*value) = answer;
    return 0;
}

int str_to_float(const char* src, uint32_t len, float * value) {
    assert(src != NULL);
    assert(value != NULL);

    float    answer            = 0;
    uint32_t decimal           = len;

    int      multiple_decimals = -1;
    uint32_t bad_char          = 0;

    // check for bad characters or multiple decimals
    for (uint32_t i = 0; i < len; i++) {
        if (src[i] == '.' || src[i] == ',') {
            decimal = i;
            multiple_decimals++;
            if (multiple_decimals) {
                break;
            }
        } else {
            if (src[i] < '0' && src[i] > '9') {
                bad_char++;
                break;
            }
        }
    }
    if ((bad_char) || (multiple_decimals)) {
        errno = EINVAL;
        return -1;
    }

    // copy fraction and whole part into local buffers
    char * whole_part         = (char*) malloc (decimal + 1);
    char * fractional_part    = (char*) malloc (len - decimal + 1);

    strncpy(whole_part, src, decimal); 
    whole_part[decimal] = '\0';

    strncpy(fractional_part, src + decimal + 1, len - decimal);
    fractional_part[len - decimal] = '\0';

    // convert whole and fraction strings to integers
    int whole_part_int = 0;
    str_to_i32(whole_part, decimal, &whole_part_int);

    int fraction_part_int = 0;
    str_to_i32(fractional_part, len - decimal, &fraction_part_int);

    // generate answer
    answer = (float) (whole_part_int) +  ((float)fraction_part_int / (10*(len - decimal)));
    (*value) = answer;

    // clean up local buffers
    free(fractional_part);
    free(whole_part);

    return 0;
}
