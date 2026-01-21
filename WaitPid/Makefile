all:proc proc++
proc:proc.c
	gcc -o $@ $^ -std=c99
proc++:proc.cpp
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f proc proc++
