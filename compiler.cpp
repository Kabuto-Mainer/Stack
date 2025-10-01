#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <string.h>

// #include "processor.h"
#include "compiler.h"
#include "support.h"
// #include "stack.h"
#include "comand.h"
#include "const.h"

int main(void) {
    compiler_f(NAME_INPUT_FILE, NAME_BIN_FILE, NAME_TEXT_FILE);

    return 0;
}



int compiler_f(const char* name_input_file, const char* name_asm_file, const char* name_text_file) {
    assert(name_input_file);
    assert(name_asm_file);
    assert(name_text_file);

    // printf("input: %s\n", name_input_file);

    FILE* input_stream = fopen_file(name_input_file, "r");

#if PRINT_TO_TEXT_FILE == 1
    FILE* text_stream = fopen_file(name_text_file, "w");
#endif
    //
    //     int* buffer_bin_code = create_buffer(MAX_AMOUNT_COMANDS);

        //! Парсить буфер буду потом
        // char* text_str = create_buffer(START_AMOUNT_COMANDS);
        // fread(bin_code, sizeof(char), file_size_check(name_input_file), input_stream);

//TODO current_size size_t
    int argument = 0;
    int push_counter = 0;
    int max_push = 0;

    int amount_cmd = 0;
    int amount_div_result = 0;

    size_t max_size = START_AMOUNT_CMD; // Only >= current_size

    size_t current_size = 2; // Only ++
    // bin_code = <amount_cmd> <max_push> <bin_code[2]> ...
    int* bin_code = create_buffer(START_AMOUNT_CMD);


    while (1) {
        char comand[8] = "";

        if (fscanf(input_stream, "%7s", comand) != 1) {
            free(bin_code);
            return -1;
        }

        // printf("comand: %s\n", comand);
        if (current_size == max_size - (2 * sizeof(int))) {
            bin_code = realloc_buffer(bin_code, (size_t) max_size);

            if (bin_code == NULL) {
                return -1;
            }

            max_size *= MOD_REALLOC;
        }

        if (max_push < push_counter) {
            max_push = push_counter;
        }

        if (strcmp(comand, STR_MASS_COMANDS[INT_PUSH]) == 0) {
            if (fscanf(input_stream, "%d", &argument) != 1) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: not found argument after PUSH\n");

                free(bin_code);
                return -1;
            }

            argument *= MODE_DECISION;

            if (argument < MIN_MEAN || argument > MAX_MEAN) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too big num in argument\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_PUSH;
            bin_code[current_size++] = argument;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d %d\n", INT_PUSH, argument);
#endif
            push_counter++;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_ADD]) == 0) {
            if (push_counter < 2) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too few arguments to ADD\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_ADD;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_ADD);
#endif
            push_counter--;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_SUB]) == 0) {
            if (push_counter < 2) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too few arguments to SUB\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_SUB;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_SUB);
#endif
            push_counter--;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_DIV]) == 0) {
            if (push_counter < 2) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too few arguments to DIV\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_DIV;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_DIV);
#endif
            push_counter--;
            amount_div_result--;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_MUL]) == 0) {
            if (push_counter < 2) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too few arguments to MULL\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_MUL;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_MUL);
#endif
            push_counter--;
            amount_div_result++;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_OUT]) == 0) {
            if (push_counter < 1) {
                printf("%s:%d: ", name_input_file, amount_cmd);
                printf("ERROR: too few argument to OUT\n");
                free(bin_code);
                return -1;
            }

            bin_code[current_size++] = INT_OUT;

#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_OUT);
#endif
            push_counter--;
        }

        else if (strcmp(comand, STR_MASS_COMANDS[INT_HLT]) == 0) {
            bin_code[current_size++] = INT_HLT;

            amount_cmd++;
#if PRINT_TO_TEXT_FILE == 1
            fprintf(text_stream, "%d\n", INT_HLT);
#endif
            break;
        }

        else {
            // syntax_error();
            free(bin_code);
            return -1;
        }
        amount_cmd++;
    }
    // В надежде на то, что current_size поместится в <int>
    bin_code[0] = (int) current_size;
    bin_code[1] = max_push;

    fclose_file(input_stream);

    FILE* bin_file = fopen_file(name_asm_file, "wb");
    if (fwrite(bin_code, sizeof(int), current_size, bin_file) != current_size) {
        printf("ERROR: write bin_code to bin_file was failed\n");
        free(bin_code);
        return -1;
    }
    fclose_file(bin_file);

    free(bin_code);
    printf("Compilation was completed\n");
    return 0;
}


