#include "uls.h"

void mx_colum_print(t_list *list) {
    int cols = 0;
    int tabs = 0;
    int rows = 0;
    int current_lenght = 0;
    int max_name = 0;
    int elements = mx_list_size(list);
    char ***to_print;
    if (elements == 0) {
        return;
    }
    t_list *curr = list;
    if (!isatty(STDOUT_FILENO)) {
        while (curr != NULL) {
            mx_printstr(curr->data);
            mx_printchar('\n');
            mx_strdel((char **) &curr->data);
            curr = curr->next;
        }
        return;
    }
    struct winsize w_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_size);
    while (curr != NULL) {
        current_lenght = mx_strlen(curr->data);
        if (current_lenght > max_name) {
            max_name = current_lenght;
        }
        curr = curr->next;
    }
    cols = (w_size.ws_col) / ((max_name / 8 + 1) * 8);
    rows = elements / cols;
    rows += elements % cols == 0 ? 0 : 1;
    to_print = malloc(cols * sizeof *to_print);
    curr = list;
    int i = 0;
    while (i < cols) {
        to_print[i] = malloc(rows * sizeof **to_print);

        for (int j = 0; j < rows; j++) {
            if (curr) {
                to_print[i][j] = curr->data;
                curr = curr->next;
            } else {
                to_print[i][j] = NULL;
            }
        }
        i++;
    }
    int j = 0;
    for (int j = 0; j < rows; j++)
        for (int i = 0; i < cols; i++) {
            if (!to_print[i][j])
                break;
            mx_printstr(to_print[i][j]);
            if (i + 1 != cols && to_print[i + 1][j]) {
                cur_len = mx_strlen(to_print[i][j]);
                tabs = max_len_name / 8 + 1;
                tabs -= cur_len / 8;
                for (int z = 0; z < tabs; z++)
                    mx_printchar('\t');
            } else
                mx_printchar('\n');
            mx_strdel(&to_print[i][j]);
        }
}

int get_max_len(char ***str_arr, int index, int size) {
    int len;
    int max = 0;
    int i = 0;
    while (i < size) {
        len = mx_strlen(str_arr[i][index]);
        if (len > max) {
            max = len;
        }
        i++;
    }
    return max;
}

void print_spaces(char *str, int max) {
    int len = mx_strlen(str);
    int i = 0;
    while (i < max - len) {
        mx_printchar(' ');
        i++;
    }
}

void mx_long_col_print(t_list *list) {
    t_list *cur = list;
    int count = mx_list_size(list);
    int parts = 0;
    int i = 0;
    int *max_size;
    char ***split;
    if (!list) {
        return;
    }
    split = malloc(count * sizeof *split);
    while (i < count) {
        split[i] = mx_strsplit(cur->data, ' ');
        cur = cur->next;
        i++;
    }
    i = 0;
    while (split[0][i] != NULL) {
        parts++;
        i++;
    }
    max_size = malloc(parts * sizeof *max_size);
    i = 0;
    while (i < 8) {
        max_size[i] = get_max_len(split, i, count);
        i++;
    }
    cur = list;
    i = 0;
    while (i < count) {
        for (int j = 0; j < parts; j++) {
            if (!split[i][j]) {
                mx_printchar('\n');
                break;
            }
            if (j == 5) {
                mx_printstr(mx_strstr(cur->data, split[i][j]));
                mx_printchar('\n');
                break;
            }
            if (j == 0 || j == 2 || j == 3) {
                mx_printstr(split[i][j]);
                print_spaces(split[i][j], max_size[j]);
                mx_printstr("  ");
                continue;
            }
            if (mx_isdigit(split[i][j][0])) {
                print_spaces(split[i][j], max_size[j]);
                mx_printstr(split[i][j]);
                mx_printchar(' ');
            }
        }
        mx_strdel((char **) &cur->data);
        cur = cur->next;
        mx_del_strarr(&split[i]);
        i++;
    }
    free(split);
    free(max_size);
}
