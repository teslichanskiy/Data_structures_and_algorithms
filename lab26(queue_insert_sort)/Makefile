CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c99 -Wall -Werror
FILE_OUT = lab26.out
SOURCES = 26main.c 26source.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

clean:
	rm -f *.out

debug:
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(FILE_OUT)

comp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

run:
	./$(FILE_OUT)