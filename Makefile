CC = gcc
FLAGS = -Wall -ggdb -std=c99

starsim: 
	$(CC) $(FLAGS) -o starsim starsim.c -lm

animate:
	$(CC) $(FLAGS) -DANIMATE starsim.c -o starsim -lm -lX11

run: animate
	./starsim 

star.o: starsim.h starsim.c
	$(CC) $(FLAGS) -DUNITTEST -c starsim.c -lm


test: testCases.c star.o
	$(CC) $(FLAGS) -o test testCases.c starsim.o -lm -lcunit 
	./test	

clean:
	rm starsim starsim.o testCases.o

.PHONY: clean
