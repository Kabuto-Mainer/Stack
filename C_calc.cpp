#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "C_calc.h"
#include "S_stack.h"


int my_compiler(FILE* stream, calc_program_file* result_address) {
    assert(stream);
    assert(result_address);

    char comand[8] = "";
    long long int argument = 0;

    size_t push_counter = 0;
    size_t max_amount_push_element = 0;
    size_t amount_div_result = 0;

    size_t current_amount_comands = 0;

    size_t current_size = 0;
    size_t max_size = MIN_MASS_SIZE;

    void* comand_address = calloc(MIN_MASS_SIZE, SZ_C);
    if (comand_address == NULL) {
        printf("ERROR with calloc in my_compiler (NULL)\n");
        return -1;
    }

    while(1) {
        if (fscanf(stream, "%s", comand) != 1) {
            free(comand_address);
            return -1;
        }

        if ((max_size - current_size) < SZ_B) {
            void* buffer_address = realloc(comand_address,
                                MODE_REALLOC * max_size * SZ_C);

            if (buffer_address == NULL) {
                printf("ERROR with realloc in my_compiler (NULL)\n");
                free(comand_address);
                return -1;
            }

            comand_address = buffer_address;
            max_size *= MODE_REALLOC;
        }

        if (max_amount_push_element < push_counter) {
            max_amount_push_element = push_counter;
        }

        if (!strcmp(comand, STR_MASS_COMANDS[NUM_PUSH])) {
            if (fscanf(stream, "%lld", &argument) != 1) {
                printf("ERROR: not found argument after PUSH\n");
                free(comand_address);
                return -1;
            }

            argument *= MODE_DECISION;

            if (argument < MIN_MEAN_C || argument > MAX_MEAN_C) {
                printf("ERROR: too big num in argument\n");
                free(comand_address);
                return -1;
            }

            *( (char*)comand_address + current_size) = CHAR_NUM_PUSH;
            current_size += SZ_C;

            memcpy( (char*)comand_address + current_size, &argument, SZ_A);
            // *( (long long int*) (((char*) comand_address) + current_size) ) = argument;
            current_size += SZ_A;

            push_counter++;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_ADD])) {
            if (push_counter < 2) {
                printf("ERROR: too few arguments to ADD\n");
                free(comand_address);
                return -1;
            }

            *( (char*) comand_address + current_size) = CHAR_NUM_ADD;
            current_size += SZ_C;
            push_counter--;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_SUB])) {
            if (push_counter < 2) {
                printf("ERROR: too few arguments to SUB\n");
                free(comand_address);
                return -1;
            }

            *( (char*) comand_address + current_size) = CHAR_NUM_SUB;
            current_size += SZ_C;

            push_counter--;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_DIV])) {
            if (push_counter < 2) {
                printf("ERROR: too few arguments to DIV\n");
                free(comand_address);
                return -1;
            }

            *( (char*) comand_address + current_size) = CHAR_NUM_DIV;
            current_size += SZ_C;

            push_counter--;
            amount_div_result--;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_MUL])) {
            if (push_counter < 2) {
                printf("ERROR: too few arguments to MULL\n");
                free(comand_address);
                return -1;
            }

            *( (char*) comand_address + current_size) = CHAR_NUM_MUL;
            current_size += SZ_C;;

            push_counter--;
            amount_div_result++;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_OUT])) {
            if (push_counter < 1) {
                printf("ERROR: too few argument to OUT\n");
                free(comand_address);
                return -1;
            }

            *( (char*)comand_address + current_size) = CHAR_NUM_OUT;
            current_size += SZ_C;

            push_counter--;
        }

        else if (!strcmp(comand, STR_MASS_COMANDS[NUM_HLT])) {
            *( (char*)comand_address + current_size) = CHAR_NUM_HLT;
            current_size += SZ_C;

            current_amount_comands++;
            break;
        }
        current_amount_comands++;
    }
    result_address->comands = comand_address;
    result_address->amount_comands = current_amount_comands;
    result_address->max_size = max_amount_push_element;
    result_address->amount_div_result = amount_div_result;

    return 0;
}


int run_program(calc_program_file* program_struct) {
    assert(program_struct);

    stack_struct stack = {};
    stack_stk(&stack, (program_struct->max_size + 1) * SZ_A, __FILE__, __LINE__, NAME_RETURN(stack));

    void* comand_address = program_struct->comands;
    size_t current_size = 0;

    for (size_t i = 0; i < program_struct->amount_comands; i++) {
        current_size += SZ_C;
        switch ( *( (char*)comand_address + current_size - SZ_C) ) {
            case CHAR_NUM_PUSH: {

                long long int argument = 0;
                memcpy(&argument, (char*)comand_address + current_size, SZ_A);

                stack_push(&stack, argument);
                current_size += SZ_A;

                break;
            }

            case CHAR_NUM_ADD: {

                STACK_GET_ARGUMENTS;
                stack_push(&stack, argument_1 + argument_2);

                break;
            }

            case CHAR_NUM_SUB: {

                STACK_GET_ARGUMENTS;
                stack_push(&stack, argument_1 - argument_2);

                break;
            }

            case CHAR_NUM_DIV: {

                STACK_GET_ARGUMENTS;
                if (argument_2 == 0) {
                    printf("ERROR: Can not division by ZERO\n");
                    free(comand_address);
                    stack_destruct(&stack);
                    return -1;
                }

                stack_push(&stack, argument_1 / argument_2);

                break;
            }

            case CHAR_NUM_MUL: {

                STACK_GET_ARGUMENTS;
                stack_push(&stack, argument_1 * argument_2);

                break;
            }

            case CHAR_NUM_OUT: {
                long long int argument = 0;

                stack_pop(&stack, &argument);
                printf("%lld", argument);

                break;
            }

            default: {
                break;
            }
        }
    }

    stack_destruct(&stack);
    free(comand_address);

    return 0;
}



