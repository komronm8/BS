CC=gcc
FLAGS=-Wall -D_XOPEN_SOURCE -D_POSIX_SOURCE 
FLAGS_EVIL=-Werror

all: sum

sum: main.c sumA.c sumB.c sumC.c
	$(CC) $(FLAGS) -o $@ $^

sum_evil: main.c sumA.c sumB.c sumC.c
	$(CC) $(FLAGS) $(FLAGS_EVIL) -o $@ $^

sumD: mainD.c sumA.c sumB.c sumC.c
	$(CC) $(FLAGS) -o $@ $^

clean: 
	rm -f sum

.PHONY: clean sum_evil

