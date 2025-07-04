#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cresult.h"

typedef struct {
  char *name;
} person;

void person_destroy(person *p) {
  if (!p) return;
  if (p->name) {
    free(p->name);
  }
  free(p);
}

cresult_result person_create(char *name) {
  person *p = malloc(sizeof(person));
  if (strlen(name) == 0) {
    return CRESULT_FAILURE("no empty names allowed");
  }
  p->name = strdup(name);
  return cresult_result_success(p);
}

void cresult_test_failure() {
  cresult_result result = person_create("");
  result = cresult_result_on_error_exit(&result);
  person *p = (person *)cresult_result_take(&result);
  printf("%s\n", p->name);
  person_destroy(p);
}

void cresult_test_success() {
  cresult_result result = person_create("bob");
  result = cresult_result_on_error_exit(&result);
  person *p = (person *)cresult_result_take(&result);
  printf("%s\n", p->name);
  person_destroy(p);
}

void cresult_test_fallback() {
cresult_result result = person_create("");
cresult_result fallback_result = person_create("anonymous");
result = cresult_result_on_error_fallback(&result, &fallback_result);
person *p = (person *)cresult_result_take(&result);
printf("%s\n", p->name);  // prints "anonymous"
person_destroy(p);
}

int main(void) {
  cresult_test_success();
  cresult_test_fallback();
  cresult_test_failure(); // must be last test ran
  return EXIT_SUCCESS;
}
