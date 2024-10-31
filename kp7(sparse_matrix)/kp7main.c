//Курсовая работа. Задание №7. Вариант [3,11]
//Выполнил студент группы М8О-104Б-22
//Тесля Данила Сергеевич

#include "matrix.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Введите:\n%s ./file_txt \n", argv[0]);
        exit(0);
    }

	FILE* input = fopen(argv[1], "r");
	if (!input) { 
        printf("Не удалось открыть файл\n");
        exit(1);
    }

    matrix* spmatrix = NULL;
    spmatrix = matrix_create(spmatrix);
    int value = 0, m = 0, n = 0, indrow = 0, indcol = 0, temp = 0, flag = 0;
    if (!fscanf(input, "%d %d", &m, &n)) {
        printf("Некорректные данные файла\n");
        exit(1);
    }

    while (!feof(input)) {
        if(!fscanf(input, "%d", &value)) {
            printf("Некорректные данные файла\n");
            exit(1);
        }
        
        if(value != 0) {
            vector_pushback(spmatrix->row, indrow);
            vector_pushback(spmatrix->col, indcol);
            vector_pushback(spmatrix->value, value);
        }

        indcol++;
        if(indcol == n) {
            indrow++;
            indcol = 0;
        }
    }

    fclose(input);

    while (1) {
        printf("Что Вы хотите сделать?\n [1]-Вывести разреженную матрицу\n [2]-Вывести матрицу в привычном виде\n\
 [3]-Транспонировать матрицу отн. побочн. диагонали\n [4]-Проверить, является ли она кососимметрической\n\
 [0]-Завершить\n");
        fscanf(stdin, "%d", &flag);

        switch (flag) {
            case PRINTSP:
                spmatrix_print(spmatrix);
                break;

            case PRINTSTD:
                stdmatrix_print(spmatrix, m, n);
                break;

            case TRANSPOSE:
                spmatrix = transpose(spmatrix, m, n);
                temp = m;
                m = n;
                n = temp;
                break;

            case CHECK:
                if (is_symmetric(spmatrix, m, n)) {
                    printf("Да, эта матрица - кососимметрическая\n");
                } else {
                    printf("Нет, эта матрица не явл. кососимметрической\n");
                }

                break;

            default:
                matrix_free(spmatrix);
                return 0;
        }
    }
}