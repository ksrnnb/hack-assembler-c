#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// 文字が一致しているかどうか
bool is_matched(char *a, char *b) { return strcmp(a, b) == 0; }

// 指定したデリミタで文字列を分割する
void split(char *dest[], char *str, char *delimiter) {
    char *token = strtok(str, delimiter);

    for (int i = 0; token != NULL; i++) {
        dest[i] = token;
        token = strtok(NULL, delimiter);
    }
}

// 任意の文字を取り除く
void trim(char *dest, char *str, int delimiter) {
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == delimiter) {
            continue;
        }
        dest[j] = str[i];
        j++;
    }
}

// 末尾の改行を除く。
void lntrim(char *str) {
    char *p = strchr(str, '\n');

    if (p != NULL) {
        *p = '\0';
    }
}
