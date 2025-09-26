#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "S_stack.h"
#include "color.h"





stack_error_t stack_stk(stack_struct* stack_address, const ssize_t start_capacity,
                        char* file_name, int line, char* stack_name) {
    // assert(stack_address);
    assert(file_name);
    assert(stack_name);

    if (file_name == NULL) {
        printf("NULL ADDRESS: %s:%d  Name: %s\n", file_name, line, stack_name);
        return MUST_STOP;
    }
//
//     printf("Capacity - %d\n", start_capacity);
//     printf("File - %s\n", file_name);
//     printf("Line - %d\n", line);
//     printf("Name - %s\n", stack_name);

    if (MOD_START == DEBUG && start_capacity == 0) {
        printf("%sWARNING!!! Start capacity = 0%s\n", _P_, _N_);
    }

    stack_address->capacity = start_capacity;
    stack_address->size = 0;

    STACK_STR_INF(stack_address);
    STACK_STR_CAPACITY_CHECK(stack_address, start_capacity);
    // printf("%zu\n", start_capacity);
    stmn_t* buffer_address = (stmn_t*) calloc(start_capacity, sizeof(stmn_t));

    STACK_STR_ADDRESS_CHECK(stack_address, buffer_address);

    stack_address->data = buffer_address;
    // stack_address->capacity = start_capacity;
    // stack_address->size = 0;

    for (size_t i = 0; i < start_capacity; i++) {
        buffer_address[i] = POISON_NUM;
    }

    // STACK_STR_INF(stack_address);

    return NOT_ERRORS;
}


int stack_destruct(stack_struct* stack_address) {
    assert(stack_address);

    free(stack_address->data);
    return 0;
}


stack_error_t stack_push(stack_struct* stack_address, const stmn_t mean_to_push) {
    assert(stack_address);

    // printf("%d\n", mean_to_push);
    DUMP_NOT_CORRECT_STACK(stack_address);
    STACK_PUSH_CHECK(stack_address);
    STACK_PUSH_NUM_CHECK(stack_address, mean_to_push);

    stack_address->data[stack_address->size++] = mean_to_push;


    DUMP_NOT_CORRECT_STACK(stack_address);

    return NOT_ERRORS;
}


