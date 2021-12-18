#include <stdbool.h>

extern void split(char *dest[], char *str, char *delimiter);
extern void lntrim(char *str);
extern void trim(char *dest, char *str, int delimiter);
extern void die(char *message);

extern bool is_matched(char *a, char *b);
extern void decimalToBinary(char *dest, int size, int decimal);