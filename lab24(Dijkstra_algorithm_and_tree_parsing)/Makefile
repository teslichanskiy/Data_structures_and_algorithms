CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c11 -Wall -Werror
FILE_OUT = lab24.out
SOURCES = 24main.c parstree.c

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