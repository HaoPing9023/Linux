BIN=code.exe
CC=gcc
SRC=code.c
OBJ=code.o
LFLAGS=-o
FLAGS=-c
RM=rm -f

$(BIN):$(OBJ)
	@$(CC) $(LFLAGS) $@ $^
	@echo "linking ... $^ to $@"

%.o:%.c
	@$(CC) $(FLAGS) $<
	@echo "compling ... $< to $@"

.PHONY:clean
clean:
	$(RM) $(OBJ) $(BIN)






#$(BIN):$(SRC)
#	@$(CC) $(FLAGS) $@ $^
#	@echo "linking ... $^ to $@"
#
#.PHONY:
#clean:
#	@$(RM) $(BIN)
#	@echo "remove ... $(BIN)"
#	
#.PHONY:test
#test:
#	@echo $(BIN)
#	@echo $(CC)
#	@echo $(SRC)
#	@echo $(FLAGS)
#	@echo $(RM)
#

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
