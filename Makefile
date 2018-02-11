#put some optional flags into this
CC_FLAGS := -ggdb
LD_FLAGS :=
OS_TYPE = $(shell expr `uname`)

ifeq "$(OS_TYPE)" "Linux" 
	SHARED_FLAG := -shared
endif
ifeq "$(OS_TYPE)" "Darwin"
	SHARED_FLAG := -dynamiclib
endif

.PHONY: all
all : bfk

.PHONY: clean
clean :
	rm -f *.o *.so bfk

brainlib.o :
	$(CC) brainlib.c $(CC_FLAGS) -fPIC -c

brainlib.so : brainlib.o
	$(CC) brainlib.o $(LD_FLAGS) $(SHARED_FLAG) -o libbrainlib.so

bfk : brainlib.so
	$(CC) brainfuck.c -L. -lbrainlib $(CC_FLAGS) $(LD_FLAGS) -o bfk
