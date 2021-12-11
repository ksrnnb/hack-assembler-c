#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// 関数を利用する前に宣言しておかないと
// `implicit declaration of function`のワーニングが発生する
void argument_validation(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    argument_validation(argc, argv);

    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "%s: file cannot open\n", argv[0]);
        exit(1);
    }

    parse_file(file);

    print_1st_row();

    fclose(file);
}

void argument_validation(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: file name is not given\n", argv[0]);
        exit(1);
    }

    if (argc > 2) {
        fprintf(stderr, "%s: 1 argument should be given\n", argv[0]);
        exit(1);
    }

    // .asmを検索
    char *address = strstr(argv[1], ".asm");

    if (address == NULL) {
        fprintf(stderr, "%s: extension should be .asm\n", argv[0]);
        exit(1);
    }
}
