VPATH := ./inc ./src ./obj ./lib
vpath %.h ./inc
vpath %.c ./src
vpath %.o ./obj
vpath %.so ./lib

CC = gcc
INCDIR = -I.
SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
EXEDIR = ./bin
TSTDIR = ./tst
LOGDIR = ./log
COVDIR = ./cov
BLDDIR = ./
OPTIMIZATION = -O0
OBJECT_NAMES = base64 adler32
OBJECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/$(f_name).o)
TSTECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/test_$(f_name).o)
EXECUTABLE := $(EXEDIR)/codec
TSTCUTABLE := $(EXEDIR)/tst
MEMCUTABLE := $(EXEDIR)/mem
BDGCUTABLE := $(EXEDIR)/bdg
LIBRARY := $(LIBDIR)/libcodec.so
CFLAGS = -Wall -Wextra -g $(INCDIR) $(OPTIMIZATION)
CFLAGS_EXTRA = -fPIC -shared -finput-charset=UTF-8# [1] position-indepedent-code, [2] shared object, [3] input character encoding UTF-8
CFLAGS_COVERAGE = --coverage
LIB_DSA := -L$(shell pwd)/DSA/lib/ -ldsa
LIB_ENV_PARAM := LD_LIBRARY_PATH=./DSA/lib/:$$LD_LIBRARY_PATH

all: $(EXECUTABLE) $(TSTCUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "-> Linking all object files and generating executable binary file ..."
	@$(CC) $(CFLAGS) $(LIB_DSA) -o $@ $^ ./main.c
	@chmod +x $(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(LIB_DSA) -o $@ -c $^

test: $(TSTCUTABLE)

$(TSTCUTABLE): $(TSTECTS)
	@echo "-> Linking all object files and generating test binary file ..."
	@$(CC) $(CFLAGS) $(CFLAGS_COVERAGE) $(LIB_DSA) -o $@ ./test.c $(OBJECTS) $^
	@chmod +x $(TSTCUTABLE)

$(OBJDIR)/test_%.o: $(TSTDIR)/%.c
	@echo " + Compiling test_"$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(CFLAGS_COVERAGE) -o $@ -c $^
#	@echo "... Done!"
#	@echo

.PHONY: clean again check

clean:
	@echo "-> Removing generated files ..."
	@-rm -f $(OBJECTS) $(EXECUTABLE) $(TSTCUTABLE) $(LIBRARY)
	@-rm -f ./obj/* ./lib/* ./bin/* ./log/* ./cov/* ./aft/*
	@echo "... Done"
#	@echo

again:
	@make clean && make all

check:
	@tabs 4
	@$(LIB_ENV_PARAM) $(TSTCUTABLE) | tee $(LOGDIR)/test.log
	@$(LIB_ENV_PARAM) $(EXECUTABLE) -t "base64" -e "Hello"
	@$(LIB_ENV_PARAM) $(EXECUTABLE) -t "base64" -d "SGVsbG8="
	@$(LIB_ENV_PARAM) $(EXECUTABLE) -t "adler32" -e "Hello, World!"

