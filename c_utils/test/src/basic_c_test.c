#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "dumb_stuff/mycode.h"

char* x = NULL;

void suiteSetup(void) {
  x = (char*)malloc(sizeof(char) * (4 + 1));
}
void suiteTeardown(void) {
  free(x);
  x = NULL;
}

TestSuite(basictests, .init=suiteSetup, .fini=suiteTeardown);

Test(basictests, create) {
  cr_expect(x != NULL, "x should alocate 5 chars on the heap.");            //stupid idea ik
  strcpy(x, "KCUF");
  cr_expect(strcmp(reverse(x), "FUCK") == 0, "the reverse of KCUF should be FUCK.");
  cr_expect(strcmp(reverse(x), "KCUF") == 0, "the reverse of FUCK should be KCUF.");
}

Test(basictests, reallocate) {
  char* y = (char*)realloc(x, sizeof(char) * 10);
  cr_expect(y != NULL, "y should reallocare x to 10 chars on the heap.");   //still stupid
  strcpy(y, "D00FDAAB");
  cr_expect(strcmp(reverse(x), "BAADF00D") == 0, "the reverse of D00FDAAB should be BAADF00D.");
  cr_expect(strcmp(reverse(x), "D00FDAAB") == 0, "the reverse of BAADF00D should be D00FDAAB.");
}