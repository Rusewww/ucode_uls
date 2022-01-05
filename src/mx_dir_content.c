#include "../inc/uls.h"

/*char *mx_get_path_base(char *path) {
    char *res;
    char **path_nodes = mx_strsplit(path, '/');
    for (int i = 0; path_nodes[i]; i++)
        if (!path_nodes[i + 1])
            res = mx_strdup(path_nodes[i]);
    mx_del_strarr(&path_nodes);
    return res;
}*/

void print_long_list(char *dir_name, t_list *list) {
    char *buffer;
    t_list *head = list;
    t_list *list_buffer = NULL;
    int count = 0;
    while (list != NULL) {
        buffer = mx_strjoin(dir_name, "/");
        mx_str_concat(&buffer, list->data);
        mx_push_back(&list_buffer, mx_list_file_long(buffer, &count));
        mx_strdel((char **) &list->data);
        mx_strdel(&buffer);
        list = list->next;
    }
    if (head != NULL) {
        mx_printstr("total ");
        mx_printint(count);
        mx_printchar('\n');
        mx_long_col_print(list_buffer);
        mx_del_list(&list_buffer);
    }
}

bool mx_list_dir_content(char *dir_name, char *flags) {
    DIR *dir;
    bool skip_dots = !mx_strchr(flags, 'a');
    bool skip_only_dirdots = !mx_strchr(flags, 'A');
    bool is_recursive = mx_strchr(flags, 'R');
    char *base_name;
    bool is_empty;
    t_list *curr;
    t_list *to_print = NULL;
    char *path_build_buf = NULL;
    t_list *inner_dir_names = NULL;
    struct dirent *cur_file;
    errno = 0;
    dir = opendir(dir_name);
    if (errno != 0) {
        char **path_nodes = mx_strsplit(path, '/');
        for (int i = 0; path_nodes[i]; i++)
            if (!path_nodes[i + 1])
                base_name = mx_strdup(path_nodes[i]);
        mx_del_strarr(&path_nodes);
        mx_printerr("uls: ");
        perror(base_name);
        mx_strdel(&base_name);
        return false;
    }
    cur_file = readdir(dir);
    while (cur_file) {
        if (skip_dots && cur_file->d_name[0] == '.') {
            if (skip_only_dirdots) {
                cur_file = readdir(dir);
                continue;
            } else if (!mx_strcmp(cur_file->d_name, ".") || !mx_strcmp(cur_file->d_name, "..")) {
                cur_file = readdir(dir);
                continue;
            }
        }
        if (mx_strcmp(cur_file->d_name, ".") && mx_strcmp(cur_file->d_name, "..") && cur_file->d_type == DT_DIR &&
            is_recursive) {
            path_build_buf = mx_strdup(dir_name);
            mx_str_concat(&path_build_buf, "/");
            mx_str_concat(&path_build_buf, cur_file->d_name);
            mx_push_front(&inner_dir_names, path_build_buf);
        }
        mx_push_front(&to_print, mx_strdup(cur_file->d_name));
        cur_file = readdir(dir);
    }
    mx_sort_list(to_print, &mx_by_lex);
    if (!mx_strchr(flags, 'l'))
        mx_colum_print(to_print);
    else
        print_long_list(dir_name, to_print);
    if (!to_print)
        is_empty = true;
    mx_del_list(&to_print);
    closedir(dir);
    if (inner_dir_names) {
        mx_sort_list(inner_dir_names, &mx_by_lex);
        curr = inner_dir_names;
        while (curr) {
            mx_printchar('\n');
            mx_printstr(curr->data);
            mx_printstr(":\n");
            mx_list_dir_content(curr->data, flags);
            mx_strdel((char **) &curr->data);
            mx_pop_front(&inner_dir_names);
            curr = curr->next;
        }
    }
    return is_empty;
}
