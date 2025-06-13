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

cresult_result cresult_result_success(void* data) {
  cresult_result result;
  result.data = data;
  result.is_err = false;
  return result;
}

cresult_result cresult_result_failure(cresult_error err) {
  cresult_result result;
  result.data = NULL;
  result.is_err = true;
  result.err = err;
  return result;
}

cresult_result cresult_result_force(cresult_result result) {
  if (result.is_err) {
    cresult_error_print(result.err);
    exit(EXIT_FAILURE);
  }
  return result;
}

void* cresult_result_take(cresult_result* result) {
  void* data = result->data;
  result->data = NULL;
  return data;
} 
