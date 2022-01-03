#include "uls.h"

static bool is_unique(t_list *uniqs, char c)
{
    while (uniqs != NULL)
    {
        if (*(char *)(uniqs->data) == c)
            return false;
        uniqs = uniqs->next;
    }
    return true;
}

static char *list_to_str(t_list *uniqs)
{
    int size = mx_list_size(uniqs);
    char *res = mx_strnew(size);
    for (int i = 0; i < size; i++)
    {
        res[i] = *(char *)(uniqs->data);
        uniqs = uniqs->next;
    }
    return res;
}

char *mx_extract_flags(int argc, char **argv)
{
    char *res;
    t_list *uniques = NULL;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++)
        for (int j = 1; argv[i][j] != '\0'; j++)
            if (is_unique(uniques, argv[i][j]))
                mx_push_front(&uniques, &argv[i][j]);
    res = list_to_str(uniques);
    mx_del_list(&uniques);
    return res;
}
