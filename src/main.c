#include "uls.h"

int main(int argc, char **argv) {
    char *flags;
    int currentjust = 0;
    int left = 0;
    t_list *direct;
    t_list *tmp;
    mx_validate_args(argc, argv);
    flags = mx_extract_flags(argc, argv);
    direct = mx_extract_dirs(argc, argv);
    mx_sort_list(direct, &mx_by_lex);
    mx_validate_dirs(direct);
    if (mx_printfiles(direct, flags)) {
        tmp = direct;
        while (tmp && !left) {
            if (tmp->data) {
                left = true;
            }
            tmp = tmp->next;
        }
        if (left == 1) {
            mx_printchar('\n');
        }
    }
    currentjust = direct == NULL;
    if (currentjust) {
        mx_push_front(&direct, ".");
    }
    currentjust = currentjust || mx_list_size(direct) == 1;
    tmp = direct;
    mx_sort_list(direct, &mx_by_lex);
    mx_sort_list(direct, &mx_by_null);
    while (tmp) {
        if (tmp->data != NULL) {
            if (!currentjust) {
                mx_printstr(tmp->data);
                mx_printstr(":\n");
            }
            if (!mx_list_dir_content(tmp->data, flags) && tmp->next)
                mx_printchar('\n');
        }
        tmp = tmp->next;
    }
    free(flags);
    mx_del_list(&direct);
    return errno != 0;
}
