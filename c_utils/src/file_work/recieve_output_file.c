#include "recieve_output_file.h"

#include <stdint.h>               //int32_t
#include <linux/limits.h>         //PATH_MAX
#include <string.h>               //strcmp, strcpy
#include <unistd.h>               //access
#include <stdio.h>                //printf, scanf
#include <libgen.h>               //dirname
#include "is_regular_file.h"      //isRegularFile


int32_t recieve_output_file(int32_t c, char** v, char *path) {
  char dir[PATH_MAX];
  if (c >= 3) {
    strcpy(path, v[2]);
  }
/* i'm ashamed of myself
  //n : _ e w r d
  //1 : 0 0 0 0 0 : get another       +----------+-------+-------+-------+-------+
  //2 : 0 0 0 0 1 : impossible        |          |  _  e |  _ !e | !_ !e | !_  e |
  //3 : 0 0 0 1 0 : impossible        +----------+-------+-------+-------+-------+
  //4 : 0 0 0 1 1 : impossible        |  w  r  d |   o   |       |       |       |
  //5 : 0 0 1 0 0 : impossible        +----------+-------+-------+-------+-------+
  //6 : 0 0 1 0 1 : impossible        |  w  r !d |   g   |       |       |       |
  //7 : 0 0 1 1 0 : impossible        +----------+-------+-------+-------+-------+
  //8 : 0 0 1 1 1 : impossible        |  w !r !d |   g   |       |       |       |
  //9 : 0 1 0 0 0 : impossible        +----------+-------+-------+-------+-------+
  //10: 0 1 0 0 1 : impossible        |  w !r  d |   g   |       |       |       |
  //11: 0 1 0 1 0 : impossible        +----------+-------+-------+-------+-------+
  //12: 0 1 0 1 1 : impossible        | !w !r  d |   g   |   c   |       |       |
  //13: 0 1 1 0 0 : impossible        +----------+-------+-------+-------+-------+
  //14: 0 1 1 0 1 : impossible        | !w !r !d |   g   |   g   |   g   |       |
  //15: 0 1 1 1 0 : impossible        +----------+-------+-------+-------+-------+
  //16: 0 1 1 1 1 : impossible        | !w  r !d |   g   |       |       |       |
  //17: 1 0 0 0 0 : get another       +----------+-------+-------+-------+-------+
  //18: 1 0 0 0 1 : create one        | !w  r  d |   g   |       |       |       |
  //19: 1 0 0 1 0 : impossible        +----------+-------+-------+-------+-------+
  //20: 1 0 0 1 1 : impossible
  //21: 1 0 1 0 0 : impossible
  //22: 1 0 1 0 1 : impossible
  //23: 1 0 1 1 0 : impossible
  //24: 1 0 1 1 1 : impossible
  //25: 1 1 0 0 0 : get another
  //26: 1 1 0 0 1 : get another
  //27: 1 1 0 1 0 : get another
  //28: 1 1 0 1 1 : get another
  //29: 1 1 1 0 0 : get another
  //30: 1 1 1 0 1 : get another
  //31: 1 1 1 1 0 : get another
  //32: 1 1 1 1 1 : open
*/

  int32_t _ = (strcmp(path, "") != 0);            // path is valid
  int32_t e = (access(path, F_OK) == 0);          // file exists
  int32_t w = (access(path, W_OK) == 0);          // can write into file
  int32_t r = is_regular_file(path);              // is a regular file
  strcpy(dir, path);
  int32_t d = (access(dirname(dir), W_OK) == 0); // the directory where the file is has writing privileges

  while ((!e && !w && !r && !d) || (_ && e && !(w && r && d))) {
    printf("Insert a file name here: ");
    scanf("%s", path);

    _ = (strcmp(path, "") != 0);
    e = (access(path, F_OK) == 0);
    w = (access(path, W_OK) == 0);
    r = is_regular_file(path);
    strcpy(dir, path);
    d = (access(dirname(dir), W_OK) == 0);
  }
  if (_ && !e && !w && !r && d) {
    return 0; // file should be created
  }
  else if (_ && e && w && r && d) {
    return 1; // file should be opened
  }
  else {
    return -1;
  }
}