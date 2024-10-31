#ifndef _SEARCH_H
#define _SEARCH_H

#include "inout.h"
#include "passenger.h"

typedef enum {
    PRINTBIN = 1,
    PRINTTXT = 2,
    ADDTOTXT = 3,
    ADDTOBIN = 4,
    DELETEFROMTXT = 5,
    DELETEFROMBIN = 6, 
    SEARCH = 7
} var_flags;

Passenger passenger_get_from_user (Passenger pass);
void passenger_add_to_txt (FILE* filetxt);
void passenger_add_to_bin (FILE* filebin);
void passenger_delete_from_txt (const char* filename, const char* passname, FILE* filetxt);
void passenger_delete_from_bin (const char* filename, const char* passname, FILE* filebin); 
void pass_free(Passenger* pass, int size);
int search_max (Passenger* pass, int size);

#endif