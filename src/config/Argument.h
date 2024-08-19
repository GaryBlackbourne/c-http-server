#ifndef _BALU_ARGUMENT_H
#define _BALU_ARGUMENT_H

#define ARGUMENT_KEY_LENGTH   25
#define ARGUMENT_VALUE_LENGTH 25

#include <stdint.h>

typedef enum ArgumentType {

    Integer = 1,
    Float   = 2,
    String  = 3,

} ArgumentType;

typedef struct Argument {

    const char key[ARGUMENT_KEY_LENGTH];
    char value[ARGUMENT_VALUE_LENGTH];
    const ArgumentType type;

} Argument;

int get_integer_value(const Argument* arg, int32_t* value);
int get_string_value(const Argument* arg, char* value);
int get_float_value(const Argument* arg, float* value);

int check_argument(const Argument* arg);

Argument create_argument(const char* key, const ArgumentType type);
Argument copy_argument(const Argument* arg);


#endif
