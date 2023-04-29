#include <string.h>
#include "mycode.h"

char* reverse(char* string) {
  size_t length = strlen(string);
  char temp;
  for (size_t i = 0; i < length / 2; ++i) {
    temp = string[i];
    string[i] = string[length - 1 - i];
    string[length - 1 - i] = temp;
  }
  return string;
}
