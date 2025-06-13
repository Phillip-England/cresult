#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cresult.h"


typedef struct {
  char* name;
} person;

void person_destroy(void* rperson) {
  person* p = (person*)rperson;
  if (!p) return;
  if (p->name) {
    free(p->name);
  }
  free(p);
}

cresult_result* person_create(char* name) {
  person* p = malloc(sizeof(person));
  if (strlen(name) == 0) {
    return CRESULT_FAILURE("no empty names allowed");
  }
  p->name = strdup(name);
  return cresult_result_success(p, person_destroy);
}

void cresult_test_failure() {
  cresult_result* rperson = cresult_result_force(person_create(""));
  person* p = (person*)rperson->data;
  printf("%s\n", p->name);
  cresult_result_destroy(rperson);
}

void cresult_test_success() {
  cresult_result* rperson = cresult_result_force(person_create("bob"));
  person* p = (person*)rperson->data;
  printf("%s\n", p->name);
  cresult_result_destroy(rperson);
}

int main(void) {
  cresult_test_success();
  cresult_test_failure();
  return EXIT_SUCCESS;
}
