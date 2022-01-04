#include "uls.h"

static bool is_unique(t_list *uniqs, char c) {
    while (uniqs != NULL) {
        if (*(char *) (uniqs->data) == c)
            return false;
        uniqs = uniqs->next;
    }
    return true;
}

static char *list_to_str(t_list *uniqs) {
    int size = mx_list_size(uniqs);
    char *res = mx_strnew(size);
    for (int i = 0; i < size; i++) {
        res[i] = *(char *) (uniqs->data);
        uniqs = uniqs->next;
    }
    return res;
}
