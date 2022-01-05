#include "uls.h"

void mx_validate_args(int argc, char **argv)
{
    int cur_len = 0;
    char *allowed_flags = "ARal";
    char *invalid_arg = NULL;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++)
    {
        cur_len = mx_strlen(argv[i]);
        for (int j = 1; j < cur_len; j++)
        {
            if (mx_strchr(allowed_flags, argv[i][j]) == NULL)
            {
                invalid_arg = &argv[i][j];
                break;
            }
        }
        if (invalid_arg != NULL)
        {
            mx_printerr("uls: illegal option -- ");
            write(STDERR_FILENO, invalid_arg, 1);
            // Wish we had ACGRSTacehlrtu1@
            mx_printerr("\nusage: uls [-ARal] [file ...]\n");
            exit(1);
        }
    }
}
