#include "uls.h"

char *mx_get_path_base(char *path)
{
    char *res;
    char **path_nodes = mx_strsplit(path, '/');
    for (int i = 0; path_nodes[i]; i++)
        if (!path_nodes[i + 1])
            res = mx_strdup(path_nodes[i]);
    mx_del_strarr(&path_nodes);
    return res;
}
