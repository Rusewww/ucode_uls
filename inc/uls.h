#ifndef ULS
#define ULS

#include "../libmx/inc/libmx.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/acl.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <uuid/uuid.h>

bool mx_list_dir_content(char *dir_name, char *flags);
bool mx_print_files(t_list *dirs, char *flag);
char *mx_list_file_long(char *src, int *blcok_count);
void mx_colum_print(t_list *list);
void mx_long_col_print(t_list *list);
bool mx_is_unique(t_list *unique, char c);
char *mx_list_to_str(t_list *list);
void mx_validate_dirs(t_list *dirs);

#endif
