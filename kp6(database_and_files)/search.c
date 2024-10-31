#include "inout.h"
#include "passenger.h"
#include "search.h"

Passenger passenger_get_from_user (Passenger pass) {
	printf ("Surname:\t");
	fscanf(stdin, "%s", pass->surname); 
	printf ("Initials:\t");
	fscanf(stdin, "%s", pass->initials);
	printf ("Amount of luggage:\t");
	fscanf(stdin, "%d", &pass->luggage);
	printf ("Weight:\t");
	fscanf(stdin, "%d", &pass->weight); 
	printf ("Destination:\t");
	fscanf(stdin, "%s",pass->destination);
	printf ("Date & time (day/month/year,hour:minutes):\t");
	fscanf(stdin, "%d/%d/%d,%d:%d",&pass->time.day,&pass->time.month, &pass->time.year, &pass->time.hour, &pass->time.minute); 
	printf ("Amount of transfers:\t");
	fscanf(stdin, "%d", &pass->transfer);
	printf ("Amount of children:\t");
	fscanf(stdin, "%d", &pass->children);

	return pass;
}

void passenger_add_to_txt (FILE* filetxt) {
	Passenger pass = (Passenger)malloc(sizeof(*pass));
	pass = passenger_get_from_user(pass);
	if (ftell(filetxt) != 0) {
		fputc ('\n', filetxt);
	}

	passenger_write_txt(pass, filetxt);
    free(pass); 
    rewind(filetxt);
}

void passenger_add_to_bin (FILE* filebin) {
	Passenger pass = (Passenger)malloc(sizeof(*pass));
	pass = passenger_get_from_user(pass);
	passenger_write_bin(pass, filebin);
    free(pass);
    rewind(filebin);
}

void passenger_delete_from_txt (const char* filename, const char* passname, FILE* filetxt) {
	FILE* temp_file = fopen("temp_database.txt", "w");
    if (temp_file == NULL) {
        printf("Ошибка в создании временного файла");
        return;
    }

    Passenger pass = (Passenger)malloc(sizeof(*pass));
    int flag = 0;
    rewind(filetxt); 
    while (passenger_read_txt(pass,filetxt)) {
        if (strncmp(pass->surname, passname, LEN_STR) == 0) {
            flag = 1; 
            continue; 
        }

        if (ftell(temp_file) != 0) {
            fprintf(temp_file, "\n");
        }

        passenger_write_txt(pass,temp_file);
    }

    free(pass);
    fclose(temp_file);
    if (!flag) {
        printf("Студент '%s' не найден в файле'%s'.\n", passname, filename);
        return;
    }
    
    int rem = remove(filename);
    int ren = rename("temp_database.txt", filename);

	if (rem != 0) {
        printf("Ошибка в переименовании файла\n");
        return;
    }

    if (ren != 0) {
        printf("Ошибка в переименовании файла\n");
        return;
    }
}

void passenger_delete_from_bin (const char* filename, const char* passname, FILE* filebin) {
	FILE* temp_file = fopen("temp_database.bin", "w");
    if (temp_file == NULL) {
        printf("Ошибка в создании временного файла");
        return;
    }

    Passenger pass = (Passenger)malloc(sizeof(*pass));
    int flag = 0; 
    rewind(filebin);
    while (passenger_read_bin(pass,filebin)) {
        if (strncmp(pass->surname, passname, strlen(passname)) == 0) {
            flag = 1; 
            continue; 
        }

        passenger_write_bin(pass,temp_file);
    }

    free(pass);
    fclose(temp_file);
    if (!flag) {
        printf("Студент '%s' не найден в файле'%s'.\n", passname, filename);
        return;
    }
   
    int rem = remove(filename);
    int ren = rename("temp_database.bin", filename);

	if (rem != 0) {
        printf("Ошибка в переименовании файла\n");
        return;
    }

    if (ren != 0) {
        printf("Ошибка в переименовании файла\n");
        return;
    }
}

int search_max (Passenger* pass, int size) {
    int indmax1 = 0, indmax2 = 0;
    for(int i = 1; i < size; i++) {
        indmax1 = pass[indmax1]->luggage < pass[i]->luggage ? i : indmax1;
        indmax2 = pass[indmax2]->weight < pass[i]->weight ? i : indmax2;
    }

    if(indmax1 == indmax2) 
        return indmax1;
    else return -1;
}

void pass_free(Passenger* pass, int size) {
    for(int i = 0; i < size; i++) {
        free(pass[i]);
    }

    free(pass);
}