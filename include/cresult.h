#ifndef CRESULT_H
#define CRESULT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Error type
typedef struct {
  char* message;
  char* file_name;
  size_t line_number;
} cresult_error;

// Creates an error with file and line info
cresult_error cresult_error_create(char* message, char* file_name, size_t line_number);

// Prints a cresult_error to stderr
void cresult_error_print(cresult_error err);

// Result type
typedef struct {
  void* data;
  void (*destructor)(void*);
  bool is_err;
  cresult_error err;
} cresult_result;

// Constructs a success result
cresult_result* cresult_result_success(void* data, void (*destructor)(void*));

// Constructs a failure result
cresult_result* cresult_result_failure(cresult_error err);

// Macro to generate a failed result
#define CRESULT_FAILURE(message) (cresult_result_failure(cresult_error_create((message), __FILE__, __LINE__)))

// Inspects the result: exits if error, returns result otherwise
cresult_result* cresult_result_force(cresult_result* result);

// Frees both the result and its contained data (if applicable)
void cresult_result_destroy(cresult_result* result);

#endif // CRESULT_H
