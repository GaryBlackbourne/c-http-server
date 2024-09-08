#include "argument.h"
#include "stdlib.h"
#include "assert.h"
#include "errno.h"
#include "string.h"
#include "common.h"

int get_integer_value(const Argument *arg, int32_t *value) {
    assert(arg != NULL);
    assert(value != NULL);

    errno = 0;

    if (arg->type != Integer) {
        errno = EINVAL;
        return -1;
    }

    int len = strnlen(arg->value, ARGUMENT_VALUE_LENGTH);
    if (len == ARGUMENT_VALUE_LENGTH) {
        errno = EINVAL;
        return -1;
    }

    str_to_i32(arg->value, len, value);

    if (errno != 0) {
        return -1;
    } else {
        return 0;
    }
}

int get_string_value(const Argument* arg, char* value) {
    assert(arg != NULL);
    assert(value != NULL);

    if (arg->type != String) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;

    strncpy(value, arg->value, ARGUMENT_VALUE_LENGTH);
    
    return 0;
}

int get_float_value(const Argument* arg, float* value) {
    assert(arg != NULL);
    assert(value != NULL);

    if (arg->type != Float) {
        errno = EINVAL;
        return -1;
    }

    int len = strnlen(arg->value, ARGUMENT_VALUE_LENGTH);
    if (len == ARGUMENT_VALUE_LENGTH) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;
    
    str_to_float(arg->value, len, value);

    if (errno != 0) {
        return -1;
    } else {
        return 0;
    }
}

Argument create_argument(const char *key, const ArgumentType type) {
    assert(key != NULL);
    Argument a = {
        .type = type,
        .key = {0},
        .value = {0}
    };
    memcpy((char*) a.key, key, ARGUMENT_KEY_LENGTH);
    return a;
}

Argument copy_argument(const Argument* arg) {
    assert(arg != NULL);
    Argument a = create_argument(arg->key, arg->type);
    memcpy((char*)a.value, (char*)arg->value, strlen(arg->value) + 1);
    return a;
}

/*
int check_argument(const Argument* arg) {
    assert(arg != NULL);

    int ival;
    float fval;
    char sval[ARGUMENT_VALUE_LENGTH];

    switch(arg->type) {
    case Integer:
        if (get_integer_value(arg, &ival) == 0) {
            return 0;
        }
        break;
    case Float:
        if (get_float_value(arg, &fval) == 0) {
            return 0;
        }
        break;
    case String:
        // char* cast discards a warning. Is it good this way?
        if (get_string_value(arg, (char*)&sval) == 0) {
            return 0;
        }
        break;
    default:
    return -1;
    }
    return -1;
}
*/
