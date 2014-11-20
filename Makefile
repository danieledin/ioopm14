CC = gcc
FLAGS = -Wall -ggdb -std=c99
#
#starsim: 
#	$(CC) $(FLAGS) -o starsim starsim.c -lm
#
#animate:
#	gcc -std=c99 -DANIMATE starsim.c -o starsim -lm -lX11

#run: animate
#	./starsim 

star.o: starsim.h starsim.c
	$(CC) $(FLAGS) -c starsim.c -lm


test: testCases.c star.o
	$(CC) $(FLAGS) -DUNITTEST -o test testCases.c starsim.o -lm -lcunit 
	./test	

clean:
	rm starsim

.PHONY: clean
