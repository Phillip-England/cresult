#include "cresult.h"
#include <stdio.h>
#include <string.h>

cresult_error cresult_error_create(char *message, char *file_name, size_t line_number) {
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

cresult_result cresult_result_success(void *data) {
  cresult_result result;
  result.data = data;
  result.is_err = false;
  result.is_spent = false;
  return result;
}

cresult_result cresult_result_failure(cresult_error err) {
  cresult_result result;
  result.data = NULL;
  result.is_err = true;
  result.is_spent = true;
  result.err = err;
  return result;
}

cresult_result cresult_result_on_error_exit(cresult_result *result) {
  if (result->is_err) {
    cresult_error_print(result->err);
    exit(EXIT_FAILURE);
  }
  return *result;
}

cresult_result cresult_result_on_error_warn(cresult_result *result) {
  if (result->is_err) {
    cresult_error_print(result->err);
    result->is_spent = true;
  }
  return *result;
}

cresult_result cresult_result_on_error_fallback(cresult_result *result, cresult_result *fallback_result) {
  if (result->is_err) {
    if (fallback_result->is_err) {
      printf("CRESULT ERROR: provided a fallback result which itself contains an error\n");
      printf("here is the fallback result error:\n\n");
      cresult_error_print(fallback_result->err);
      exit(EXIT_FAILURE);
    }
    return *fallback_result;
  }
  return *result;
}

void *cresult_result_take(cresult_result *result) {
  if (result->is_spent) {
    cresult_error err = CRESULT_ERROR("CRESULT ERROR: attempted to take from a spent cresult_result");
    cresult_error_print(err);
    exit(EXIT_FAILURE);
  }
  result->is_spent = true;
  void *data = result->data;
  result->data = NULL;
  return data;
}
