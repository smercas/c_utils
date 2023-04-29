very unclear instrunctions on how to set it up:
  -download everything somewhere on ur computer(I'd suggest ~/Documents, this guide will go on assuming that you have followed this suggestion)
  -when creating c projects/libraries, use the "make_c_stuff.sh" script in the following way:
  
--------the-"make_c_stuff.sh"-bash-script--------
  
    bash ~/Documents/make_c_stuff.sh <location> <name> [p/l]
      <location> - where you want to place the directory of the project
                   this location must point towards a directory with read, write and execute(access) permissions
                   wtherwise you'll be asked to introduce a path to a directory that has those permissions until you do
      <name> - then name of your new project/library
               the name only has to not be ""
               you can pass the name to an already existing project and it'll most likely just replace its makefile
      [p/l] - optional argument, if not mentioned, the script will create a new project
              (so not including it is equivalent to it being p)

      "make_c_stuff.sh" is mainly used for creating the "skeleton" of a c project/library, it'll create:
        -a folder with the name of the project/library
        -a "src" folder
                       for the actual c code you'll write
          -a .c/.h file with the name of the project/library - in case a project is created, this .c file should normally be the core of the project
                                                               (it should contain the main function, "link" the whole project together; otherwise,
                                                               it should be the "linker" of the library (have includes to all the header files that
                                                               are present in the library so, if you wanted to, you could just include this header
                                                               file in other projects and have access to all of the functionality of the library)
        -a "obj" folder - for the intermediary object files created by the compilation of the source files
                          it'll have the same structure as the src folder(idk why I even bothered)

        -a "bin"/"lib" folder - stores the compilation result, either a libproject_name.so file or a main file
        -a "test" folder - used for unit testing, is split into:
          -a "src" folder - where the tests are written
          -a "bin" folder - same structure as src, contains the tests from "test/src" but compiled
        -a "Makefile" - there are some significant differences between a Makefile generated inside a project and one generated inside a library

      this structure is only a recommendation; as long as you modify the "make_c_stuff.sh"/"Makefile_c_p" file/"Makefile_c_l" file properly,
      you can organise your projects however you want.

      the script will end by opening the .c/.h file inside of the "src" folder in vscode; if you want to open this file with a different text editor,
      feel free to modify the "make_c_stuff.sh" script accordingly

--------contributions-and-structure--------

  for normal personal projects:
    I can't restrict you when it comes to what stuff you use this static library for, but I can give you a few suggestions:
      - first of all, use the .c file that has the name of the project as the "core" of the project, the "main" function should preferably be here and,
        if you want to/the functions take way too much space in the file, you can organize your project in multiple files in the following way:
        --let's say you want to create a new file for a 1000 line function called "int32_t abcdef (int32_t c, char** v)"
        --in that case, create a "abcdef.h" file that contains the function definition(meaning "int32_t abcdef (int32_t, char**)")
        --then, create a "abcdef.c" file that has the implementation of said function
        --don't forget to add an #include "abcdef.h" somewhere after the other includes but before any actual implementation
        --lastly, add that exact same line to the original .c file that had the "int32_t abcdef(int32_t c, char** v)" function
      - second of all, use stdint.h templates such as int32_t, uint64_t so you know the exact size of your variables

  for c_utils contributions
    Unless you follow these principles, I will most likely not accept your contribution so please follow them
      - ALWAYS use stdint.h templates so there's no confusion when typing long or stuff like that
      - explain why you included any libraries so "dependencies" are clear(if you want to include some parts of a function that would
        help you figure out what you need to include as far as standard libraries
      - separate any function you want to add into a .c file and a .h file(this way, if you want to include a smaller function compared to the
        whole "c_utils.h" library, you can do simply add its header file)
      - add #pragma once on the first line of any header file you want to add
      - have only one function per .c .h pair(same reason here)
      - include your header file into the bigger subheader file
      - don't do any complicated stuff unless you explain it or add an option that does stuff normally and use something like:

      #define EFFICIENT_IMPLEMENTATION 1
      #if EFFICIENT_IMPLEMENTATION == 1
        //  insert efficient implementation here
      #else
        //  insert normal implementation here
      #endif
      #undef EFFICIENT_IMPLEMENTATION

      I'll let you know if a function is too complicated to be dropped into the library so you can either modify it or wait for me to do it for you
      also if you could do some unit testing that would be immensely appreciated(place them where the normal function implementation is
      relative to "src" in "test/src")

      let's say that you want to add a function named "is_ok" into the file_work folder
      its implementation has to be split into two files:
        a header file named "file_work/is_ok.h":
          #pragma once
          #include <stdint.h>

          int32_t is_ok (int32_t, int32_t);

        a c file named "file_work/is_ok.c":
          #include <stdint.h>
          #include "is_ok.h"

          int32_t is_ok (int32_t a, int32_t b) {
            return a == b;
          }

      let's say, for the sake of the argument, that "file_work.h" contains:
        #pragma once
        #include "file_work/is_regular_file.h"

      the file should be modified in the following way

        #pragma once
        #include "file_work/is_regular_file.h"
        #include "file_work/is_ok.h"


--------the-"Makefile"-file--------

  if you already have a project set up, you can run the following commands(more might be added into the future):
  > make     - these last 2 commands compile all the .c files that've been modified since the last time the one of these commands has been executed;
  > make all   if any .h file with the same name as a .c file has been modified, the respective .c file is considered to have changed
  > make clean - removes any files and folders in "obj", "bin"/"lib" and "test/bin"
  > make runtest - compiles every test present in the "test/src" folder and then runs them
  > make release - cleans the project and compiles it with optimizations(not that useful ngl)
  there are some more commands but they're not worth explaining; you'll have to see them on your own

  there's a basic test in c_utils/test/src literally called "basic_c_test.c"; while it's far from being a good example,
  it should get you familiar enough with the criterion syntax if you ever want to write tests; tests are compiled individually
  and, after compiling them, "test/obj" will have the same folder structure as "test/src"; also, compiled tests can be executed
  separately(compared to "> make runtest" which runs all the tests after compiling them) symply by typing "> ./test/src/test_name"
  
  if you want to learn more about unit testing, I cordially invite you to read the criterion documentation
  this library will most likely not switch from criterion for unit testing

--------example-of-a-project--------
  > bash ~/Documents/make_c_stuff.sh ~/Desktop basic_c_project p
    # assuming that "~/Desktop/projects" is a valid path, the script will generate the following structure:
    # Desktop/
    #         projects/
    #                  basic_c_project/
    #                                  bin/
    #                                  obj/
    #                                  src/
    #                                      basic_c_project.c
    #                                  test/
    #                                       src/
    #                                       bin/
    #                  Makefile
  > mkdir ~/Desktop/projects/basic_c_project/src/abc
  > mkdir ~/Desktop/projects/basic_c_project/src/abc/def
  > mkdir ~/Desktop/projects/basic_c_project/src/abc/ghi
  > touch ~/Desktop/projects/basic_c_project/src/relevant.c
  > touch ~/Desktop/projects/basic_c_project/src/abc/c_file.c
  > touch ~/Desktop/projects/basic_c_project/src/abc/c_file.h
  > touch ~/Desktop/projects/basic_c_project/src/abc/def/stuff.h
  > touch ~/Desktop/projects/basic_c_project/src/abc/ghi/hmm.c
    # after running these commands, the structure of the project will become:
    # Desktop/
    #         projects/
    #                  basic_c_project/
    #                                  bin/
    #                                  obj/
    #                                  src/
    #                                      abc/
    #                                          def/
    #                                              stuff.h
    #                                          ghi/
    #                                              hmm.c
    #                                          c_file.c
    #                                          c_file.h
    #                                      basic_c_project.c
    #                                      relevant.c
    #                                  test/
    #                                       src/
    #                                       bin/
    #                  Makefile
    # now modifying the "basic_c_project.c" file:
    #include <stdio.h>
    #include "abc/c_file.h"

    int main() {
      printf("%d ^ %d = %d\n", 3, 8, power(3, 8));
    }

    # now modifying the "c_file.c" file:
    #include <stdint.h>   //int32_t
    #include "c_file.h"   //pow

    int32_t power (int32_t a, int32_t b) {
      int32_t p = 1;
      int32_t i = 0;
      while (i < b) {
        p = p * a;
        ++i;
      }
      return p;
    }

    # now modifying the "c_file.h" file:
    #pragma once
    #include <stdint.h>   //int32_t

    int32_t power (int32_t, int32_t);

    # now modifying the "hmm.c" file:
    #include <stdio.h>    //printf
    #include <stdint.h>   //int32_t

    void print_int(int32_t n) {
      printf("%d\n", n);
    }

    # now modifying he "relevant.c" file:
    #include <stdint.h>

    int32_t nothing() {
      return 0;
    }

    # if you were to run the "make [all]"(as in the "all" argument is optional/implied) command in the project directory,
    the structure of the project will become:
  > cd cd ~/Desktop/projects/basic_c_project
  > make
    # Desktop/
    #         projects/
    #                  basic_c_project/
    #                                  bin/
    #                                      main
    #                                  obj/
    #                                      abc/
    #                                          ghi/
    #                                              hmm.o
    #                                          c_file.o
    #                                      basic_c_project.o
    #                                      relevant.o
    #                                  src/
    #                                      abc/
    #                                          def/
    #                                              stuff.h
    #                                          ghi/
    #                                              hmm.c
    #                                          c_file.c
    #                                          c_file.h
    #                                      basic_c_project.c
    #                                      relevant.c
    #                                  test/
    #                                       src/
    #                                       bin/
    #                  Makefile
    # if you run the "./bin/main" command you'll get "3 + 8 = 6561
  > ./bin/main
  3 + 8 = 6561

  The created project links the "basic_c_project.c", "c_file.c" and "c_file.h" file how you'd think they'd link, while the
  "hmm.c" and "relevant.c" files remain isolated. "hmm.c" and "relevant.c" have some sort of implementation behind them
  and have to not show any errors in order for the project to compile, the stuff.h file does not affect the project in any way
  and can safely be removed.
