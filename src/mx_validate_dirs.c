#include "uls.h"

void mx_validate_dirs(t_list *dirs) {
    DIR *curr;
    for (; dirs != NULL; dirs = dirs->next;) {
        curr = opendir(dirs->data);
        if (curr == NULL && errno != ENOTDIR && errno != EACCES) {
            mx_printerr("uls: ");
            perror(dirs->data);
            dirs->data = NULL;
        }
    }
}
