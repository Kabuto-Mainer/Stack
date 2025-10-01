#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <string.h>

#include "processor.h"
#include "support.h"
#include "stack.h"
#include "comand.h"


int main(void) {
    processor_f(NAME_BIN_FILE);

    return 0;
}


int processor_f(const char* name_asm_file) {
    assert(name_asm_file);

    FILE* file_bin = fopen_file(name_asm_file, "rb");


    size_t amount_elements = 0;
    if (fread(&amount_elements, sizeof(int), 1, file_bin) != 1) {
        fclose_file(file_bin);
        printf("ERROR: read amount_elements not correct\n");
        return -1;
    }

    int size_stack = 0;
    if (fread(&size_stack, sizeof(int), 1, file_bin) != 1) {
        fclose_file(file_bin);
        printf("ERROR: read size_check not correct\n");
        return -1;
    }

    stack_struct stack = {};
    if (stack_stk(&stack, size_stack, __FILE__,  __LINE__, NAME_RETURN(stack)) != 0) {
        fclose_file(file_bin);
        printf("ERROR: creating stack was not completed\n");
        return -1;
    }

    int* bin_code = create_int_buffer(amount_elements);
    // int read_size = fread(bin_code, sizeof(int), amount_elements, file_bin);
    // printf("read_size: %d\n", read_size);
    // printf("amount_elements: %d\n", amount_elements);
    // return 0;
    if (fread(bin_code, sizeof(int), amount_elements, file_bin) != amount_elements - 2) {
        stack_destruct(&stack);
        free(bin_code);
        fclose_file(file_bin);
        printf("ERROR: with read bin_code\n");
        return -1;
    }

    fclose_file(file_bin);

//     for (int i = 0; i < amount_elements; i++) {
//         printf("EL(%d): %d\n", i, bin_code[i]);
//     }
//     return 0;
//

    for (unsigned int current_element = 0; current_element < amount_elements - 2; current_element++) {
        // printf("COM: %d\n", bin_code[current_element]);
        // printf("current_element = %d\n", current_element);
        switch (bin_code[current_element]) {
            case INT_PUSH: {
                current_element++;

                stack_push(&stack, bin_code[current_element]);
                break;
            }

            case INT_ADD: {
                int arg_1 = 0;
                int arg_2 = 0;

                stack_pop(&stack, &arg_1);
                stack_pop(&stack, &arg_2);

                stack_push(&stack, arg_1 + arg_2);
                break;
            }

            case INT_SUB: {
                int arg_1 = 0;
                int arg_2 = 0;

                stack_pop(&stack, &arg_1);
                stack_pop(&stack, &arg_2);

                stack_push(&stack, arg_1 - arg_2);
                break;
            }

            case INT_DIV: {
                int arg_1 = 0;
                int arg_2 = 0;

                stack_pop(&stack, &arg_1);
                stack_pop(&stack, &arg_2);

                if (arg_2 == 0) {
                    printf("ERROR: division by zero is not correct\n");
                    stack_destruct(&stack);
                    free(bin_code);
                    return -1;
                }

                stack_push(&stack, arg_1 / arg_2);
                break;
            }

            case INT_MUL: {
                int arg_1 = 0;
                int arg_2 = 0;

                stack_pop(&stack, &arg_1);
                stack_pop(&stack, &arg_2);

                stack_push(&stack, arg_1 * arg_2);
                break;
            }

            case INT_OUT: {
                int arg = 0;

                stack_pop(&stack, &arg);
                printf("%d\n", arg);
                break;
            }

            case INT_HLT: {
                stack_destruct(&stack);
                free(bin_code);

                return 0;
            }

            default: {
                stack_destruct(&stack);
                free(bin_code);

                printf("ERROR: unknown command\n");
                return -1;
            }
        }
    }
    stack_destruct(&stack);
    free(bin_code);
    return -1;
}

//     assert(program_struct);
//
//     stack_struct stack = {};
//     stack_stk(&stack, (program_struct->max_size + 1) * SZ_A, __FILE__, __LINE__, NAME_RETURN(stack));
//
//     void* comand_address = program_struct->comands;
//     size_t current_size = 0;
//
//     for (size_t i = 0; i < program_struct->amount_comands; i++) {
//         current_size += SZ_C;
//         switch ( *( (char*)comand_address + current_size - SZ_C) ) {
//             case CHAR_NUM_PUSH: {
//
//                 long long int argument = 0;
//                 memcpy(&argument, (char*)comand_address + current_size, SZ_A);
//
//                 stack_push(&stack, argument);
//                 current_size += SZ_A;
//
//                 break;
//             }
//
//             case CHAR_NUM_ADD: {
//
//                 STACK_GET_ARGUMENTS;
//                 stack_push(&stack, argument_1 + argument_2);
//
//                 break;
//             }
//
//             case CHAR_NUM_SUB: {
//
//                 STACK_GET_ARGUMENTS;
//                 stack_push(&stack, argument_1 - argument_2);
//
//                 break;
//             }
//
//             case CHAR_NUM_DIV: {
//
//                 STACK_GET_ARGUMENTS;
//                 if (argument_2 == 0) {
//                     printf("ERROR: Can not division by ZERO\n");
//                     free(comand_address);
//                     stack_destruct(&stack);
//                     return -1;
//                 }
//
//                 stack_push(&stack, argument_1 / argument_2);
//
//                 break;
//             }
//
//             case CHAR_NUM_MUL: {
//
//                 STACK_GET_ARGUMENTS;
//                 stack_push(&stack, argument_1 * argument_2);
//
//                 break;
//             }
//
//             case CHAR_NUM_OUT: {
//                 long long int argument = 0;
//
//                 stack_pop(&stack, &argument);
//                 // printf("%lld", argument);
//
//                 break;
//             }
//
//             default: {
//                 break;
//             }
//         }
//     }
//
//     stack_destruct(&stack);
//     free(comand_address);
//
//     return 0;
//
// }
//
//
