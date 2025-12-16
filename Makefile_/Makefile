BIN=code
CC=gcc
SRC=code.c
FLAGS=-o
RM=rm -f

$(BIN):$(SRC)
	$(CC) $(FLAGS) $(BIN) $(SRC)

.PHONY:
clean:
	$(RM) $(BIN)
	
.PHONY:test
test:
	@echo $(BIN)
	@echo $(CC)
	@echo $(SRC)
	@echo $(FLAGS)
	@echo $(RM)


#hello:hello.o
#	gcc hello.o -o hello
#hello.o:hello.s
#	gcc -c hello.s -o hello.o
#hello.s:hello.i
#	gcc -S hello.i -o hello.s
#hello.i:hello.c
#	gcc -E hello.c -o hello.i
#
#.PHONY:clean
#clean:
#	rm -rf *.i *.s *.o hello
