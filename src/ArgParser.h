#ifndef _BALU_ARGPARSER_H
#define _BALU_ARGPARSER_H

#define ARGUMENT_KEY_LENGTH   25
#define ARGUMENT_VALUE_LENGTH 25

typedef enum ArgumentType {

    Integer = 1,
    Float   = 2,
    String  = 3,

} ArgumentType;

typedef struct Argument {

    const char key[ARGUMENT_KEY_LENGTH];
    const char value[ARGUMENT_VALUE_LENGTH];
    ArgumentType type;

} Argument;

typedef struct ArgumentListElement {

    Argument argument;
    struct ArgumentListElement* next;

} ArgumentListElement;

typedef struct ArgumentsList {

    ArgumentListElement* list;    
    
} ArgumentsList;

#endif
