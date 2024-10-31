#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int* elem;
	int size;
} vector;

typedef struct {
	vector* row; //Вектор хранит значения ИНДЕКСОВ СТРОК КАЖДОГО ИЗ ЭЛЕМЕНТОВ
	vector* col; //Вектор хранит значения ИНДЕКСОВ СТОЛБЦОВ КАЖДОГО ИЗ ЭЛЕМЕНТОВ
	vector* value; //Вектор хранит значения элементов матрицы
} matrix;

typedef enum {
    PRINTSP = 1,
    PRINTSTD = 2,
    TRANSPOSE = 3,
    CHECK = 4
} var_flags;

vector* vector_create (vector* vec);
matrix* matrix_create (matrix* mat);
void vector_pushback (vector* vec, int value);
void vector_print(vector* vec);
void spmatrix_print (matrix* mat);
void stdmatrix_print (matrix* mat, int m, int n);
void vector_free (vector* vec);
void matrix_free (matrix* mat);
matrix* transpose (matrix* mat, int m, int n);
bool is_symmetric (matrix* mat, int m, int n);


#endif