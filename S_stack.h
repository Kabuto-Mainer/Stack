#ifndef S_STACK_H
#define S_STACK_H
#include <stdio.h>

enum work_mode{
    FOR_USERS = 0,
    DEBUG = 1
};

const int POISON_NUM = 0; //* Если мы планируем добавлять другие типы с невозможными значениями
const int MIN_ADDRESS = 8000;

#define MOD_START 1

#if MOD_START == 1
    #define

const work_mode MOD_START = DEBUG;
const int AMOUNT_PRINT_ELEMENT = 10;





enum stack_error_t{
    NOT_ERRORS = 0,
    BAD_DATA_ADDRESS = 1,
    BAD_SIZE = 2,
    BAD_CAPACITY = 4,
    BAD_CURRENT_ELEMENT = 8,
    SIZE_BIGGER_CAPACITY = 16,
    BAD_PUSH_SIZE = 32,
    BAD_PUSH_MEAN = 64,
    BAD_POP_SIZE = 128,
    BAD_REALLOC = 256,
    LOSE_MEANS = 512,
    BAD_CREATE_CALLOC = 1024,
    MUST_STOP = 2048
};


const char ALL_ERRORS[20][40] = {"BAD_DATA_ADDRESS",
                                "BAD_SIZE",
                                "BAD_CAPACITY",
                                "BAD_CURRENT_ELEMENT",
                                "SIZE_BIGGER_CAPACITY",
                                "BAD_PUSH_SIZE",
                                "BAD_PUSH_MEAN",
                                "BAD_POP_SIZE",
                                "MUST_STOP",
                                "BAD_REALLOC",
                                "LOSE_MEANS",
                                "BAD_CREATE_CALLOC"
};
// const char DESCRIPTION

struct error_inf{
   int current_error;
   char* error_file;
   int error_line;
};

struct location_inf{
   char* name_stack;
   char* creation_file;
   int creation_line;
};

struct stack_struct{
   int* data;
   ssize_t size;
   ssize_t capacity;

   //TODO Define, что бы можно было делать режим отладки и режим обычного использования
   #if MOD_START == 1
       #define
   error_inf inf_adr_error;
   location_inf inf_adr_location;
};



int stack_error(stack_struct* stack_address);



int stack_dump(stack_struct* stack_address);

void print_errors_for_dump(const int error_with_stack);



stack_error_t stack_pop(stack_struct* stack_address, int* mean_pop_address);

stack_error_t stack_push(stack_struct* stack_address, const int mean_to_push);



stack_error_t stack_stk(stack_struct* stack_address, const size_t start_capacity,
                        char* file_name, const int line_number, char* stack_name);

stack_error_t stack_realloc(stack_struct* stack_address,
                            const size_t size_of_stack);

int stack_destruct(stack_struct* stack_address);



#define NAME_RETURN(NAME_FILE) { #NAME_FILE }

//TODO Rename!
#define ERROR_FUNC_RETURN(stack_address) { \
 stack_address->inf_adr_error.error_file = __FILE__; \
 stack_address->inf_adr_error.error_line = __LINE__; \
 stack_dump(stack_address); \
 return MUST_STOP; \
}

//TODO Аналогично
#define DUMP_NOT_CORRECT_STACK(stack_address) { \
 if (stack_error(stack_address) != NOT_ERRORS) { \
    ERROR_FUNC_RETURN(stack_address); \
 } \
}


// #define CHECK_CORRECT_PUSH_SIZE(stack_address) { \
//  if (stack_address->size == stack_address->capacity) { \
//     stack_address->current_error = BAD_PUSH_SIZE; \ // Можем так сделать, т.к. заранее известно, что стек правильный
//     \
//     stack_address->error_file = __FILE__; \
//     stack_address->error_line = __LINE__; \
//     \
//     stack_dump(stack_address);\
//     return MUST_STOP; \
//  } \
// }
//
// #define CHECK_CORRECT_PUSH_MEAN(stack_address, mean_to_push) { \
//  if (mean_to_push == POISON_NUM) { \
//     stack_address->current_error = BAD_PUSH_MEAN; \
//     \
//     stack_address->error_file = __FILE__; \
//     stack_address->error_line = __LINE__; \
//     \
//     stack_dump(stack_address);\
//     return MUST_STOP; \
//  } \
// }
//
// #define CHECK_CORRECT_POP(stack_address) { \ // Нам не нужно проверять текущий элемент, т.к. этим занимается DUMP_NOT_CORRECT_STACK
//  if (stack_address->size == 0) { \
//     stack_address->current_error = BAD_POP_SIZE; \ // Можем так сделать, т.к. заранее известно, что стек правильный
//     \
//     stack_address->error_file = __FILE__; \
//     stack_address->error_line = __LINE__; \
//     \
//     stack_dump(stack_address);\
//     return MUST_STOP; \
//  } \
// }
//
// stack_error_t stack_stk(stack_struct* stack_address, const size_t start_capacity,
//                         const char* file_name, const char* line_number, const char* stack_name);


// stack_error_t stack_stk(stack_struct* stack_address, const size_t start_capacity,
//                         char* file_name, char* line_number);
//
//
// stack_error_t stack_push(stack_struct* stack_address);
//
// stack_error_t stack_error();
//
// stack_error_t stack_pop(stack_struct* stack_address, int* mean_pop_address);
















#endif // S_STACK_H
