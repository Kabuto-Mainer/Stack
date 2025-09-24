#include <stdio.h>
#include <stdlib.h>

#include "S_stack.h"
#include "color.h"

int main() {
    stack_struct stack_for_test = {};
    stack_stk(&stack_for_test, 1, __FILE__, __LINE__, NAME_RETURN(stack_for_test));

    // printf("Stack Error: %d\n", stack_error(&stack_for_test));

    free(stack_for_test.data);
    stack_push(&stack_for_test, 10);

    int buffer_place = 0;

    stack_pop(&stack_for_test, &buffer_place);

    // printf("Buffer Place = %d\n", buffer_place);

    free(stack_for_test.data); //TODO Загнать в функцию
    return 0;
}








