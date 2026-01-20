BIN=processbar
SRC=$(shell ls *.c)
OBJ=$(SRC:.c=.o)

$(BIN):$(OBJ)
	gcc -o $@ $^
%.o:%.c
	gcc -c $< -std=gnu99

.PHONY:
clean:
	rm -f $(OBJ) $(BIN)
