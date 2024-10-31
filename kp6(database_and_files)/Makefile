CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c99 -Wall -Werror
 

MAIN_SRC = kp6main.c inout.c search.c
MAIN_OUT = kp6.out

CONV_SRC = generate.c inout.c search.c
CONV_OUT = generate.out

all: 
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

generate: 
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

convert: 
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)

debug: 
	$(CC) -g $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)
	$(CC) -g $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

clean:
	rm -f *.out