stack_error_t stack_pop(stack_struct* stack_address, stmn_t* mean_pop_address) {
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

    if (stack_address->data < (stmn_t*) MIN_ADDRESS && stack_address->capacity != 0) {
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
    printf("ERROR with stack_error in USER_MODE\n");
    return 0;
}
#endif // MOD_START == DEBUG



stack_error_t stack_realloc(stack_struct* stack_address) {
    assert(stack_address);

    DUMP_NOT_CORRECT_STACK(stack_address);
    // STACK_REALLOC_SIZE(stack_address);

    stmn_t* buffer_address = (stmn_t*) realloc(stack_address->data,
                                            stack_address->capacity * MODIFICATOR_REALLOC * sizeof(stmn_t));

    STACK_REALLOC_ADDRESS(stack_address, buffer_address);

    stack_address->capacity *= MODIFICATOR_REALLOC;
    stack_address->data = buffer_address;

    return NOT_ERRORS;
}

#if MOD_START == DEBUG
int stack_dump(stack_struct* stack_address) {
    assert(stack_address);

    int error_with_stack = stack_address->inf_adr_error.current_error;

    printf("\n%s===============================================================================\n", _R_);
    printf("--- STACK DUMP ---%s\n", _N_);
    printf("%sstack %s<%s> [%p]%s from %s%s:%d %sname stack:%s %s%s \nERRORS: \n",
            _P_,   _B_, name_type, stack_address, _R_, _B_,
            stack_address->inf_adr_location.creation_file,
            stack_address->inf_adr_location.creation_line, _P_, _B_,
            stack_address->inf_adr_location.name_stack, _R_);

    print_errors_for_dump(error_with_stack);
    printf("In Function: %s:%d\n\n", stack_address->inf_adr_error.error_file,
                                  stack_address->inf_adr_error.error_line);
    print_error(error_with_stack);

    if ((error_with_stack & BAD_CREATE_CALLOC) == BAD_CREATE_CALLOC ||
        (error_with_stack & BAD_DATA_ADDRESS) == (BAD_DATA_ADDRESS) ||
        (error_with_stack & BAD_REALLOC) == BAD_REALLOC ||
        stack_address->size < 1) {
        printf("%s===============================================================================\n%s",_P_, _N_);
        return 0;
    }

    printf("%s{\n", _P_);

    printf("size = %s%zd%s\n", _B_, stack_address->size, _P_);
    printf("capacity = %s%zd%s\n", _B_, stack_address->capacity, _P_);
    printf("data %s[%p]%s\n", _B_, stack_address->data, _P_);

    printf("    {\n");

    print_stack_for_dump(stack_address, error_with_stack);
//     for (int i = 0; i < MIN_INT(stack_address->size, AMOUNT_PRINT_ELEMENT); i++) {
//         printf("   ");
//
//         if ((error_with_stack & BAD_SIZE) != BAD_SIZE && i < stack_address->size) {
//             printf("*");
//         }
//         else {
//             printf(" ");
//         }
//
//         // printf("%d = %s%d%s\n", i, _B_, stack_address->data[i], _P_); //TODO
//         printf("%d = %s%d%s\n", i, _B_, stack_address->data[i], _P_);
//     }
    printf("    }\n");
    printf("}\n");
    printf("%s===============================================================================\n%s",_P_, _N_);
    return 0;
}

#else
int stack_dump(stack_struct* stack_address) {
    printf("ERROR with dump in USER_MOD\n");
    return 0;
}

printf(_R_ "-- %s ---\n", ALL_ERRORS[]);

#endif //MOS_START == DEBUG

void print_error(const int error_with_stack) {
    if ((error_with_stack & BAD_DATA_ADDRESS) == BAD_DATA_ADDRESS) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[0]);
        printf("Data Address < %d\n%s\n", MIN_ADDRESS, _N_);
    }

    if ((error_with_stack & BAD_SIZE) == BAD_SIZE) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[1]);
        printf("Size In Stack < 0\n%s\n", _N_);
    }

    if ((error_with_stack & BAD_CAPACITY) == BAD_CAPACITY) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[2]);
        printf("Capacity < 0\n%s\n", _N_);
    }

    if ((error_with_stack & BAD_CURRENT_ELEMENT) == BAD_CURRENT_ELEMENT) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[3]);
        printf("Current Element Is Poison (%d)\n%s\n", POISON_NUM, _N_);
    }

    if ((error_with_stack & SIZE_BIGGER_CAPACITY) == SIZE_BIGGER_CAPACITY) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[4]);
        printf("Current Size Is Bigger Then Capacity\n%s\n", _N_);
    }

    if ((error_with_stack & BAD_PUSH_SIZE) == BAD_PUSH_SIZE) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[5]);
        printf("In Mode NOT_AUTO_REALLOC\n");
        printf("Size == Capacity \n%s\n", _N_);
    }

    if ((error_with_stack & BAD_PUSH_MEAN) == BAD_PUSH_MEAN) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[6]);
        printf("Push Element == Poison (%d) \n%s\n", POISON_NUM, _N_);
    }

    if ((error_with_stack & BAD_POP_SIZE) == BAD_POP_SIZE) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[7]);
        printf("Call Pop When Size == 0\n%s\n", _N_);
    }

    if ((error_with_stack & BAD_REALLOC) == BAD_REALLOC) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[8]);
        printf("Realloc return NULL\n\n" _N_);
    }

    if ((error_with_stack & LOSE_MEANS) == LOSE_MEANS) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[9]);
        printf("New Capacity Of Stack < Current Size\n%s\n", _N_);
    }

    if ((error_with_stack & BAD_CREATE_CALLOC) == BAD_CREATE_CALLOC) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[10]);
        printf("Calloc Return Null\n%s\n", _N_);
    }

    if ((error_with_stack & PUSH_MEAN_WITHOUT_LIMIT) == PUSH_MEAN_WITHOUT_LIMIT) {
        printf(_R_ "-- %s ---\n", ALL_ERRORS[11]);
        printf("Push Mean > %ld or < %ld\n%s\n", MAX_MEAN, MIN_MEAN, _N_);
    }
}




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

void print_stack_for_dump(stack_struct* stack_address, const int error_with_stack) {
    for (int i = 0; i < AMOUNT_PRINT_ELEMENT; i++) {
        printf("   ");

        if ((error_with_stack & BAD_SIZE) != BAD_SIZE && i < stack_address->size) {
            printf("*");
        }
        else {
            printf(" ");
        }
        printf("%d = %s", i, _B_);
        PRINT_ELEMENT(stack_address, i);
        printf("%s\n", _P_);
    }
}

#else
void print_errors_for_dump(const int error_with_stack) {
    printf("ERROR with print_errors_for_dump in USER_MODE\n");
}

void print_stack_for_dump(stack_struct* stack_address, const int error_with_stack) {
    printf("ERROR with print_stack_for_dump in USER_MODE\n");
}
#endif // MOD_START == DEBUG

