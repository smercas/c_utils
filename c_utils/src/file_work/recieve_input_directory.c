#include "recieve_input_file.h"

#include <stdint.h>               //int32_t
#include <unistd.h>               //access
#include <string.h>               //strcpy, strcmp
#include <stdio.h>                //scanf, printf
#include "is_directory.h"         //is_directory

void recieve_input_directory(int32_t c, char** v, char *path) {
  if (c >= 2) {
    strcpy(path, v[1]);
  }
  int32_t r = is_directory(path);

  while (strcmp(path, "") == 0 || access(path, R_OK) == -1 || !r) {
    printf("Insert a directory name here: ");
    scanf("%s", path);
    r = is_directory(path);
  }
}
