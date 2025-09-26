#include <stdio.h>
#include <stdlib.h>

#include "S_stack.h"
#include "color.h"

int main() {
    stack_struct stack_for_test = {};
    stack_stk(&stack_for_test, 10, __FILE__, __LINE__, NAME_RETURN(stack_for_test));

    // printf("Stack Error: %d\?n", stack_error(&stack_for_test));

    stack_for_test.inf_adr_error.current_error = 1000;
    stack_dump(&stack_for_test);

    // stack_push(&stack_for_test, 10);
    // int buffer_place = 0;
    // stack_pop(&stack_for_test, &buffer_place);
    // stack_pop(&stack_for_test, &buffer_place);

    stack_destruct(&stack_for_test);
    return 0;
}








