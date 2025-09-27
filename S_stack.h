#ifndef S_STACK_H
#define S_STACK_H
#include <stdio.h>

//TODO Undef all name
//TODO Check size and capacity < MAX

typedef long long int stmn_t;
const char name_type[] = "long long int";
//! При смене типа меняем спецификатор ввода
#define PRINT_ELEMENT(num) { \
   printf("%lld", num); \
}

const stmn_t MAX_MEAN = 1e8;
const stmn_t MIN_MEAN = -1e8;


const stmn_t POISON_NUM = 0; //* Если мы планируем добавлять другие типы с невозможными значениями
const stmn_t BIRD_NUM = 0; //* Чисто для теста
const int SIZE_ADD_CAPACITY = 0;

const int MIN_ADDRESS = 8000;
const int AMOUNT_PRINT_ELEMENT = 10;
const int MODIFICATOR_REALLOC = 2;


#define USER_MOD 0
#define DEBUG 1
#define AUTO_REALLOC 0
#define NOT_AUTO_REALLOC 1


#define MOD_START USER_MOD
#define REALLOC_TYPE NOT_AUTO_REALLOC
#define COMPLETION_DATA 0


#define STRUCT_INFORMATION

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



#if MOD_START == DEBUG
   #define STRUCT_INFORMATION \
    error_inf inf_adr_error; \
    location_inf inf_adr_location;

struct stack_struct{
   stmn_t* data;
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

   #define STACK_STR_CAPACITY_CHECK(stack_address, start_capacity) { \
    if (start_capacity < 0) { \
        stack_address->inf_adr_error.current_error = BAD_CAPACITY; \
        stack_address->capacity = start_capacity; \
        ERROR_FUNC_RETURN(stack_address); \
    } \
   }

   #define STACK_STR_ADDRESS_CHECK(stack_address, buffer_address) { \
    if (buffer_address == NULL) { \
       (stack_address)->inf_adr_error.current_error = BAD_CREATE_CALLOC; \
       ERROR_FUNC_RETURN(stack_address); \
    }\
   }

   #if REALLOC_TYPE == AUTO_REALLOC
   #define STACK_PUSH_CHECK(stack_address) { \
    if ((stack_address)->capacity <= stack_address->size) { \
       stack_realloc(stack_address); \
    }\
   }

   #else // NOT_AUTO_REALLOC
   #define STACK_PUSH_CHECK(stack_address) { \
    if ((stack_address)->capacity <= stack_address->size) { \
       (stack_address)->inf_adr_error.current_error = BAD_PUSH_SIZE; \
       ERROR_FUNC_RETURN(stack_address); \
    }\
   }

   #endif // REALLOC_TYPE == AUTO_REALLOC

   #define STACK_PUSH_NUM_CHECK(stack_address, push_mean) { \
      if (push_mean > MAX_MEAN || push_mean < MIN_MEAN) { \
         stack_address->inf_adr_error.current_error = PUSH_MEAN_WITHOUT_LIMIT; \
         ERROR_FUNC_RETURN(stack_address); \
      } \
   }


   #define STACK_POP_CHECK(stack_address) { \
    if ((stack_address)->size < 1 + SIZE_ADD_CAPACITY) { \
       (stack_address)->inf_adr_error.current_error = BAD_POP_SIZE; \
       ERROR_FUNC_RETURN(stack_address); \
    } \
   }

   // #define STACK_REALLOC_SIZE(stack_address) { \
   //  if ((stack_address)->size > ) { \
   //     (stack_address)->inf_adr_error.current_error = BAD_REALLOC; \
   //     ERROR_FUNC_RETURN(stack_address); \
   //  } \
   // }

   #define STACK_REALLOC_ADDRESS(stack_address, buffer_address){ \
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
   stmn_t* data;
   ssize_t size;
   ssize_t capacity;

   STRUCT_INFORMATION
   // error_inf inf_adr_error;
   // location_inf inf_adr_location;
};
   #define ERROR_FUNC_RETURN(stack_address) (void(0))
   #define STACK_STR_CAPACITY_CHECK(stack_addres, start_capacity) (void(0))
   #define STACK_STR_INF(stack_address) (void(0))
   #define STACK_STR_ADDRESS_CHECK(stack_address, buffer_address) (void(0))
   #define STACK_PUSH_CHECK(stack_address) (void(0))
   #define STACK_PUSH_NUM_CHECK(stack_address, mean_to_push) (void(0))
   #define STACK_POP_CHECK(stack_address) (void(0))
   #define STACK_REALLOC_SIZE(stack_address) (void(0))
   #define STACK_REALLOC_ADDRESS(stack_address, buffer_address) (void(0))
   #define DUMP_NOT_CORRECT_STACK(stack_address) (void(0))
#endif // MOD_START == DEBUG

#define MIN_INT(size, amount_elements) (size < amount_elements ? size : amount_elements)


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
    PUSH_MEAN_WITHOUT_LIMIT = 2048,
    BIRD_NOT_CORRECT = 4096,
    MUST_STOP = 8192
};


const char ALL_ERRORS[20][40] = {"BAD_DATA_ADDRESS",
                                "BAD_SIZE",
                                "BAD_CAPACITY",
                                "BAD_CURRENT_ELEMENT",
                                "SIZE_BIGGER_CAPACITY",
                                "BAD_PUSH_SIZE",
                                "BAD_PUSH_MEAN",
                                "BAD_POP_SIZE",
                                "BAD_REALLOC",
                                "LOSE_MEANS",
                                "BAD_CREATE_CALLOC",
                                "PUSH_MEAN_WITHOUT_LIMIT",
                                "BIRD_NOT_CORRECT",
                                "MUST_STOP"
};


int stack_error(stack_struct* stack_address);

int stack_dump(stack_struct* stack_address);

void print_errors_for_dump(const int error_with_stack);

void print_error(const int error_with_stack);

void print_stack_for_dump(stack_struct* stack_address, const int error_with_stack);


stack_error_t stack_pop(stack_struct* stack_address, stmn_t* mean_pop_address);

stack_error_t stack_push(stack_struct* stack_address, const stmn_t mean_to_push);


stack_error_t stack_stk(stack_struct* stack_address, const ssize_t start_capacity,
                        char* file_name, const int line_number, char* stack_name);

stack_error_t stack_realloc(stack_struct* stack_address);

int stack_destruct(stack_struct* stack_address);



#define NAME_RETURN(NAME_FILE) { #NAME_FILE }


#endif // S_STACK_H


