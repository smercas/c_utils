#include <stdint.h>         //int32_t, uint64_t
#include <regex.h>          //regex_t, regcomp, REG_EXTENDED
#include <stdio.h>          //stderr, printf, scanf
#include <string.h>         //strcpy, strcmp, 
#include <stdlib.h>         //strtoull

#define rn_rc_err { fprintf(stderr, "%s: Error encountered while compiling a regular expression. (%s)\n", __func__, pattern); return -1; }
#define rn_re_err { fprintf(stderr, "%s: Error encountered while matching a char array to a reguar expression.\n", __func__); return -2; }

//  -1 - rn_rc_err
//  -2 - rn_re_err
int32_t recieve_gt0_int_number(uint64_t *n, int32_t c, char** v, int32_t o) {
  while (o <= 0) {
    printf("Recieved optional argument number (%d) should be at least 1. Insert another one here: ", o);
    scanf("%d", &o);
  }
  regex_t reg;
  int32_t ret;
  char* pattern = "^[1-9][0-9]*$";
  if (regcomp(&reg, pattern, REG_EXTENDED) != 0) rn_rc_err
  char number[128];

  if (c > o) {
    strcpy(number, v[o]);
  }
  else {
    strcpy(number, "0");
  }
  while (strcmp(number, "") == 0 || (ret = regexec(&reg, number, 0, NULL, 0)) == REG_NOMATCH) {
    printf("Insert a new number here: ");
    scanf("%s", number);
  }
  regfree(&reg);
  if (ret != 0) rn_re_err
  *n = strtoull(number, NULL, 10);
  return 0;
}
#undef rn_rc_err
#undef rn_re_err
