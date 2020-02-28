compile: main.c lab2.c builtIn.c lab2.h
	gcc -o main main.c

run: main
	./main