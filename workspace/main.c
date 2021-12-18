#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "utils.h"

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

    Parser parser = new_parser(file);
    FILE *outFile = fopen("result.hack", "w+");

    while (has_more_commands(parser)) {
        parser = advance(parser);

        if (command_type(parser) == A_COMMAND) {
            int symbol_size = 16;
            int buffer_size = 16;
            char s[symbol_size];
            char buf[buffer_size];

            symbol(s, parser);
            decimalToBinary(buf, sizeof buf, s);
            fprintf(outFile, "0%s\n", buf);
        }
    }

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
