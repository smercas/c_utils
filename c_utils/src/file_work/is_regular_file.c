#include "is_regular_file.h"

#include <stdint.h>     //int32_t
#include <sys/stat.h>   //stat, S_ISREG

int32_t is_regular_file(char* path) {
  struct stat dstat;
  if (stat(path, &dstat) == -1) {
    return 0;
  }
  return S_ISREG(dstat.st_mode);
}
