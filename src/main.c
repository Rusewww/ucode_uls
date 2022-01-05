#include "uls.h"

int main(int argc, char **argv) {
    char *flags;
    bool only_curr = false;
    t_list *dirs;
    t_list *t;
    bool dirs_left = false;
    mx_args_check(argc, argv);
    flags = mx_extract_flags(argc, argv);

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

    //mx_validate_dirs(dirs);

    DIR *curr;
    while (dirs) {
        curr = opendir(dirs->data);
        if (curr == NULL && errno != ENOTDIR && errno != EACCES) {
            mx_printerr("uls: ");
            perror(dirs->data);
            dirs->data = NULL;
        }
        dirs = dirs->next;
    }

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
