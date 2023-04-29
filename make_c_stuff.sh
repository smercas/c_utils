#!/bin/bash

if [ $# -ge 1 ]
then
    path=$1
    shift
fi

while ! [ -e "$path" -a -d "$path" -a -r "$path" -a -w "$path" -a -x "$path" ]
# r - to read the contents of the recieved folder
# w - so files/folders can be added to/deleted from it
# x - again, visibility(can't read if you can't see, unless you know braille)
do
    read -p "Given directory ($path) either does not exist, is not a directory, its files can't be read/modified or it can't be accessed. Insert a new directory here: " path
done

if [ $# -ge 1 ]
then
    name=$1
    shift
fi

while ! [ -n "$name" ]
do
    read -p "Give me a normal project/library name please: " name
done

if [ $# -ge 1 ]
then
    type=$1
    shift
else
    type="p"
fi

while ! [ "$type" == "p" -o "$type" == "l" ]
do
    read -p "Specify a valid type(can either be a project or a library): " type
    if [ "$type" == "proj" -o "$type" == "project" ]
    then
        type="p"
    elif [ "$type" == "lib" -o "$type" == "library" ]
    then
        type="l"
    fi
done

container="$path/$name"

if ! [ -e "$container" -a -d "$container" ]
then
    mkdir "$container"
fi
if [ "$type" == "p" ]
then
    if ! [ -e "$container/bin" -a -d "$container/bin" ]
    then
        mkdir "$container/bin"
    fi
elif [ "$type" == "l" ]
then
    if ! [ -e "$container/lib" -a -d "$container/lib" ]
    then
        mkdir "$container/lib"
    fi
fi

if ! [ -e "$container/obj" -a -d "$container/obj" ]
then
    mkdir "$container/obj"
fi

if ! [ -e "$container/src" -a -d "$container/src" ]
then
    mkdir "$container/src"
fi

if ! [ -e "$container/test" -a -d "$container/test" ]
then
    mkdir "$container/test"
fi

if ! [ -e "$container/test/src" -a -d "$container/test/src" ]
then
    mkdir "$container/test/src"
fi

if ! [ -e "$container/test/bin" -a -d "$container/test/bin" ]
then
    mkdir "$container/test/bin"
fi

if [ "$type" == "p" ]
then
    if ! [ -e "$container/src/$name.c" -a -f "$container/src/$name.c" ]
    then
        touch "$container/src/$name.c"
    fi
elif [ "$type" == "l" ]
then
    if ! [ -e "$container/src/$name.h" -a -f "$container/src/$name.h" ]
    then
        touch "$container/src/$name.h"
    fi
fi

if [ -e "$container/Makefile" ] || [ -L "$container/Makefile" ]
then
    rm "$container/Makefile"
fi

if ! [ -e "$container/Makefile" -a -f "$container/Makefile" -a -L "$container/Makefile" ]
then
    cp ~/"Documents/Makefile_c_$type" "$container/Makefile"
fi

if [ "$type" == "l" ]
then
    sed -i "1s#.*#LIBNAME = $name#" "$container/Makefile"
    sed -i "2s#.*#LIBPATH = $(readlink -f $path)#" "$container/Makefile"
fi

if [ "$type" == "p" ]
then
    code "$container/src/$name.c"
elif [ "$type" == "l" ]
then
    code "$container/src/$name.h"
fi

# just remembered i don't need this since makefiles
# organise ur project folder like new_c_project and you're good to go
# run "make" while in the project folder to compile everything
# run "make clean" to clean ur project
# i'm not listing the rest of the commands, good luck
# run ./bin/main to execute that shii

# might come back to this someday and do some more stuff
