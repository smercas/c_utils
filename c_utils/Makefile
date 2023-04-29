LIBNAME = c_utils
LIBPATH = /home/stefan/Documents
CC = gcc
WARNINGS = -Wall -Wextra
OPTIMIZATIONS = -O0
DEBUGINFO = -g3
CFLAGS = $(WARNINGS) $(DEBUGINFO) $(OPTIMIZATIONS)
USEDLIBRARIES = -lc

SRC = src
SOURCES = $(shell find $(SRC) -name "*.c")

OBJ = obj
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

LIB = lib
MAIN = $(LIB)/lib$(LIBNAME).so

TESTFRAMEWORK = -lcriterion
TESTUSEDLIBRARIES = $(USEDLIBRARIES) $(TESTFRAMEWORK) -l$(LIBNAME)
IFLAGS = -I$(LIBPATH)/$(LIBNAME)/src
LFLAGS = -L$(LIBPATH)/$(LIBNAME)/lib
WLFLAGS = -Wl,-rpath=$(LIBPATH)/$(LIBNAME)/lib

TEST = test

TESTSRC = $(TEST)/src
TESTSOURCES = $(shell find $(TESTSRC) -name "*.c")

TESTBIN = $(TEST)/bin
TESTBINARIES = $(patsubst $(TESTSRC)/%.c, $(TESTBIN)/%, $(TESTSOURCES))

all: $(MAIN)

release: CFLAGS = -Wall -O3 -DNDEBUG
release: clean
release: $(MAIN)

$(MAIN): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) -shared $(OBJECTS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/$(LIBNAME).h
	mkdir -p $(dir $@) ; $(CC) $(CFLAGS) -fpic -c $< -o $@ $(USEDLIBRARIES)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	mkdir -p $(dir $@) ; $(CC) $(CFLAGS) -fpic -c $< -o $@ $(USEDLIBRARIES)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/$(LIBNAME).h
	mkdir -p $(dir $@) ; $(CC) $(CFLAGS) -fpic -c $< -o $@ $(USEDLIBRARIES)

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@) ; $(CC)  $(CFLAGS)-fpic -c $< -o $@ $(USEDLIBRARIES)

$(OBJ):
	mkdir $@

$(LIB):
	mkdir $@

$(TESTBIN)/%: $(TESTSRC)/%.c $(MAIN)
	mkdir -p $(dir $@) ; $(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(WLFLAGS) $^ -o $@ $(TESTUSEDLIBRARIES)

$(TEST):
	mkdir $@

$(TESTBIN): $(TEST)
	mkdir $@

runtest: $(LIB) $(TESTBIN) $(TESTBINARIES)
	for test in $(TESTBINARIES) ; do ./$$test ; done

clean:
	$(RM) -r $(LIB)/* $(OBJ)/* $(TESTBIN)/*
