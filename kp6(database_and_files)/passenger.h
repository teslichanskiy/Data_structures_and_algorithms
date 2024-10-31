#ifndef _PASSENGER_H
#define _PASSENGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LEN_STR 30

typedef struct {
    int day, month, year, hour, minute;
} Datetime;

typedef struct {
	char surname[LEN_STR];
	char initials[LEN_STR];
	int luggage;
	int weight;
	char destination[LEN_STR];
	Datetime time;
	int transfer;
	int children;
} *Passenger;


#endif