#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


//Functions from convert.c since we don't have an .h file in deliverables
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main() {
    FILE *file;
    char line[256];
    char test_type[50];
    char input_str[100]; // Buffer size
    char out[33]; // 32 bit fixed size
    char expected[33]; // 32 bit fixed size
    long n_long; // Use long for strtol parsing
    int test_num = 1;
    int passed_tests = 0;
    int total_tests = 0;


    file = fopen("a2_test.txt", "r");

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        // Parses function name, input, expected output & handles line formats
        int items_read = sscanf(line, "%s %s %s", test_type, input_str, expected);

        if (items_read != 3) {
            // Skip formatted lines
            continue;
        }

        printf("Test %d: %s(%s) ->", test_num, test_type, input_str);

        if (strcmp(test_type, "oct_to_bin") == 0) {
            oct_to_bin(input_str, out);
        } else if (strcmp(test_type, "oct_to_hex") == 0) {
            oct_to_hex(input_str, out);
        } else if (strcmp(test_type, "hex_to_bin") == 0) {
            hex_to_bin(input_str, out);
        }
        // Signed functions being integer parsed
        else if (strcmp(test_type, "to_sign_magnitude") == 0 ||
                 strcmp(test_type, "to_ones_complement") == 0 ||
                 strcmp(test_type, "to_twos_complement") == 0) {

            // Converts the string input to a 32-bit signed int
            n_long = strtol(input_str, NULL, 10);
            int32_t n = (int32_t)n_long;

            if (strcmp(test_type, "to_sign_magnitude") == 0) {
                to_sign_magnitude(n, out);
            } else if (strcmp(test_type, "to_ones_complement") == 0) {
                to_ones_complement(n, out);
            } else if (strcmp(test_type, "to_twos_complement") == 0) {
                to_twos_complement(n, out);
            }
        }

        if (strcmp(out, expected) == 0) {
            printf(" [PASS]\n");
            passed_tests++;
        } else {
            printf(" [FAIL] Expected: \"%s\" Got: \"%s\"\n", expected, out);
        }
        total_tests++;
        test_num++;
    }

    fclose(file);
    printf("Summary: %d/%d tests passed\n", passed_tests, total_tests);
    return 0;
}
