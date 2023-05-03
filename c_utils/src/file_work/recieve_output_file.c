#include "recieve_output_file.h"

#include <stdint.h>               //int32_t
#include <linux/limits.h>         //PATH_MAX
#include <unistd.h>               //access
#include <string.h>               //strcpy
#include <stdio.h>                //fprintf, stderr
#include <stdlib.h>               //realpath
#include <libgen.h>               //dirname
#include "is_regular_file.h"      //is_regular_file

#define rof_ii_err { fprintf(stderr, "%s: Recieved optional argument number should be an integer with values between 1 and %d when it's %d.\n", __func__, c - 1, o); return -1; }
#define rof_r_err { fprintf(stderr, "%s: Error encountered while solving the path of '%s'.\n", __func__, v[o]); return -2; }
#define rof_irf_err { fprintf(stderr, "%s: Error encountered while trying to find out if %s is a regular file or not.\n", __func__, path); return -3; }
#define rof_ip_err {\
  fprintf(stderr, "%s: The specified output file (%s):\n", __func__, path);\
  if (!e) {\
    fprintf(stderr, "\t-does not exist\n");\
  }\
  if (!w) {\
    fprintf(stderr, "\t-does not have write permissions\n");\
  }\
  if (!f) {\
    fprintf(stderr, "\t-is not a regular file\n");\
  }\
  if (!d) {\
    fprintf(stderr, "\t-can't be accessed, along with all the other files in the '%s' directory\n", dir);\
  }\
  return -4;\
}

//  -1 - invalid index
//  -2 - realpath
//  -3 - is_regular_file
//  -4 - invalid path
int32_t recieve_output_file(int32_t c, char** v, char *path, int32_t o) {
  if (o <= 0 || o >= c) rof_ii_err
  if (realpath(v[o], path) == NULL) rof_r_err
  char dir[PATH_MAX];
  strcpy(dir, path);
  dirname(dir);

  int32_t e = (access(path, F_OK) == 0);
  int32_t w = (access(path, W_OK) == 0);
  int32_t f = is_regular_file(path);
  int32_t d = (access(dir, W_OK) == 0);

/*  cases
cases where a new file should be created:
  e w f d
  0 0 0 1

cases where a file should be opened:
  e w f d
  1 1 1 1

bad cases:
  e w f d
  0 0 0 0
  1 0 0 0
  1 0 0 1
  1 0 1 0
  1 0 1 1
  1 1 0 0
  1 1 0 1
  1 1 1 0

the other cases are impossible
*/

  if (f < 0) rof_irf_err
  if (!(e && w && f && d) && !(!e && !w && !f && d)) rof_ip_err
  else if (!e && !w && !f && d) {
    return 0;   //file should be created
  }
  else {
    return 1;   //file should be opened
  }
}

#undef rof_ii_err
#undef rof_r_err
#undef rof_irf_err
#undef rof_ip_err
