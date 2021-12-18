#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code.h"
#include "parser.h"
#include "utils.h"

// 関数を利用する前に宣言しておかないと
// `implicit declaration of function`のワーニングが発生する
void argument_validation(int argc, char *argv[]);
void do_a_command(Parser parser, FILE *outFile);
void do_c_command(Parser parser, FILE *outFile);

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

    while (true) {
        parser = advance(parser);

        if (!has_more_commands(parser)) {
            break;
        }

        if (command_type(parser) == A_COMMAND) {
            int symbol_size = 16;
            int buffer_size = 16;
            char s[symbol_size];
            char buf[buffer_size];

            symbol(s, parser);
            decimalToBinary(buf, sizeof buf, atoi(s));
            fprintf(outFile, "0%s\n", buf);
        }

        if (command_type(parser) == C_COMMAND) {
            do_c_command(parser, outFile);
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

void do_c_command(Parser parser, FILE *outFile) {
    char d[16];
    char c[16];
    char j[16];
    dest(d, parser);
    comp(c, parser);
    jump(j, parser);

    int b_dest = code_dest(d);
    int b_comp = code_comp(c);
    int b_jump = code_jump(j);

    char buf_dest[4];
    char buf_comp[8];
    char buf_jump[4];

    decimalToBinary(buf_dest, sizeof buf_dest, b_dest);
    decimalToBinary(buf_comp, sizeof buf_comp, b_comp);
    decimalToBinary(buf_jump, sizeof buf_jump, b_jump);

    fprintf(outFile, "111%s%s%s\n", buf_comp, buf_dest, buf_jump);
}
