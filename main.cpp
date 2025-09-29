#include <stdio.h>
#include <stdlib.h>

#include "S_stack.h"
#include "C_calc.h"
#include "support.h"
#include "color.h"

void print_mods();

int main() {
    print_mods();


    FILE* file_address = fopen_file("test_proccec.txt", "r");

    calc_program_file struct_file = {}; //! Тест процессорных функций
    my_compiler(file_address, &struct_file);
    run_program(&struct_file);
    printf("\n");

    printf("Amount Comands: %zu\n", struct_file.amount_comands);
    printf("Max Size: %zu\n", struct_file.max_size);
    printf("Amount Div: %d \n", struct_file.amount_div_result);



    // stack_stk(&stack_for_test, 10, __FILE__, __LINE__, NAME_RETURN(stack_for_test));
    // stack_push(&stack_for_test, 10); //! Тест хеша
    // stack_push(&stack_for_test, 10);
    // stack_push(&stack_for_test, 10);
    // stack_push(&stack_for_test, 10);
    // // printf("hash = %zd\n", stack_for_test.inf_hash_code.hash_code);
    // stmn_t buffer_place = 0;
    // stack_pop(&stack_for_test, &buffer_place);
    // stack_for_test.data[1] = 3;
    // stack_pop(&stack_for_test, &buffer_place);
//
    // stack_destruct(&stack_for_test);
    return 0;
}

void print_mods() {
    if (MOD_WORK == DEBUG) {
        printf("--- Activated debug mode ---\n");
    }

    else {
        printf("--- Activated processor mode ---\n");
    }

    if (AUTO_REALLOC == ON) {
        printf("-- Activated auto realloc mode ---\n");
    }

    if (COMPLETION_DATA == ON) {
        printf("--- Activation completion data ---\n");
    }

    if (BIRD_SECURE == ON) {
        printf("-- Using bird secure ---\n");
    }

    if (HASH_SECURE == ON) {
        printf("-- Using hash secure ---\n");
    }

}






