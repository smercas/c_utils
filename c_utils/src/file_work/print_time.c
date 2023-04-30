#include <stdint.h>   //uint64_t
#include <time.h>     //time_t
#include <stdio.h>

void print_time(time_t time, char* buffer, uint64_t bufsize, const char* info) {
  strftime(buffer, bufsize, "%Y-%m-%d %H:%M:%S", localtime(&time));
  printf("Last %s: %s\n", info, buffer);
}
