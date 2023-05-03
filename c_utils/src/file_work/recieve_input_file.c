#include "recieve_input_file.h"

#include <stdint.h>               //int32_t
#include <unistd.h>               //access
#include <stdio.h>                //fprintf, stderr
#include <stdlib.h>               //realpath
#include "is_regular_file.h"      //is_regular_file

#define rif_ii_err { fprintf(stderr, "%s: Recieved optional argument number should be an integer with values between 1 and %d when it's %d.\n", __func__, c - 1, o); return -1; }
#define rif_r_err { fprintf(stderr, "%s: Error encountered while solving the path of '%s'.\n", __func__, v[o]); return -2; }
#define rif_irf_err { fprintf(stderr, "%s: Error encountered while trying to find out if %s is a regular file or not.\n", __func__, path); return -3; }
#define rif_ip_err {\
  fprintf(stderr, "%s: The specified input file (%s):\n", __func__, path);\
  if (!e) {\
    fprintf(stderr, "\t-does not exist\n");\
  }\
  if (!r) {\
    fprintf(stderr, "\t-does not have read permissions\n");\
  }\
  if (!f) {\
    fprintf(stderr, "\t-is not a regular file\n");\
  }\
  return -4;\
}

//  -1 - invalid index
//  -2 - realpath
//  -3 - is_regular_file
//  -4 - invalid path
int32_t recieve_input_file(int32_t c, char** v, char *path, int32_t o) {
  if (o <= 0 || o >= c) rif_ii_err
  if (realpath(v[o], path) == NULL) rif_r_err

  int32_t e = (access(path, F_OK) == 0);
  int32_t r = (access(path, R_OK) == 0);
  int32_t f = is_regular_file(path);
  if (f < 0) rif_irf_err
  if (!e || !r || !f) rif_ip_err
  return 0;
}

#undef rif_ii_err
#undef rif_r_err
#undef rif_irf_err
#undef rif_ip_err
