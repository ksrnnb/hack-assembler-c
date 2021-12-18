#include <stdio.h>

#include "utils.h"

int code_dest(char *dest) {
    if (is_matched(dest, "M")) return 0b001;
    if (is_matched(dest, "D")) return 0b010;
    if (is_matched(dest, "MD")) return 0b011;
    if (is_matched(dest, "A")) return 0b100;
    if (is_matched(dest, "AM")) return 0b101;
    if (is_matched(dest, "AD")) return 0b110;
    if (is_matched(dest, "AMD")) return 0b111;
    if (dest[0] == '\0') return 0b000;

    die("dest mnemonic is invalid");
}

int code_comp(char *comp) {
    if (is_matched(comp, "0")) return 0b0101010;
    if (is_matched(comp, "1")) return 0b0111111;
    if (is_matched(comp, "-1")) return 0b0111010;
    if (is_matched(comp, "D")) return 0b0001100;
    if (is_matched(comp, "A")) return 0b0110000;
    if (is_matched(comp, "!D")) return 0b0001101;
    if (is_matched(comp, "!A")) return 0b0110001;
    if (is_matched(comp, "-D")) return 0b001111;
    if (is_matched(comp, "-A")) return 0b110011;
    if (is_matched(comp, "D+1")) return 0b0011111;
    if (is_matched(comp, "A+1")) return 0b0110111;
    if (is_matched(comp, "D-1")) return 0b0001110;
    if (is_matched(comp, "A-1")) return 0b0110010;
    if (is_matched(comp, "D+A")) return 0b0000010;
    if (is_matched(comp, "D-A")) return 0b0010011;
    if (is_matched(comp, "A-D")) return 0b0000111;
    if (is_matched(comp, "D&A")) return 0b0000000;
    if (is_matched(comp, "D|A")) return 0b0010101;
    if (is_matched(comp, "M")) return 0b1110000;
    if (is_matched(comp, "!M")) return 0b1110001;
    if (is_matched(comp, "-M")) return 0b1110011;
    if (is_matched(comp, "M+1")) return 0b1110111;
    if (is_matched(comp, "M-1")) return 0b1110010;
    if (is_matched(comp, "D+M")) return 0b1000010;
    if (is_matched(comp, "D-M")) return 0b1010011;
    if (is_matched(comp, "M-D")) return 0b1000111;
    if (is_matched(comp, "D&M")) return 0b1000000;
    if (is_matched(comp, "D|M")) return 0b1010101;

    die("comp mnemonic is invalid");
}

int code_jump(char *jump) {
    if (is_matched(jump, "JGT")) return 0b001;
    if (is_matched(jump, "JEQ")) return 0b010;
    if (is_matched(jump, "JGE")) return 0b011;
    if (is_matched(jump, "JLT")) return 0b100;
    if (is_matched(jump, "JNE")) return 0b101;
    if (is_matched(jump, "JLE")) return 0b110;
    if (is_matched(jump, "JMP")) return 0b111;
    if (jump[0] == '\0') return 0b000;

    die("jump mnemonic is invalid");
}