CC = gcc
FLAGS = -Wall -ggdb -std=c99

starsim.o: starsim.c starsim.h
	$(CC) $(FLAGS) -c starsim.c -lm

starsim: starsim.o
	$(CC) $(FLAGS) -o starsim starsim.o -lm

test: starsim
	./starsim

clean:
	rm -f starsim starsim.o gmon.out


.PHONY: test

animate:
	gcc -std=c99 -DANIMATE starsim.c -o starsim  -lm -lX11


gprof: 
	$(CC) $(FLAGS) -DANIMATE -pg -o starsim starsim.c -lm -lX11 
	./starsim
	gprof -b starsim gmon.out
run:	
	./starsim 
