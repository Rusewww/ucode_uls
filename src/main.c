#include "uls.h"

int main(int argc, char **argv) {
    char *flag;
    int curr = 0;
    int left_dir = 0;
    t_list *dirs;
    t_list *tmp;

    mx_args_check(argc, argv);

    t_list *uniques = NULL;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        for (int j = 1; argv[i][j] != '\0'; j++) {
            if (mx_is_unique(uniques, argv[i][j])) {
                mx_push_front(&uniques, &argv[i][j]);
            }
        }
    }
    flag = mx_list_to_str(uniques);
    mx_del_list(&uniques);

    argc--;
    argv++;
    while (argc > 0 && (*argv)[0] == '-') {
        argv++;
        argc--;
    }

    for (int i = 0; i < argc; i++) {
        mx_push_back(&dirs, argv[i]);
    }

    mx_sort_list(dirs, &mx_by_lex);

    DIR *curr;
    while (dirs) {
        curr = opendir(dirs->data);
        if (errno != ENOTDIR && errno != EACCES && curr == NULL) {
            mx_printerr("uls: ");
            perror(dirs->data);
            dirs->data = NULL;
        }
        dirs = dirs->next;
    }

    if (mx_print_files(dirs, flag)) {
        tmp = dirs;
        while (tmp && !left_dir) {
            if (tmp->data) {
                left_dir = true;
            }
            tmp = tmp->next;
        }
        if (left_dir)
            mx_printchar('\n');
    }

    curr = dirs == NULL;

    if (curr) {
        mx_push_front(&dirs, ".");
    }

    curr = curr || mx_list_size(dirs) == 1;
    tmp = dirs;
    mx_sort_list(dirs, &mx_by_lex);
    mx_sort_list(dirs, &mx_by_null);

    while (tmp) {
        if (tmp->data != NULL) {
            if (!curr) {
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
