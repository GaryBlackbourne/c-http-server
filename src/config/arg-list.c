#include "arg-list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

ArgumentListElement* create_argument_list_element(Argument* arg) {
    ArgumentListElement* element
        = (ArgumentListElement*)malloc(sizeof(ArgumentListElement));
    if (element) {
        element->next     = NULL;
        element->prev     = NULL;
        element->argument = arg;
    }
    return element;
}

void push_argument_list_element(ArgumentList* arglist,
                                       ArgumentListElement* element) {
    assert(arglist != NULL);
    assert(element != NULL);

    element->prev = NULL;
    element->next = NULL;

    ArgumentListElement* current = arglist->list;
    if (current == NULL) {
        current = element;
        return;
    }

    while (current->next != NULL) { current = current->next; }
    current->next = element;
    element->prev = current;

    return;
}

int remove_argument_list_element(ArgumentList* arglist,
                                        ArgumentListElement* target) {
    assert(arglist != NULL);
    assert(target != NULL);

    ArgumentListElement* current = arglist->list;
    if (current == NULL) {
        return -1;
    }

    if (current == target) {
        arglist->list       = current->next;
        current->next->prev = arglist->list;
        free(current);
    }

    int found = 0;
    while (current->next != NULL) {
        current = current->next;
        if (current == target) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return -1;
    }

    ArgumentListElement* p = current->prev;
    ArgumentListElement* n = current->next;

    p->next = n;
    if (n != NULL) {
        n->prev = p;
    }

    free(current);

    return 0;
}

// interface------------------------------------

ArgumentList create_argument_list() {
    ArgumentList list = {
        .list = NULL,
    };
    return list;
}

int destroy_argument_list(ArgumentList* listp) {
    assert(listp != NULL);
    if (listp->list == NULL) {
        return 0;
    }

    ArgumentListElement* current = listp->list;
    while (current->next != NULL) {
        current = current->next;
        free(current->prev);
    }
    free(current);

    return 0;
}

int add_argument(ArgumentList* arglist, Argument* arg) {
    assert(arglist != NULL);
    assert(arg != NULL);

    ArgumentListElement* current = arglist->list;
    if (current == NULL) {
        arglist->list = create_argument_list_element(arg);
    }

    push_argument_list_element(arglist, create_argument_list_element(arg));

    return 0;
}

int find_argument(const ArgumentList* arglist, const char* key,
                  const Argument** result) {
    assert(arglist != NULL);
    assert(key != NULL);
    assert(result != NULL);

    unsigned target_key_len = strlen(key);
    (*result)               = NULL;

    // dummy starter for indexing
    ArgumentListElement cur = {
        .next = arglist->list,
    };
    ArgumentListElement* current = &cur;

    while (current->next != NULL) {

        current = current->next;

        unsigned element_key_len = strlen(current->argument->key);

        if ((element_key_len == target_key_len)
            && (0 == strncmp(key, current->argument->key, target_key_len))) {
            (*result) = (current->argument);
            return 0;
        }
    }
    return -1;
}

int remove_argument(ArgumentList* arglist, const char* target_key) {
    assert(arglist != NULL);
    assert(target_key != NULL);

    const Argument* target;
    int res = find_argument(arglist, target_key, &target);

    if (res != 0) {
        return -1;
    }
    
    ArgumentListElement* current        = arglist->list;
    ArgumentListElement* target_element = NULL;

    if (current->argument == target) {
        remove_argument_list_element(arglist, current);
    }

    while (current->next != NULL) {
        current = current->next;
        if (current->argument == target) {
            target_element = current;
            break;
        }
    }

    if ( target_element != NULL) {
        remove_argument_list_element(arglist, target_element);
    } else {
        return -1; // imposible
    }

    return 0;
}
