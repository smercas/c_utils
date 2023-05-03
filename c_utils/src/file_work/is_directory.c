#include "is_directory.h"

#include <stdio.h>      //fprintf, stderr
#include <stdint.h>     //int32_t
#include <sys/stat.h>   //stat, S_ISREG

#define id_s_err { fprintf(stderr, "%s: Error encountered while recieving information about a directory (%s).\n", __func__, path); return -1; }

//  -1 - stat
int32_t is_directory(char* path) {
  struct stat dstat;
  if (stat(path, &dstat) == -1) id_s_err
  return S_ISDIR(dstat.st_mode);
}

#undef id_s_err