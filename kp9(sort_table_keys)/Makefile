CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c99 -Wall -Werror
FILE_OUT = kp9.out
SOURCES = kp9main.c sort.c

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