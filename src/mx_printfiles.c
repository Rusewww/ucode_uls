#include "uls.h"

bool mx_printfiles(t_list *dirs, char *flags)
{
    DIR *curr;
    t_list *to_print = NULL;
    t_list *to_print_long = NULL;
    int block_counter = 0;
    bool has_files = false;
    while (dirs)
    {
        if (!dirs->data)
        {
            dirs = dirs->next;
            continue;
        }
        curr = opendir(dirs->data);
        if (curr == NULL && errno == ENOTDIR)
        {
            has_files = true;
            errno = 0;
            if (!mx_strchr(flags, 'l'))
                mx_push_back(&to_print, mx_strdup(dirs->data));
            else
                mx_push_back(&to_print_long, mx_list_file_long(dirs->data, &block_counter));
            dirs->data = NULL;
        }
        dirs = dirs->next;
    }
    if (has_files)
    {
        mx_long_col_print(to_print_long);
        mx_col_print(to_print);
        mx_del_list(&to_print);
        mx_del_list(&to_print_long);
    }
    return has_files;
}
