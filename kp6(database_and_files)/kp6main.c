//Курсовая работа. Задание №6. Вариант 39
//Выполнил студент группы М8О-104Б-22
//Тесля Данила Сергеевич

#include "inout.h"        
#include "passenger.h"
#include "search.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Введите:\n%s ./file_txt ./file_bin\n", argv[0]);
		exit(0);
	}

	FILE* filetxt = fopen(argv[1], "a+");
	FILE* filebin = fopen(argv[2], "a+b");

	if (!filetxt || !filebin) {
		printf("Не удалось открыть один из файлов\n");
		exit(1);
	}

    int flag = 0;
    while (1) {
    	printf("Что Вы хотите сделать?\n [1]-Вывести содержимое бинарного файла\n\
 [2]-Вывести содержимое текстового файла\n [3]-Добавить в текстовый файл\n\
 [4]-Добавить в бинарный файл\n [5]-Удалить из текстового файла\n [6]-Удалить из бинарного файла\n\
 [7]-Поиск пассажира по условию варианта\n [0]-Завершить\n");
    	scanf("%d", &flag);
    	switch(flag) {
    		case PRINTBIN:
    			fclose(filebin);
    			filebin = fopen(argv[2], "a+b");
    			if (!filebin) {
					printf("Не удалось открыть файл\n");
					exit(1);
				}

    			passenger_print_from_bin(filebin);
    			break;

    		case PRINTTXT:
    			fclose(filetxt);
    			filetxt = fopen(argv[1], "a+");
    			if (!filetxt) {
					printf("Не удалось открыть файл\n");
					exit(1);
				}

    			passenger_print_from_txt(filetxt);
    			break;

    		case ADDTOTXT:
    			fclose(filetxt);
    			filetxt = fopen(argv[1], "a+");
    			if (!filetxt) {
					printf("Не удалось открыть файл\n");
					exit(1);
				}
				
    			passenger_add_to_txt(filetxt);
    			break;

    		case ADDTOBIN:
    			fclose(filebin);
    			filebin = fopen(argv[2], "a+b");
    			if (!filebin) {
					printf("Не удалось открыть файл\n");
					exit(1);
				}

    			passenger_add_to_bin(filebin);
    			break;

    		case DELETEFROMTXT:
    			char buffer[LEN_STR];
    			printf("Введите фамилию пассажира, которого нужно удалить из списка:\t");
    			scanf("%s", buffer);
    			passenger_delete_from_txt(argv[1], buffer, filetxt);
    			break;

			case DELETEFROMBIN:
				char buffer1[LEN_STR];
    			printf("Введите фамилию пассажира, которого нужно удалить из списка:\t");
    			scanf("%s", buffer1);
				passenger_delete_from_bin(argv[2], buffer1, filebin);
				break;

			case SEARCH:
				int index = 0, size = 0;
				Passenger* pass = (Passenger*)malloc(sizeof(**pass));
				pass[index] = (Passenger)malloc(sizeof(**pass));
				rewind(filebin);
    			while (passenger_read_bin(pass[index], filebin)) {
   					index++;
   					size++;
   					pass[index] = (Passenger)malloc(sizeof(**pass));
   					pass = (Passenger*)realloc(pass, (size+1) * sizeof(**pass));
    			} 

    			free(pass[index]);
    			pass = (Passenger*)realloc(pass, size * sizeof(**pass));

				int ind = search_max(pass,size);
				if (ind!=-1) {
					printf("\nДа, такой пассажир есть: %s %s \n", pass[ind]->surname, pass[ind]->initials);
				} else {
					printf("\nТакого пассажира нет в списке.\n");
				}

				pass_free(pass,size);
				break;

			default:
				fclose(filetxt);
				fclose(filebin);
				return 0;
		}
    }
}