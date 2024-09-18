#ifndef _BALU_ARGPARSER_H
#define _BALU_ARGPARSER_H

#include "argument.h"

typedef struct ArgumentListElement {

    Argument argument;
    struct ArgumentListElement* next;
    struct ArgumentListElement* prev;

} ArgumentListElement;

typedef struct ArgumentList {

    ArgumentListElement* list;

} ArgumentList;

// interface
ArgumentList create_argument_list();
void destroy_argument_list(ArgumentList* list);

int add_argument(ArgumentList* list, Argument arg);
int find_argument(const ArgumentList* list, const char* string, const Argument** result);

int remove_argument(ArgumentList* list, const char* target_key); // do we need this?

#endif
