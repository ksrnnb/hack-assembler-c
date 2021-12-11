#include <stdio.h>
#include <string.h>

struct Parser {
    FILE *file;
};

struct Parser parser;

#define BUFFER_SIZE 64

void parse_file(FILE *file) { parser.file = file; }

void print_1st_row() {
    char buf[BUFFER_SIZE];

    fgets(buf, BUFFER_SIZE - 1, parser.file);

    printf("1st row is %s\n", buf);
}