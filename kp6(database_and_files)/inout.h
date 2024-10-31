#ifndef _INOUT_H
#define _INOUT_H

#include "passenger.h"

bool passenger_read_txt (Passenger pass, FILE* input);
void passenger_write_txt (Passenger pass, FILE* output);
void passenger_write_bin (Passenger pass, FILE* output);
bool passenger_read_bin (Passenger pass, FILE* input);
void passenger_print_from_bin (FILE* input);
void passenger_print_from_txt (FILE* input);

#endif