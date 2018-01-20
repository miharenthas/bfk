#put some optional flags into this
CC_FLAGS := -ggdb
LD_FLAGS :=

.PHONY: all
all : bfk

.PHONY: clean
clean :
	rm -f *.o *.so bfk

brainlib.o :
	$(CC) brainlib.c $(CC_FLAGS) -fPIC -c

brainlib.so : brainlib.o
	$(CC) brainlib.o $(LD_FLAGS) -shared -o libbrainlib.so

bfk : brainlib.so
	$(CC) brainfuck.c -L. -lbrainlib $(CC_FLAGS) $(LD_FLAGS) -o bfk
