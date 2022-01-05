#include "uls.h"

bool mx_is_unique(t_list *uniqs, char c)
{
    while (uniqs != NULL)
    {
        if (*(char *)(uniqs->data) == c)
            return false;
        uniqs = uniqs->next;
    }
    return true;
}

char *mx_extract_flags(int argc, char **argv)
{
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
