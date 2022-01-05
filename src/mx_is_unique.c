#include "uls.h"

bool mx_is_unique(t_list *unique, char c) {
    while (unique != NULL) {
        if (*(char *) (unique->data) == c)
            return false;
        unique = unique->next;
    }
    return true;
}
