main: main.c
	cc main.c -o main -g -Wall -Wextra -lm

clean:
	rm -f main