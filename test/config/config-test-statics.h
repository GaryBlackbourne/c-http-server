#ifndef _CONFIG_TEST_STATICS_H
#define _CONFIG_TEST_STATICS_H

#include "argument.h"
#include "arg-list.h"

ArgumentListElement* create_argument_list_element(Argument* arg);

void push_argument_list_element(ArgumentList* arglist, ArgumentListElement* element);

int remove_argument_list_element(ArgumentList* arglist,
                                 ArgumentListElement* target);

#endif
