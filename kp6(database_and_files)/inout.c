#include "inout.h"
#include "passenger.h"

bool passenger_read_txt (Passenger pass, FILE* input) {
	if(fscanf(input, "%s\t%s\t%d\t%d\t%s\t%d/%d/%d,%d:%d\t%d\t%d", pass->surname, pass->initials,\
	&pass->luggage, &pass->weight, pass->destination, &pass->time.day,\
	&pass->time.month, &pass->time.year, &pass->time.hour, &pass->time.minute, &pass->transfer,&pass->children) != -1)
		return true;

	else return false;
}

void passenger_write_txt (Passenger pass, FILE* output) {
	fprintf(output, "%s\t%s\t%d\t%d\t%s\t%d/%d/%d,%d:%d\t%d\t%d", pass->surname, pass->initials,\
	pass->luggage, pass->weight, pass->destination, pass->time.day,\
	pass->time.month, pass->time.year, pass->time.hour, pass->time.minute, pass->transfer,pass->children);
}

void passenger_write_bin (Passenger pass, FILE* output) {
	fwrite(pass->surname, sizeof(pass->surname[0]), LEN_STR, output);
	fwrite(pass->initials, sizeof(pass->initials[0]), LEN_STR, output);
	fwrite(&pass->luggage, sizeof(pass->luggage), 1, output); 
	fwrite(&pass->weight, sizeof(pass->weight), 1, output); 
	fwrite(pass->destination, sizeof(pass->destination[0]), LEN_STR, output);
	fwrite(&pass->time.day, sizeof(pass->time.day), 1, output); 
	fwrite(&pass->time.month, sizeof(pass->time.month), 1, output); 
	fwrite(&pass->time.year, sizeof(pass->time.year), 1, output); 
	fwrite(&pass->time.hour, sizeof(pass->time.hour), 1, output); 
	fwrite(&pass->time.minute, sizeof(pass->time.minute), 1, output); 
	fwrite(&pass->transfer, sizeof(pass->transfer), 1, output); 
	fwrite(&pass->children, sizeof(pass->children), 1, output); 
}

bool passenger_read_bin (Passenger pass, FILE* input) {
	if(fread(pass->surname, sizeof(pass->surname[0]), LEN_STR, input) &&\
	fread(pass->initials, sizeof(pass->initials[0]), LEN_STR, input) &&\
	fread(&pass->luggage, sizeof(pass->luggage), 1, input) &&\
	fread(&pass->weight, sizeof(pass->weight), 1, input) &&\
	fread(pass->destination, sizeof(pass->destination[0]), LEN_STR, input) &&\
	fread(&pass->time.day, sizeof(pass->time.day), 1, input) &&\
	fread(&pass->time.month, sizeof(pass->time.month), 1, input) &&\
	fread(&pass->time.year, sizeof(pass->time.year), 1, input) &&\
	fread(&pass->time.hour, sizeof(pass->time.hour), 1, input) &&\
	fread(&pass->time.minute, sizeof(pass->time.minute), 1, input) &&\
	fread(&pass->transfer, sizeof(pass->transfer), 1, input) &&\
	fread(&pass->children, sizeof(pass->children), 1, input))
		return true;

	else return false;
}

void passenger_print_from_bin (FILE* input) {
	printf("____________________________________________________________________________________________\n");
    printf("|      Surname      |Luggage| Weight |       To       |     Date/time     |  Trans  |  Ch  |\n");
    printf("____________________________________________________________________________________________\n");
    Passenger pass = (Passenger)calloc(1, sizeof(*pass));
    while (passenger_read_bin(pass, input)) {
    	fprintf(stdout, "%s %s\t\t%d\t%d\t%s\t\t%d/%d/%d,%d:%d\t\t%d\t%d\n", pass->surname, pass->initials,\
	pass->luggage, pass->weight, pass->destination, pass->time.day,\
	pass->time.month, pass->time.year, pass->time.hour, pass->time.minute, pass->transfer,pass->children);
    }

    free(pass);
	printf("___________________________________________________________________________________________\n");
}

void passenger_print_from_txt (FILE* input) {
	printf("____________________________________________________________________________________________\n");
    printf("|      Surname      |Luggage| Weight |       To       |     Date/time     |  Trans  |  Ch  |\n");
    printf("____________________________________________________________________________________________\n");
    Passenger pass = (Passenger)calloc(1, sizeof(*pass));
    while (passenger_read_txt(pass, input)) {
    	fprintf(stdout, "%s %s\t\t%d\t%d\t%s\t\t%d/%d/%d,%d:%d\t\t%d\t%d\n", pass->surname, pass->initials,\
	pass->luggage, pass->weight, pass->destination, pass->time.day,\
	pass->time.month, pass->time.year, pass->time.hour, pass->time.minute, pass->transfer,pass->children);
    }

    free(pass);
	printf("___________________________________________________________________________________________\n");
}