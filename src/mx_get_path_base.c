#include "uls.h"

char *mx_get_path_base(char *path) {
    char *res;
    char **node_path = mx_strsplit(path, '/');
    int i = 0;
    while (node_path[i]) {
        if (!node_path[i + 1]) {
            res = mx_strdup(node_path[i]);
        }
        i++;
    }
    mx_del_strarr(&node_path);
    return res;
}
