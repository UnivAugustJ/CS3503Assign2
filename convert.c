#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        // Check the i-th bit and place it at the correct index (31-i)
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void map_oct_digit_to_bin(char oct_digit, char *out) {
    int val = oct_digit - '0';
    out[0] = (val >> 2) & 1 ? '1' : '0';
    out[1] = (val >> 1) & 1 ? '1' : '0';
    out[2] = (val >> 0) & 1 ? '1' : '0';
    out[3] = '\0';
}

void map_hex_digit_to_bin(char hex_digit, char *out) {
    int val;
    if (hex_digit >= '0' && hex_digit <= '9') {
        val = hex_digit - '0';
    } else if (hex_digit >= 'A' && hex_digit <= 'F') {
        val = hex_digit - 'A' + 10;
    } else if (hex_digit >= 'a' && hex_digit <= 'f') {
        val = hex_digit - 'a' + 10;
    } else {
        val = 0;
    }
    out[0] = (val >> 3) & 1 ? '1' : '0';
    out[1] = (val >> 2) & 1 ? '1' : '0';
    out[2] = (val >> 1) & 1 ? '1' : '0';
    out[3] = (val >> 0) & 1 ? '1' : '0';
    out[4] = '\0';
}

void bin_to_hex(const char *bin, char *out) {
    int len = strlen(bin);
    int pad_len = (4 - (len % 4)) % 4;
    char temp_bin[100] = {0};

    for (int i = 0; i < pad_len; i++) {
        temp_bin[i] = '0';
    }
    strcat(temp_bin, bin);
    len = strlen(temp_bin);
    out[0] = '\0';
    char hex_digit[2];
    for (int i = 0; i < len; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            if (temp_bin[i + j] == '1') {
                val += (1 << (3 - j));
            }
        }
        if (val < 10) {
            hex_digit[0] = val + '0';
        } else {
            hex_digit[0] = val - 10 + 'A';
        }
        hex_digit[1] = '\0';
        strcat(out, hex_digit);
    }

    // Removes leading zeros
    int first_non_zero = -1;
    for (int i = 0; i < strlen(out); i++) {
        if (out[i] != '0') {
            first_non_zero = i;
            break;
        }
    }
    if (first_non_zero > 0) {
        memmove(out, out + first_non_zero, strlen(out) - first_non_zero + 1);
    } else if (first_non_zero == -1 && strlen(out) > 0) {
        out[0] = '0';
        out[1] = '\0';
    }
}

void oct_to_bin(const char *oct, char *out) {
    out[0] = '\0';
    char bin_chunk[4];
    for (int i = 0; i < strlen(oct); i++) {
        map_oct_digit_to_bin(oct[i], bin_chunk);
        strcat(out, bin_chunk);
    }
}

void oct_to_hex(const char *oct, char *out) {
    if (strcmp(oct, "0") == 0) {
        strcpy(out, "0");
        return;
    }
    char bin_buffer[100];
    char temp_map[4];
    bin_buffer[0] = '\0';
    for (int i = 0; i < strlen(oct); i++) {
        map_oct_digit_to_bin(oct[i], temp_map);
        strcat(bin_buffer, temp_map);
    }
    bin_to_hex(bin_buffer, out);
}

void hex_to_bin(const char *hex, char *out) {
    out[0] = '\0';
    char bin_chunk[5];

    for (int i = 0; i < strlen(hex); i++) {
        map_hex_digit_to_bin(hex[i], bin_chunk);
        strcat(out, bin_chunk);
    }
}

void to_sign_magnitude(int32_t n, char *out) {
    // Gets the 31-bit magnitude
    uint32_t magnitude = (uint32_t) (n < 0 ? -(long long)n : n);

    // Gets the 32-bit binary string for the magnitude
    to_32bit_binary(magnitude, out);

    if (n < 0) {
        // Sets the sign bit to 1
        out[0] = '1';
    }
}

void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        // Gets the 32-bit magnitude of the absolute value
        uint32_t magnitude = (uint32_t)labs(n);
        to_32bit_binary(magnitude, out);

        // Flips ALL bits
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }
}

void to_twos_complement(int32_t n, char *out) {
    // Casts a negative signed integer to an unsigned integer automatically
    uint32_t bit_pattern = (uint32_t)n;
    to_32bit_binary(bit_pattern, out);
}