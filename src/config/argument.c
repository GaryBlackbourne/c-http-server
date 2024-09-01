#include "argument.h"
#include "stdlib.h"
#include "assert.h"
#include "errno.h"
#include "string.h"

int get_integer_value(const Argument *arg, int32_t *value) {
    assert(arg != NULL);
    assert(value != NULL);

    if (arg->type != Integer) {
        return -1;
    }

    errno = 0;
    int ret = strtol(arg->value, NULL, 10);
    if (errno != 0) {
        return -1;
    } else {
        (*value) = ret;
        return 0;
    }
}

int get_string_value(const Argument* arg, char* value) {
    assert(arg != NULL);
    assert(value != NULL);

    if (arg->type != String) {
        return -1;
    }

    strncpy(value, arg->value, ARGUMENT_VALUE_LENGTH);
    
    return 0;
}

int get_float_value(const Argument* arg, float* value) {
    assert(arg != NULL);
    assert(value != NULL);

    if (arg->type != Float) {
        return -1;
    }

    errno = 0;
    int ret = strtof(arg->value, NULL);
    if (errno != 0) {
        return -1;
    } else {
        (*value) = ret;
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
    return a;
}

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
