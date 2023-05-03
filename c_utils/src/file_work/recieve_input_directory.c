#include "recieve_input_directory.h"

#include <stdint.h>               //int32_t
#include <unistd.h>               //access
#include <stdio.h>                //fprintf, stderr
#include <stdlib.h>               //realpath
#include "is_directory.h"         //is_directory

#define rid_ii_err { fprintf(stderr, "%s: Recieved optional argument number should be an integer with values between 1 and %d when it's %d.\n", __func__, c - 1, o); return -1; }
#define rid_r_err { fprintf(stderr, "%s: Error encountered while solving the path of '%s'.\n", __func__, v[o]); return -2; }
#define rid_id_err { fprintf(stderr, "%s: Error encountered while trying to find out if %s is a directory or not.\n", __func__, path); return -3; }
#define rid_ip_err {\
  fprintf(stderr, "%s: The specified input file (%s):\n", __func__, path);\
  if (!e) {\
    fprintf(stderr, "\t-does not exist\n");\
  }\
  if (!r) {\
    fprintf(stderr, "\t-does not have read permissions\n");\
  }\
  if (!d) {\
    fprintf(stderr, "\t-is not a directory\n");\
  }\
  return -4;\
}

//  -1 - invalid index
//  -2 - realpath
//  -3 - is_directory
//  -4 - invalid path
int32_t recieve_input_directory(int32_t c, char** v, char *path, int32_t o) {
  if (o <= 0 || o >= c) rid_ii_err
  if (realpath(v[o], path) == NULL) rid_r_err

  int32_t e = (access(path, F_OK) == 0);
  int32_t r = (access(path, R_OK) == 0);
  int32_t d = is_directory(path);
  if (d < 0) rid_id_err
  if (!e || !r || !d) rid_ip_err
  return 0;
}

#undef rid_ii_err
#undef rid_r_err
#undef rid_id_err
#undef rid_ip_err
