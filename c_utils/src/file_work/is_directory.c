#include "is_directory.h"

#include <stdint.h>     //int32_t
#include <sys/stat.h>   //stat, S_ISREG

int32_t is_directory(char* path) {
  struct stat dstat;
  if (stat(path, &dstat) == -1) {
    return 0;
  }
  return S_ISDIR(dstat.st_mode);
}
