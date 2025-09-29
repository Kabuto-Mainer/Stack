#ifndef C_CALC_H
#define C_CALC_H

#include "S_stack.h"

#define PRINT_ARG OFF

#if PRINT_ARG == ON
#define PRINT_ARGUMENT \
 printf("Arg_1 = %lld\n", argument_1); \
 printf("Arg_2 = %lld\n", argument_2);

#else PRINT_NODE (void(0))

#endif // PRINT_ARG== DEBUG

enum INT_COMANDS{
    NUM_PUSH = 0,
    NUM_ADD = 1,
    NUM_SUB = 2,
    NUM_DIV = 3,
    NUM_MUL = 4,
    NUM_OUT = 5,
    NUM_HLT = 6
};

enum CHAR_NUM{
    CHAR_NUM_PUSH = '0',
    CHAR_NUM_ADD = '1',
    CHAR_NUM_SUB = '2',
    CHAR_NUM_DIV = '3',
    CHAR_NUM_MUL = '4',
    CHAR_NUM_OUT = '5',
    CHAR_NUM_HLT = '6'
};


const char STR_MASS_COMANDS[10][6] = {
                        "PUSH",
                        "ADD",
                        "SUB",
                        "DIV",
                        "MUL",
                        "OUT",
                        "HLT"
};

const size_t MIN_MASS_SIZE = 40; // > 9
const int MODE_REALLOC = 4;
const size_t MODE_DECISION = 1;
//! Не работает для 2 и более OUT PUT

const long long int MAX_MEAN_C = 1e15;
const long long int MIN_MEAN_C = -1e15;

const size_t SZ_C = sizeof(char); // sizeof comand
const size_t SZ_A = sizeof(long long int); // sizeof argument
const size_t SZ_B = SZ_C + SZ_A; // sizeof block of comand and argument


struct calc_program_file{
    void* comands;

    size_t amount_comands;
    size_t max_size;
    int amount_div_result;
};


#define STACK_GET_ARGUMENTS  \
 long long int argument_1 = 0; \
 long long int argument_2 = 0; \
 \
 stack_pop(&stack, &argument_1); \
 stack_pop(&stack, &argument_2); \
 PRINT_ARG



int my_compiler(FILE* stream, calc_program_file* result_address);

int run_program(calc_program_file* program_struct);




#endif //C_CALC_H




