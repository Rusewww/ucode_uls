#include "../inc/uls.h"

char *mx_extract_flags(int argc, char **argv) {
    char *res;
    t_list *uniques = NULL;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++)
        for (int j = 1; argv[i][j] != '\0'; j++)
            if (mx_is_unique(uniques, argv[i][j]))
                mx_push_front(&uniques, &argv[i][j]);
    res = mx_list_to_str(uniques);
    mx_del_list(&uniques);
    return res;
}

t_list *mx_extract_dirs(int argc, char **argv)
{
    t_list *res = NULL;
    argc--;
    argv++;
    while (argc > 0 && (*argv)[0] == '-')
    {
        argv++;
        argc--;
    }
    for (int i = 0; i < argc; i++)
        mx_push_back(&res, argv[i]);
    return res;
}

int main(int argc, char **argv) {
    /*char *flag;
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

    if (mx_print_files(dirs, flag)) {
        tmp = dirs;
        while (tmp && !left) {
            if (tmp->data) {
                left = true;
            }
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
    return errno != 0;*/
    char *flags;
    bool only_curr = false;
    t_list *dirs;
    t_list *t;
    bool dirs_left = false;
    mx_args_check(argc, argv);

    flags = mx_extract_flags(argc, argv);

    dirs = mx_extract_dirs(argc, argv);

    mx_sort_list(dirs, &mx_by_lex);
    mx_validate_dirs(dirs);
    if (mx_print_files(dirs, flags)) {
        t = dirs;
        while (t && !dirs_left) {
            if (t->data)
                dirs_left = true;
            t = t->next;
        }
        if (dirs_left)
            mx_printchar('\n');
    }
    only_curr = dirs == NULL;
    if (only_curr)
        mx_push_front(&dirs, ".");
    only_curr = only_curr || mx_list_size(dirs) == 1;
    t = dirs;
    mx_sort_list(dirs, &mx_by_lex);
    mx_sort_list(dirs, &mx_by_null);
    while (t) {
        if (t->data != NULL) {
            if (!only_curr) {
                mx_printstr(t->data);
                mx_printstr(":\n");
            }
            if (!mx_list_dir_content(t->data, flags) && t->next)
                mx_printchar('\n');
        }
        t = t->next;
    }
    // freeing memory
    free(flags);
    mx_del_list(&dirs);
    return errno != 0;
}
