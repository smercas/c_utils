#include <stdint.h>         //int32_t, uint64_t
#include <regex.h>          //regex_t, regcomp, REG_EXTENDED
#include <stdio.h>          //stderr, printf, scanf
#include <string.h>         //strcpy, strcmp, 
#include <stdlib.h>         //strtoull

#define rn_ii_err { fprintf(stderr, "%s: Recieved optional argument number should be an integer with values between 1 and %d when it's %d.\n", __func__, c - 1, o); return -1; }
#define rn_rc_err { fprintf(stderr, "%s: Error encountered while compiling a regular expression. (%s)\n", __func__, pattern); return -2; }
#define rn_re_err { fprintf(stderr, "%s: Error encountered while matching a char array to a reguar expression.\n", __func__); return -3; }
#define rn_nan_err { fprintf(stderr, "%s: %s is not a integer.\n", __func__, v[o]); return -4; }

//  -1 - invalid index
//  -2 - rn_rc_err
//  -3 - rn_re_err
//  -4 - not a number
int32_t recieve_gt0_int_number(int32_t c, char** v, uint64_t *n, int32_t o) {
  if (o <= 0 || o >= c) rn_ii_err
  regex_t reg;
  int32_t ret;
  char* pattern = "^[1-9][0-9]*$";
  if (regcomp(&reg, pattern, REG_EXTENDED) != 0) rn_rc_err

  if ((ret = regexec(&reg, v[o], 0, NULL, 0)) == _REG_NOMATCH) rn_nan_err
  regfree(&reg);
  if (ret != 0) rn_re_err
  *n = strtoull(v[o], NULL, 10);
  return 0;
}

#undef rn_ii_err
#undef rn_rc_err
#undef rn_re_err
#undef rn_nan_err
