#include "uls.h"

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
