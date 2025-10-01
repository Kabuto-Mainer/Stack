#ifndef S_DEFINE_H
#define S_DEFINE_H

#include <stdio.h>
#include "stack.h"
#include "const.h"



#ifndef MOD_WORK
#define MOD_WORK PROCESSOR
#endif
//! Выбор типа работы


#if MOD_WORK == PROCESSOR

//-------------------------------------
#ifndef AUTO_REALLOC
#define AUTO_REALLOC OFF
#endif

#ifndef COMPLETION_DATA
#define COMPLETION_DATA OFF
#endif

#ifndef HASH_SECURE
#define HASH_SECURE OFF
#endif

#ifndef BIRD_SECURE
#define BIRD_SECURE OFF
#endif
//-------------------------------------

struct stack_struct{
   stmn_t* data;
   ssize_t size;
   ssize_t capacity;
};

//---------------------------------------------
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
//-------------------------------------------------
#endif



#if MOD_WORK == DEBUG

//-------------------------------------
#ifndef BIRD_SECURE
#define BIRD_SECURE ON
#endif

#ifndef HASH_SECURE
#define HASH_SECURE ON
#endif

#ifndef COMPLETION_DATA
#define COMPLETION_DATA ON
#endif
//-------------------------------------



struct error_inf{
   int current_error;
   const char* error_file;
   int error_line;
};

struct location_inf{
   const char* name_stack;
   const char* creation_file;
   int creation_line;
};


#if HASH_SECURE == ON

   struct hash_inf{
      ssize_t hash_code;
      // int start_code; // Можно в дальнейшем добавить в качестве усложнения для взлома
   };

   #define STRUCT_HASH \
    hash_inf inf_hash_code;


   #define CHECK_HASH_CODE(stack_address, return_error) { \
    ssize_t new_hash = make_hash_code(stack_address); \
   \
    if (new_hash != stack_address->inf_hash_code.hash_code) { \
        return_error |= BAD_HASH; \
    } \
   }

   #define REPLACE_HASH_CODE(stack_address) { \
    (stack_address)->inf_hash_code.hash_code = make_hash_code(stack_address); \
   }

#endif // HASH_SECURE == 1



#define STRUCT_INFORMATION \
   error_inf inf_adr_error; \
   location_inf inf_adr_location;


struct stack_struct{
   stmn_t* data;
   ssize_t size;
   ssize_t capacity;

   STRUCT_INFORMATION

#ifdef STRUCT_HASH
   STRUCT_HASH
#endif
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
   (stack_address)->inf_adr_error.error_line = 0; \
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


#if AUTO_REALLOC == AUTO_REALLOC
#define STACK_PUSH_CHECK(stack_address) { \
   if ((stack_address)->capacity <= stack_address->size + 2 * SIZE_ADD_CAPACITY) { \
      stack_realloc(stack_address); \
   }\
}

#else // NOT_AUTO_REALLOC
#define STACK_PUSH_CHECK(stack_address) { \
   if ((stack_address)->capacity <= stack_address->size + 2 * SIZE_ADD_CAPACITY) { \
      (stack_address)->inf_adr_error.current_error = BAD_PUSH_SIZE; \
      ERROR_FUNC_RETURN(stack_address); \
   }\
}
#endif // AUTO_REALLOC == AUTO_REALLOC


#define STACK_PUSH_NUM_CHECK(stack_address, push_mean) { \
   if (push_mean > MAX_MEAN || push_mean < MIN_MEAN) { \
      stack_address->inf_adr_error.current_error = PUSH_MEAN_WITHOUT_LIMIT; \
      ERROR_FUNC_RETURN(stack_address); \
   } \
}

#define STACK_POP_CHECK(stack_address) { \
   if ((stack_address)->size < 1) { \
      (stack_address)->inf_adr_error.current_error = BAD_POP_SIZE; \
      ERROR_FUNC_RETURN(stack_address); \
   } \
}

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

#endif // MOD_START == DEBUG



#define MIN_INT(size, amount_elements) (size < amount_elements ? size : amount_elements)
#define NAME_RETURN(NAME_FILE) { #NAME_FILE }

#endif //S_DEFINE_H
