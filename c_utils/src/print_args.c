#include "print_args.h"

#include <stdio.h>    //printf
#include <stdint.h>   //int32_t

void print_args(int32_t c, char** v) {
  int32_t i = 0;
  while (i < c) {
    printf("argv[%d]: %s\n", i, v[i]);
    ++i;
  }
}