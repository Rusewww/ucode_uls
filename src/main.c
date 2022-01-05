#include "uls.h"

int main(int argc, char **argv) {
    char *flag;
    int current = 0;
    int left = 0;
    int i = 1;
    t_list *dirs;
    t_list *tmp;

    mx_args_check(argc, argv);

    t_list *uniques = NULL;
    while (i < argc && argv[i][0] == '-') {
        for (int j = 1; argv[i][j] != '\0'; j++) {
            if (mx_is_unique(uniques, argv[i][j])) {
                mx_push_front(&uniques, &argv[i][j]);
            }
        }
        i++;
    }

    flag = mx_list_to_str(uniques);
    mx_del_list(&uniques);

    argc--;
    argv++;

    while (argc > 0 && (*argv)[0] == '-') {
        argv++;
        argc--;
    }

    i = 0;

    while (i < argc) {
        mx_push_back(&dirs, argv[i]);
        i++;
    }

    mx_sort_list(dirs, &mx_by_lex);

    mx_validate_dirs(dirs);

    /*if (mx_print_files(dirs, flag)) {
        tmp = dirs;
        while (tmp && !left) {
            if (tmp->data) {
                left = true;
            }
            tmp = tmp->next;
        }
        if (left)
            mx_printchar('\n');
    }*/

    if (mx_print_files(dirs, flag))
    {
        tmp = dirs;
        while (tmp && !left)
        {
            if (tmp->data)
                left = true;
            tmp = tmp->next;
        }
        if (left)
            mx_printchar('\n');
    }

    current = dirs == NULL;

    if (current) {
        mx_push_front(&dirs, ".");
    }

    current = current || mx_list_size(dirs) == 1;
    tmp = dirs;
    mx_sort_list(dirs, &mx_by_lex);
    mx_sort_list(dirs, &mx_by_null);

    while (tmp) {
        if (tmp->data != NULL) {
            if (!current) {
                mx_printstr(tmp->data);
                mx_printstr(":\n");
            }
            if (!mx_list_dir_content(tmp->data, flag) && tmp->next) {
                mx_printchar('\n');
            }
        }
        tmp = tmp->next;
    }

    free(flag);
    mx_del_list(&dirs);
    return errno != 0;
}
