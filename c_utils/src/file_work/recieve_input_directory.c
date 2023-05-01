#include "recieve_input_file.h"

#include <stdint.h>               //int32_t
#include <unistd.h>               //access
#include <string.h>               //strcpy, strcmp
#include <stdio.h>                //scanf, printf
#include "is_directory.h"         //is_directory

void recieve_input_directory(int32_t c, char** v, char *path, int32_t o) {
  while (o <= 0) {
    printf("Recieved optional argument number (%d) should be at least 1. Insert another one here: ", o);
    scanf("%d", &o);
  }
  if (c > o) {
    strcpy(path, v[o]);
  }
  else {
    strcpy(path, "");
  }

  while (strcmp(path, "") == 0 || access(path, R_OK) == -1 || !is_directory(path)) {
    printf("Insert a directory name here: ");
    scanf("%s", path);
  }
}
