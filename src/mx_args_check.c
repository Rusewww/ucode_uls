#include "uls.h"

void mx_args_check(int argc, char **argv) {
    int len = 0;
    char *permitted_flag = "ARal";
    char *incorrect_flag = NULL;
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        len = mx_strlen(argv[i]);
        int j = 1;
        while (j < len) {
            if (mx_strchr(permitted_flag, argv[i][j]) == NULL) {
                incorrect_flag = &argv[i][j];
                break;
            }
            j++;
        }
        if (incorrect_flag != NULL) {
            mx_printerr("usage: uls [-ARal] [file ...]\n");
            exit(1);
        }
    }
}
