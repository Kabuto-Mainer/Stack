#include <stdio.h>
#include <stdlib.h>

#include "S_stack.h"
#include "C_calc.h"
#include "support.h"
#include "color.h"

int main() {
    FILE* file_address = fopen_file("test_proccec.txt", "r");

    calc_program_file struct_file = {};
    my_compiler(file_address, &struct_file);

    // printf("Amount Comands: %zu\n", struct_file.amount_comands);
    // printf("Max Size: %zu\n", struct_file.max_size);
    // printf("Amount Div: %d \n", struct_file.amount_div_result);

    // free(struct_file.comands);
    run_program(&struct_file);
    printf("\n");



//     stack_struct stack_for_test = {};
//     stack_stk(&stack_for_test, 1, __FILE__, __LINE__, NAME_RETURN(stack_for_test));
//
//     // printf("Stack Error: %d\?n", stack_error(&stack_for_test));
//
//     // stack_for_test.inf_adr_error.current_error = 4097;
//     stack_dump(&stack_for_test);
//
//     // stack_push(&stack_for_test, 1e9);
//     // stmn_t buffer_place = 0;
//     // stack_pop(&stack_for_test, &buffer_place);
//     // stack_pop(&stack_for_test, &buffer_place);
//
//     stack_destruct(&stack_for_test);
    return 0;
}








