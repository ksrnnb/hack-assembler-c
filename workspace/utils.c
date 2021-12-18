#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 文字が一致しているかどうか
bool is_matched(char *a, char *b) { return strcmp(a, b) == 0; }

// 指定したデリミタで文字列を分割する
void split(char *dest[], char *str, char *delimiter) {
    // 非破壊にするため、コピーを作成
    char copyStr[strlen(str)];
    for (int i = 0; i <= strlen(str); i++) {
        copyStr[i] = str[i];
    }

    char *token = strtok(copyStr, delimiter);

    if (is_matched(token, str)) {
        return;
    }

    int j = 0;
    for (int i = 0; token != NULL; i++) {
        dest[i] = token;
        j++;
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

// エラー終了処理
void die(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 10進数から2進数に変換する
void decimalToBinary(char *dest, int size, int decimal) {
    int max = (1 << 15) - 1;  // 2^15 - 1
    if (decimal > max) {
        return;
    }

    int quotient = decimal;

    for (int i = 1; i < size; i++) {
        int remainer = quotient % 2;
        dest[size - i - 1] = remainer ? '1' : '0';

        quotient = quotient / 2;
    }
    dest[size - 1] = '\0';
}