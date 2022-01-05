#include "uls.h"

char *get_permission(mode_t mode) {
    char *out = mx_strnew(9);
    out[0] = S_IRUSR & mode ? 'r' : '-';
    out[1] = S_IWUSR & mode ? 'w' : '-';
    out[2] = S_IXUSR & mode ? 'x' : '-';
    out[3] = S_IRGRP & mode ? 'r' : '-';
    out[4] = S_IWGRP & mode ? 'w' : '-';
    out[5] = S_IXGRP & mode ? 'x' : '-';
    out[6] = S_IROTH & mode ? 'r' : '-';
    out[7] = S_IWOTH & mode ? 'w' : '-';
    out[8] = S_IXOTH & mode ? 'x' : '-';
    return out;
}

char *get_time_trimmed(time_t file_time) {
    char **split_buffer = mx_strsplit(ctime(&file_time), ' ');
    time_t current_time = time(NULL);
    char **current_time_buffer = mx_strsplit(ctime(&current_time), ' ');
    char **clock_buffer = mx_strsplit(split_buffer[3], ':');
    char *out = NULL;
    mx_str_concat(&out, split_buffer[1]);
    mx_str_concat(&out, " ");
    mx_str_concat(&out, split_buffer[2]);
    mx_str_concat(&out, " ");
    if (mx_strcmp(current_time_buffer[4], split_buffer[4])) {
        *mx_strchr(split_buffer[4], '\n') = '\0';
        mx_str_concat(&out, " ");
        mx_str_concat(&out, split_buffer[4]);
    } else {
        mx_str_concat(&out, clock_buffer[0]);
        mx_str_concat(&out, ":");
        mx_str_concat(&out, clock_buffer[1]);
    }
    mx_del_strarr(&clock_buffer);
    mx_del_strarr(&split_buffer);
    mx_del_strarr(&current_time_buffer);
    return out;
}

char *mx_list_file_long(char *src, int *block_count) {
    mode_t mode;
    char *name;
    char **path = mx_strsplit(src, '/');
    int i = 0;
    while (path[i]) {
        if (!path[i + 1]) {
            name = mx_strdup(path[i]);
        }
        i++;
    }
    mx_del_strarr(&path);
    char *res = NULL;
    char *temp_buf;
    struct stat file_info;
    lstat(src, &file_info);
    mode = file_info.st_mode;
    *block_count += file_info.st_blocks;
    if (S_ISREG(mode)) {
        mx_str_concat(&res, "-");
    } else if (S_ISDIR(mode)) {
        mx_str_concat(&res, "d");
    } else if (S_ISLNK(mode)) {
        mx_str_concat(&res, "l");
    } else if (S_ISSOCK(mode)) {
        mx_str_concat(&res, "s");
    } else if (S_ISCHR(mode)) {
        mx_str_concat(&res, "c");
    } else if (S_ISFIFO(mode)) {
        mx_str_concat(&res, "p");
    } else if (S_ISBLK(mode)) {
        mx_str_concat(&res, "b");
    }
    temp_buf = get_permission(mode);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    temp_buf = mx_itoa(file_info.st_nlink);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    mx_str_concat(&res, getpwuid(file_info.st_uid)->pw_name);
    mx_str_concat(&res, " ");
    if (getgrgid(file_info.st_gid) == NULL) {
        temp_buf = mx_itoa(file_info.st_gid);
        mx_str_concat(&res, temp_buf);
        mx_strdel(&temp_buf);
    } else {
        mx_str_concat(&res, getgrgid(file_info.st_gid)->gr_name);
    }
    mx_str_concat(&res, " ");
    temp_buf = mx_itoa(file_info.st_size);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    temp_buf = get_time_trimmed(file_info.st_mtimespec.tv_sec);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    mx_str_concat(&res, name);
    mx_strdel(&name);
    return res;
}
