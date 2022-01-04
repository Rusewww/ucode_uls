#include "uls.h"

int main(int argc, char **argv) {
    char *flags;
    int only_curr = 0;
    int dirs_left = 0;
    t_list *dirs;
    t_list *t;
    mx_validate_args(argc, argv);
    flags = mx_extract_flags(argc, argv);
    dirs = mx_extract_dirs(argc, argv);

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

    if (mx_printfiles(dirs, flags)) {
        t = dirs;
        while (t && !dirs_left) {
            if (t->data) {
                dirs_left = true;
            }
            t = t->next;
        }
        if (dirs_left)
            mx_printchar('\n');
    }
    only_curr = dirs == NULL;
    if (only_curr) {
        mx_push_front(&dirs, ".");
    }
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
            if (!mx_list_dir_content(t->data, flags) && t->next) {
                mx_printchar('\n');
            }
        }
        t = t->next;
    }

    free(flags);
    mx_del_list(&dirs);
    return errno != 0;
}
