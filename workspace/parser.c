#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

struct Parser {
    FILE *file;
    char *current;
    bool done;
};

#define ONE_LINE_LIMIT 256

const int A_COMMAND = 1;
const int C_COMMAND = 2;
const int L_COMMAND = 3;

struct Parser new_parser(FILE *file) {
    struct Parser parser;
    parser.file = file;
    parser.current = NULL;
    parser.done = false;

    return parser;
}

bool has_more_commands(struct Parser parser) { return !parser.done; }

bool is_comment(char *token) { return token[0] == '/' && token[1] == '/'; }

bool is_comamnd(char *token) {
    // 改行の場合は、trim済みなので\0となる
    if (token[0] == '\0') {
        return false;
    }

    return !is_comment(token);
}

struct Parser advance(struct Parser parser) {
    char buf[ONE_LINE_LIMIT] = "";
    char *result = fgets(buf, ONE_LINE_LIMIT, parser.file);

    if (result == NULL) {
        parser.done = true;
        return parser;
    }

    lntrim(buf);
    char token[ONE_LINE_LIMIT] = "";
    trim(token, buf, ' ');

    if (!is_comamnd(token)) {
        parser = advance(parser);
        return parser;
    }

    parser.current = token;
    return parser;
}

// TODO: 入力が正しいことを前提としている。入力が正しくない場合の処理が必要。
int command_type(struct Parser parser) {
    if (parser.current[0] == '@') {
        return A_COMMAND;
    }

    if (parser.current[0] == '(') {
        return L_COMMAND;
    }

    return C_COMMAND;
}

void getSymbolA(char *dest, char *command);
void getSymbolC(char *dest, char *command);

#define COMMAND_SIZE 16

void symbol(char *dest, struct Parser parser) {
    if (strlen(dest) > COMMAND_SIZE) {
        die("symbol is too long");
    }

    if (command_type(parser) == A_COMMAND) {
        getSymbolA(dest, parser.current);
        return;
    }

    if (command_type(parser) == L_COMMAND) {
        getSymbolC(dest, parser.current);
        return;
    }

    die("command type is invalid");
}

// はじめの@を取り除く
void getSymbolA(char *dest, char *command) {
    for (int i = 0; i < strlen(command) - 1; i++) {
        dest[i] = command[i + 1];
    }

    dest[strlen(dest) - 1] = '\0';
}

void getSymbolC(char *dest, char *command) {
    // "(" と ")" を除く
    for (int i = 0; i < strlen(command) - 1; i++) {
        if (command[i + 1] == ')') {
            dest[i] = '\0';
            break;
        }

        dest[i] = command[i + 1];
    }
}

// C命令のdestニーモニックを返す
// M=M+1の左辺
void dest(char *char_dest, struct Parser parser) {
    if (command_type(parser) != C_COMMAND) {
        die("command should be c command when you use dest()");
    }

    char *buf[2] = {NULL};
    split(buf, parser.current, "=");

    if (buf[0] == NULL) {
        char_dest[0] = '\0';
        return;
    }

    for (int i = 0; i <= strlen(buf[0]); i++) {
        char_dest[i] = buf[0][i];
    }
}

void compJmp(char *dest, struct Parser parser);

// C命令のcompニーモニックを返す
// M=M+1の右辺
void comp(char *dest, struct Parser parser) {
    if (command_type(parser) != C_COMMAND) {
        die("command should be c command when you use comp()");
    }

    char *buf[2] = {NULL};
    split(buf, parser.current, "=");

    if (buf[0] == NULL || buf[1] == NULL) {
        // =でsplitできなかった場合は、JMP
        compJmp(dest, parser);
        return;
    }

    for (int i = 0; i <= strlen(buf[1]); i++) {
        dest[i] = buf[1][i];
    }
}

// JMPの場合
void compJmp(char *dest, struct Parser parser) {
    if (command_type(parser) != C_COMMAND) {
        die("command should be c command when you use compJmp()");
    }

    char *buf[2] = {NULL};
    split(buf, parser.current, ";");

    if (buf[0] == NULL || buf[1] == NULL) {
        dest[0] = '\0';
        return;
    }

    if (is_matched(buf[1], "JGT")) {
        dest[0] = 'j';
        dest[1] = 'G';
        dest[2] = 'T';
        return;
    }

    if (is_matched(buf[1], "JEQ")) {
        // TODO: JGTと同様になるよう修正
        // 新しくポインタが割り当てられてしまうため
        // もしくは、文字列を返す関数を考える。。。
        dest = "JEQ";
        return;
    }

    if (is_matched(buf[1], "JGE")) {
        dest = "JGE";
        return;
    }

    if (is_matched(buf[1], "JLT")) {
        dest = "JLT";
        return;
    }

    if (is_matched(buf[1], "JNE")) {
        dest = "JNE";
        return;
    }

    if (is_matched(buf[1], "JLE")) {
        dest = "JLE";
        return;
    }

    if (is_matched(buf[1], "JMP")) {
        dest = "JMP";
        return;
    }

    dest[0] = '\0';
    return;
}

// C命令のjumpニーモニックを返す
// D;JMPの右辺
void jump(char *dest, struct Parser parser) {
    if (command_type(parser) != C_COMMAND) {
        die("command should be c command when you use compJmp()");
    }

    char *buf[2] = {NULL};
    split(buf, parser.current, ";");

    if (buf[0] == NULL || buf[1] == NULL) {
        dest[0] = '\0';
        return;
    }

    for (int i = 0; i <= strlen(buf[1]); i++) {
        dest[i] = buf[1][i];
    }
}