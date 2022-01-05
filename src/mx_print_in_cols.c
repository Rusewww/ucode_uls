#include "uls.h"

void mx_col_print(t_list *list)
{
    int max_len_name = 0;
    int cur_len = 0;
    int cols = 0;
    int tabs = 0;
    int rows = 0;
    int elements = mx_list_size(list);
    char ***to_print;
    if (elements == 0)
        return;
    t_list *curr = list;
    if (!isatty(STDOUT_FILENO))
    {
        while (curr)
        {
            mx_printstr(curr->data);
            mx_printchar('\n');
            mx_strdel((char **)&curr->data);
            curr = curr->next;
        }
        return;
    }
    struct winsize w_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_size);
    while (curr)
    {
        cur_len = mx_strlen(curr->data);
        if (cur_len > max_len_name)
            max_len_name = cur_len;
        curr = curr->next;
    }
    cols = (w_size.ws_col) / ((max_len_name / 8 + 1) * 8);
    rows = elements / cols;
    rows += elements % cols == 0 ? 0 : 1;
    to_print = malloc(cols * sizeof *to_print);
    curr = list;
    for (int i = 0; i < cols; i++)
    {
        to_print[i] = malloc(rows * sizeof **to_print);

        for (int j = 0; j < rows; j++)
            if (curr)
            {
                to_print[i][j] = curr->data;
                curr = curr->next;
            }
            else
                to_print[i][j] = NULL;
    }
    for (int j = 0; j < rows; j++)
        for (int i = 0; i < cols; i++)
        {
            if (!to_print[i][j])
                break;
            mx_printstr(to_print[i][j]);
            if (i + 1 != cols && to_print[i + 1][j])
            {
                cur_len = mx_strlen(to_print[i][j]);
                tabs = max_len_name / 8 + 1;
                tabs -= cur_len / 8;
                for (int z = 0; z < tabs; z++)
                    mx_printchar('\t');
            }
            else
                mx_printchar('\n');
            mx_strdel(&to_print[i][j]);
        }
}

static int get_max_len(char ***str_arr, int index, int size)
{
    int max = 0;
    int cur_len = 0;
    for (int i = 0; i < size; i++)
    {
        cur_len = mx_strlen(str_arr[i][index]);
        if (cur_len > max)
            max = cur_len;
    }
    return max;
}

static void print_spaces(char *str, int max)
{
    int len = mx_strlen(str);
    for (int i = 0; i < max - len; i++)
        mx_printchar(' ');
}

void mx_long_col_print(t_list *list)
{
    t_list *cur = list;
    int count = mx_list_size(list);
    int parts = 0;
    int *max_sizes;
    char ***splited;
    if (!list)
        return;
    splited = malloc(count * sizeof *splited);
    for (int i = 0; i < count; i++)
    {

        splited[i] = mx_strsplit(cur->data, ' ');
        cur = cur->next;
    }
    for (int i = 0; splited[0][i] != NULL; i++)
        parts++;
    max_sizes = malloc(parts * sizeof *max_sizes);
    for (int i = 0; i < 8; i++)
    {
        max_sizes[i] = get_max_len(splited, i, count);
    }
    cur = list;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < parts; j++)
        {
            if (!splited[i][j])
            {
                mx_printchar('\n');
                break;
            }
            if (j == 5)
            {
                mx_printstr(mx_strstr(cur->data, splited[i][j]));
                mx_printchar('\n');
                break;
            }
            if (j == 0 || j == 2 || j == 3)
            {
                mx_printstr(splited[i][j]);
                print_spaces(splited[i][j], max_sizes[j]);
                mx_printstr("  ");
                continue;
            }
            if (mx_isdigit(splited[i][j][0]))
            {
                print_spaces(splited[i][j], max_sizes[j]);
                mx_printstr(splited[i][j]);
                mx_printchar(' ');
            }
        }
        mx_strdel((char **)&cur->data);
        cur = cur->next;
        mx_del_strarr(&splited[i]);
    }
    free(splited);
    free(max_sizes);
}
