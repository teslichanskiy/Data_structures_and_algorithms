#include "inout.h"
#include "passenger.h"

int main (int argc, char* argv[]) {
	if (argc != 3) {
		printf("Введите:\n%s ./file_txt ./file_bin\n", argv[0]);
        exit(0);
	}

	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "wb");

	if (!input || !output) {
		printf("Не удалось открыть один из файлов\n");
		exit(1);
	}

    Passenger pass = (Passenger)calloc(1, sizeof(*pass));
    while (passenger_read_txt(pass, input)) {
    	passenger_write_bin(pass, output);
    }

    free(pass);
    fclose(input);
    fclose(output); 
    return 0;
}