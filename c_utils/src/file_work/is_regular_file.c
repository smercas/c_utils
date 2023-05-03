#include "is_regular_file.h"

#include <stdio.h>      //fprintf, stderr
#include <stdint.h>     //int32_t
#include <sys/stat.h>   //stat, S_ISREG

#define irf_s_err { fprintf(stderr, "%s: Error encountered while recieving information about a directory (%s).\n", __func__, path); return -1; }

//  -1 - stat
int32_t is_regular_file(char* path) {
  struct stat dstat;
  if (stat(path, &dstat) == -1) irf_s_err
  return S_ISREG(dstat.st_mode);
}

#undef irf_s_err