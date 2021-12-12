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

#define A_COMMAND 1
#define C_COMMAND 2
#define L_COMMAND 3

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
        printf("file is empty\n");
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

    printf("token: %s\n", token);

    parser.current = buf;
    return parser;
}

int command_type() { return A_COMMAND; }

char *symbol() { return "xxx"; }
