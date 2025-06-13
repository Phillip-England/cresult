#include "cresult.h"
#include <stdio.h>
#include <string.h>

cresult_error cresult_error_create(char* message, char* file_name, size_t line_number) {
  cresult_error err;
  err.message = message;
  err.file_name = file_name;
  err.line_number = line_number;
  return err;
}

void cresult_error_print(cresult_error err) {
  printf("ERROR MESSAGE: %s\n", err.message);
  printf("FILE NAME: %s\n", err.file_name);
  printf("LINE NUMBER: %ld\n", err.line_number);
}

cresult_result* cresult_result_success(void* data, void (*destructor)(void*)) {
  cresult_result* buffer = malloc(sizeof(cresult_result));
  buffer->data = data;
  buffer->destructor = destructor;
  buffer->is_err = false;
  return buffer;
}

cresult_result* cresult_result_failure(cresult_error err) {
  cresult_result* buffer = malloc(sizeof(cresult_result));
  buffer->data = NULL;
  buffer->destructor = NULL;
  buffer->is_err = true;
  buffer->err = err;
  return buffer;
}

void cresult_result_destroy(cresult_result* result) {
  if (!result) return;
  if (!result->is_err && result->destructor) {
    result->destructor(result->data);
  }
  free(result);
}

cresult_result* cresult_result_force(cresult_result* result) {
  if (result->is_err) {
    cresult_error_print(result->err);
    free(result);
    exit(EXIT_FAILURE);
  }
  return result;
}
