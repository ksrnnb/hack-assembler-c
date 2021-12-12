#include <stdbool.h>
#include <stdio.h>

typedef struct Parser {
    FILE *file;
    char *current;
    bool done;
} Parser;

Parser new_parser(FILE *file);

extern Parser advance(Parser parser);
extern bool has_more_commands(Parser parser);