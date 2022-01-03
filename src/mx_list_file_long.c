#include "uls.h"

static char *get_permitions(mode_t mode)
{
    char *res = mx_strnew(9);
    res[0] = S_IRUSR & mode ? 'r' : '-';
    res[1] = S_IWUSR & mode ? 'w' : '-';
    res[2] = S_IXUSR & mode ? 'x' : '-';
    res[3] = S_IRGRP & mode ? 'r' : '-';
    res[4] = S_IWGRP & mode ? 'w' : '-';
    res[5] = S_IXGRP & mode ? 'x' : '-';
    res[6] = S_IROTH & mode ? 'r' : '-';
    res[7] = S_IWOTH & mode ? 'w' : '-';
    res[8] = S_IXOTH & mode ? 'x' : '-';
    return res;
}
static char *get_time_trimmed(time_t file_time)
{
    char **split_bufer = mx_strsplit(ctime(&file_time), ' ');
    time_t cur_time = time(NULL);
    char **cur_time_buf = mx_strsplit(ctime(&cur_time), ' ');
    char **clock_bufer = mx_strsplit(split_bufer[3], ':');
    char *res = NULL;
    mx_str_concat(&res, split_bufer[1]);
    mx_str_concat(&res, " ");
    mx_str_concat(&res, split_bufer[2]);
    mx_str_concat(&res, " ");
    if (mx_strcmp(cur_time_buf[4], split_bufer[4]))
    {
        *mx_strchr(split_bufer[4], '\n') = '\0';
        mx_str_concat(&res, " ");
        mx_str_concat(&res, split_bufer[4]);
    }
    else
    {
        mx_str_concat(&res, clock_bufer[0]);
        mx_str_concat(&res, ":");
        mx_str_concat(&res, clock_bufer[1]);
    }
    mx_del_strarr(&clock_bufer);
    mx_del_strarr(&split_bufer);
    mx_del_strarr(&cur_time_buf);
    return res;
}

char *mx_list_file_long(char *src, int *block_count)
{
    mode_t mode;
    char *name = mx_get_path_base(src);
    char *res = NULL;
    char *temp_buf;
    struct stat file_info;
    lstat(src, &file_info);
    mode = file_info.st_mode;
    *block_count += file_info.st_blocks;
    if (S_ISREG(mode))
        mx_str_concat(&res, "-");
    else if (S_ISDIR(mode))
        mx_str_concat(&res, "d");
    else if (S_ISLNK(mode))
        mx_str_concat(&res, "l");
    else if (S_ISSOCK(mode))
        mx_str_concat(&res, "s");
    else if (S_ISCHR(mode))
        mx_str_concat(&res, "c");
    else if (S_ISFIFO(mode))
        mx_str_concat(&res, "p");
    else if (S_ISBLK(mode))
        mx_str_concat(&res, "b");
    temp_buf = get_permitions(mode);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    temp_buf = mx_itoa(file_info.st_nlink);
    mx_str_concat(&res, temp_buf);
    mx_strdel(&temp_buf);
    mx_str_concat(&res, " ");
    mx_str_concat(&res, getpwuid(file_info.st_uid)->pw_name);
    mx_str_concat(&res, " ");
    if (getgrgid(file_info.st_gid) == NULL)
    {
        temp_buf = mx_itoa(file_info.st_gid);
        mx_str_concat(&res, temp_buf);
        mx_strdel(&temp_buf);
    }
    else
        mx_str_concat(&res, getgrgid(file_info.st_gid)->gr_name);
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
