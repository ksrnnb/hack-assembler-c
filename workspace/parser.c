#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Parser {
    FILE *file;
    char *current;
    bool done;
};

#define BUFFER_SIZE 256

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

struct Parser advance(struct Parser parser) {
    char buf[BUFFER_SIZE];
    char *result = fgets(buf, BUFFER_SIZE, parser.file);

    if (result == NULL) {
        printf("file is empty\n");
        parser.done = true;
        return parser;
    }

    printf("%s", buf);

    parser.current = buf;

    return parser;
}

int command_type() { return A_COMMAND; }

char *symbol() { return "xxx"; }