#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "S_stack.h"
#include "color.h"





stack_error_t stack_stk(stack_struct* stack_address, const size_t start_capacity,
                        char* file_name, int line, char* stack_name) {
    assert(stack_address);
    assert(file_name);
    assert(stack_name);
//
//     printf("Capacity - %d\n", start_capacity);
//     printf("File - %s\n", file_name);
//     printf("Line - %d\n", line);
//     printf("Name - %s\n", stack_name);

    if (MOD_START == DEBUG && start_capacity == 0) {
        printf("%sWARNING!!! Start capacity = 0%s\n", _P_, _N_);
    }

    int* buffer_address = (int*) calloc(start_capacity, sizeof(int));

    STACK_STR_ADDRESS_CHECK(stack_address);

    stack_address->data = buffer_address;
    stack_address->capacity = start_capacity;
    stack_address->size = 0;

    for (size_t i = 0; i < start_capacity; i++) {
        buffer_address[i] = POISON_NUM;
    }

    STACK_STR_INF(stack_address);

    return NOT_ERRORS;
}


int stack_destruct(stack_struct* stack_address) {
    assert(stack_address);

    free(stack_address->data);
    return 0;
}


stack_error_t stack_push(stack_struct* stack_address, const int mean_to_push) {
    assert(stack_address);

    DUMP_NOT_CORRECT_STACK(stack_address);
    STACK_PUSH_CHECK(stack_address);

    stack_address->data[stack_address->size++] = mean_to_push;


    DUMP_NOT_CORRECT_STACK(stack_address);

    return NOT_ERRORS;
}


stack_error_t stack_pop(stack_struct* stack_address, int* mean_pop_address) {
    assert(stack_address);
    assert(mean_pop_address);

    DUMP_NOT_CORRECT_STACK(stack_address);
    STACK_POP_CHECK(stack_address);

    *mean_pop_address = stack_address->data[--(stack_address->size)];
    // stack_address->data[stack_address->size + 1] = POISON_NUM;


    DUMP_NOT_CORRECT_STACK(stack_address);

    return NOT_ERRORS;
}

#if MOD_START == DEBUG
int stack_error(stack_struct* stack_address) {
    // Нужно возвращать int для передачи не одной ошибки, а нескольких

    assert(stack_address);

    int return_error = 0;

    if (stack_address->data < (int*) MIN_ADDRESS && stack_address->capacity != 0) {
        return_error |= BAD_DATA_ADDRESS; // 1
    }

    if (stack_address->size < 0) {
        return_error |= BAD_SIZE; // 2
    }

    if (stack_address->capacity < 1 &&
    (return_error & BAD_DATA_ADDRESS) == BAD_DATA_ADDRESS) {
        return_error |= BAD_CAPACITY; // 4
    }

    if (stack_address->size > 0 &&
    stack_address->data[(stack_address->size) - 1] == POISON_NUM) { // Можем читать и при плохом адресе
        return_error |= BAD_CURRENT_ELEMENT; // 8             // Но не знаю, стоит ли
    }                                                         // Как вариант, добавить проверку на правильность адреса

    if (stack_address->size > stack_address->capacity) { // Даже если они разного знака, то это ошибка
        return_error |= SIZE_BIGGER_CAPACITY; // 16
    }

    stack_address->inf_adr_error.current_error = return_error;

    return return_error;
}

#else
int stack_error(stack_struct* stack_address) {
    printf("ERROR ith stack_error in USER_MODE\n");
}
#endif // MOD_START == DEBUG



stack_error_t stack_realloc(stack_struct* stack_address,
                            const size_t size_of_stack) {
    assert(stack_address);

    DUMP_NOT_CORRECT_STACK(stack_address);
    STACK_REALLOC_SIZE(stack_address);

    int* buffer_address = (int*) realloc(stack_address->data, size_of_stack * sizeof(int));

    STACK_REALLOC_ADDRESS(stack_address);

    stack_address->data = buffer_address;

    return NOT_ERRORS;
}

#if MOD_START == DEBUG
int stack_dump(stack_struct* stack_address) {
    assert(stack_address);

    int error_with_stack = stack_address->inf_adr_error.current_error;

    printf("\n%s===============================================================================\n", _R_);
    printf("--- STACK DUMP ---%s\n", _N_);
    printf("%sstack %s<int> [%p]%s from %s%s:%d %sname stack:%s %s%s \nERRORS: \n",
            _P_,   _B_, stack_address, _R_, _B_,
            stack_address->inf_adr_location.creation_file,
            stack_address->inf_adr_location.creation_line, _P_, _B_,
            stack_address->inf_adr_location.name_stack, _R_);

    print_errors_for_dump(error_with_stack);
    printf("In Function: %s:%d\n", stack_address->inf_adr_error.error_file,
                                  stack_address->inf_adr_error.error_line);
    // printf("Number Of Error: %d\n", stack_address->inf_adr_error.current_error);
    if ((error_with_stack & BAD_REALLOC) == BAD_REALLOC) {
        printf("--- ERROR with realloc\n");
        printf("--- Size >= New Size\n%s", _P_);
            printf("===============================================================================\n%s", _N_);
        return 0;
    }

    if ((error_with_stack & BAD_CREATE_CALLOC) == BAD_CREATE_CALLOC) {
        printf("--- ERROR with calloc\n");
        printf("--- calloc return NULL\n%s", _P_);
            printf("===============================================================================\n%s", _N_);
        return 0;
    }

    if ((error_with_stack & LOSE_MEANS) == LOSE_MEANS) {
        printf("--- ERROR with realloc\n");
        printf("--- realloc return NULL%s\n", _P_);
            printf("===============================================================================\n%s", _N_);
        return 0;
    }

    printf("%s{\n", _P_);

    printf("size = %s%zd%s\n", _B_, stack_address->size, _P_);
    printf("capacity = %s%zd%s\n", _B_, stack_address->capacity, _P_);
    printf("data %s[%p]%s\n", _B_, stack_address->data, _P_);

    printf("    {\n");
    for (int i = 0; i < 1/*AMOUNT_PRINT_ELEMENT*/; i++) {
        printf("   ");

        if ((error_with_stack & BAD_SIZE) != BAD_SIZE && i < stack_address->size) {
            printf("*");
        }
        else {
            printf(" ");
        }

        printf("%d = %s%d%s\n", i, _B_, stack_address->data[i], _P_);
    }
    printf("    }\n");
    printf("}\n");
    printf("%s===============================================================================\n%s",_P_, _N_);
    return 0;
}

#else
int stack_dump(stack_struct* stack_address) {
    printf("ERROR with dump in USER_MOD\n");
}

#endif //MOS_START == DEBUG



#if MOD_START == DEBUG
void print_errors_for_dump(const int error_with_stack){
    int buffer = 0;
    for (int i = 1; i < MUST_STOP; i <<= 1) {
        if ((error_with_stack & i) == i) {
            printf("     %s (%d) \n", ALL_ERRORS[buffer], i);
        }
        buffer++;
    }
}

#else
void print_errors_for_dump(const int error_with_stack) {
    printf("ERROR with print_errors_for_dump in USER_MOD\n");
}
#endif // MOD_START == DEBUG

