#ifndef S_STACK_H
#define S_STACK_H
#include <stdio.h>

enum work_mode{
    FOR_USERS = 0,
    DEBUG = 1
};

const int POISON_NUM = 0; //* Если мы планируем добавлять другие типы с невозможными значениями
const int MIN_ADDRESS = 8000;

#define MOD_START 0
#define STRUCT_INFORMATION

// #if MOD_START == 1
//    #define STRUCT_INFORMATION \
//     error_inf inf_adr_error; \
//     location_inf inf_adr_location; \
// #else
//    #define STRUCT_INFORMATION /*Nothing*/
// #endif


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
//
// struct stack_struct{
//    int* data;
//    ssize_t size;
//    ssize_t capacity;
//
//    STRUCT_INFORMATION
//    // error_inf inf_adr_error;
//    // location_inf inf_adr_location;
// };



#if MOD_START == 1
   #define STRUCT_INFORMATION \
    error_inf inf_adr_error; \
    location_inf inf_adr_location;

struct stack_struct{
   int* data;
   ssize_t size;
   ssize_t capacity;

   STRUCT_INFORMATION
};

   #define ERROR_FUNC_RETURN(stack_address) { \
    (stack_address)->inf_adr_error.error_file = __FILE__; \
    (stack_address)->inf_adr_error.error_line = __LINE__; \
    stack_dump(stack_address); \
    return MUST_STOP; \
   }

   #define STACK_STR_INF(stack_address) { \
    (stack_address)->inf_adr_location.name_stack = stack_name; \
    (stack_address)->inf_adr_location.creation_file = file_name; \
    (stack_address)->inf_adr_location.creation_line = line; \
    \
    (stack_address)->inf_adr_error.current_error = NOT_ERRORS; \
    (stack_address)->inf_adr_error.error_file = NULL; \
    (stack_address)->inf_adr_error.error_line = NULL; \
   }

   #define STACK_STR_ADDRESS_CHECK(stack_address) { \
    if (buffer_address == NULL) { \
       (stack_address)->inf_adr_error.current_error = BAD_CREATE_CALLOC; \
       ERROR_FUNC_RETURN(stack_address); \
    }\
   }

   #define STACK_PUSH_CHECK(stack_address) { \
    if ((stack_address)->capacity <= stack_address->size) { \
       (stack_address)->inf_adr_error.current_error = BAD_PUSH_SIZE; \
       ERROR_FUNC_RETURN(stack_address); \
    }\
   }

   #define STACK_POP_CHECK(stack_address) { \
    if ((stack_address)->size < 1) { \
       (stack_address)->inf_adr_error.current_error = BAD_POP_SIZE; \
       ERROR_FUNC_RETURN(stack_address); \
    } \
   }

   #define STACK_REALLOC_SIZE(stack_address) { \
    if ((stack_address)->size > size_of_stack) { \
       (stack_address)->inf_adr_error.current_error = BAD_REALLOC; \
       ERROR_FUNC_RETURN(stack_address); \
    } \
   }

   #define STACK_REALLOC_ADDRESS(stack_address){ \
    if (buffer_address == NULL) { \
       (stack_address)->inf_adr_error.current_error = LOSE_MEANS; \
       ERROR_FUNC_RETURN(stack_address); \
    } \
   }

   #define DUMP_NOT_CORRECT_STACK(stack_address) { \
    if (stack_error(stack_address) != NOT_ERRORS) { \
      ERROR_FUNC_RETURN(stack_address); \
    } \
   }

#else

struct stack_struct{
   int* data;
   ssize_t size;
   ssize_t capacity;

   STRUCT_INFORMATION
   // error_inf inf_adr_error;
   // location_inf inf_adr_location;
};
   #define ERROR_FUNC_RETURN(stack_address) (void(0))
   #define STACK_STR_INF(stack_address) (void(0))
   #define STACK_STR_ADDRESS_CHECK(stack_address) (void(0))
   #define STACK_PUSH_CHECK(stack_address) (void(0))
   #define STACK_POP_CHECK(stack_address) (void(0))
   #define STACK_REALLOC_SIZE(stack_address) (void(0))
   #define STACK_REALLOC_ADDRESS(stack_address) (void(0))
   #define DUMP_NOT_CORRECT_STACK(stack_address) (void(0))
#endif // MOD_START == 1

// const work_mode MOD_START = DEBUG;
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


#endif // S_STACK_H


