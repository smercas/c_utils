#include <criterion/criterion.h>
#include <stdlib.h>

//  #include "../src/file_to_test"

int* x = NULL;

void suiteSetup(void) {
  int* x = (int*)malloc(sizeof(int) * 20);
}
void suiteTeardown(void) {
  free(x);
  x = NULL;
}

TestSuite(basictests, .init=suiteSetup, .fini=suiteTeardown);

Test(basictests, create) {
  cr_expect(x != NULL, "x should alocate 20 ints on the heap.");

}

Test(basictests, reallocate) {
  int* y = (int*)realloc(x, sizeof(int) * 40);
  cr_expect(y != NULL, "y should reallocare x to 40 ints on the heap.");
}