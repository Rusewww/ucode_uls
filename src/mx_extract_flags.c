#include "uls.h"

bool mx_is_unique(t_list *unique, char c) {
    while (unique != NULL) {
        if (*(char *) (unique->data) == c)
            return false;
        unique = unique->next;
    }
    return true;
}

char *mx_list_to_str(t_list *list) {
    int size = mx_list_size(list);
    char *res = mx_strnew(size);
    for (int i = 0; i < size; i++) {
        res[i] = *(char *) (list->data);
        list = list->next;
    }
    return res;
}
