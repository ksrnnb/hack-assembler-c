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
extern int command_type(struct Parser parser);
extern void symbol(char *dest, struct Parser parser);

extern int A_COMMAND;
extern int C_COMMAND;
extern int L_COMMAND;