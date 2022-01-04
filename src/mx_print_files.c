#include "uls.h"

bool mx_print_files(t_list *dirs, char *flag) {
    DIR *curr;
    int counter = 0;
    int have_files = 0;
    t_list *printing = NULL;
    t_list *big_printing = NULL;

    while (dirs != NULL) {
        if (!dirs->data) {
            dirs = dirs->next;
            continue;
        }
        curr = opendir(dirs->data);
        if (errno == ENOTDIR && curr == NULL) {
            have_files = 1;
            errno = 0;
            if (!mx_strchr(flag, 'l')) {
                mx_push_back(&printing, mx_strdup(dirs->data));
            } else {
                mx_push_back(&big_printing, mx_list_file_long(dirs->data, &counter));
            }
            dirs->data = NULL;
        }
        dirs = dirs->next;
    }

    if (have_files) {
        mx_long_col_print(big_printing);
        mx_colum_print(printing);
        mx_del_list(&printing);
        mx_del_list(&big_printing);
    }

    return have_files;
}
