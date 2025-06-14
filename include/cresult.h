#ifndef CRESULT_H
#define CRESULT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Error type
typedef struct {
  char *message;
  char *file_name;
  size_t line_number;
} cresult_error;

// Creates an error with file and line info
cresult_error cresult_error_create(char *message, char *file_name, size_t line_number);

#define CRESULT_ERROR(message) (cresult_error_create(message, __FILE__, __LINE__))

// Prints a cresult_error to stderr
void cresult_error_print(cresult_error err);

// Result type
typedef struct {
  void *data;
  bool is_err;
  cresult_error err;
  bool is_spent;
} cresult_result;

// Constructs a success result
cresult_result cresult_result_success(void *data);

// Constructs a failure result
cresult_result cresult_result_failure(cresult_error err);

// Macro to generate a failed result
#define CRESULT_FAILURE(message) (cresult_result_failure(cresult_error_create((message), __FILE__, __LINE__)))

// Inspects the result: exits if error, returns result otherwise
cresult_result cresult_result_on_error_exit(cresult_result *result);

// Inspects the result: warns if error, returns result otherwise
cresult_result cresult_result_on_error_warn(cresult_result *result);

// Inspects the result: warns if error, returns result otherwise
cresult_result cresult_result_on_error_fallback(cresult_result *result, cresult_result *fallback_result);

// Transfers ownership from the result type to the caller
void *cresult_result_take(cresult_result *result);

#endif // CRESULT_H
