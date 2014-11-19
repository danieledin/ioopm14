CC = gcc
FLAGS = -Wall -ggdb -std=c99

starsim: 
	$(CC) $(FLAGS) -o starsim starsim.c -lm

animate:
	gcc -std=c99 -DANIMATE starsim.c -o starsim  -lm -lX11

run: animate
	./starsim 

clean:
	rm starsim

.PHONY: clean
