#include "matrix.h"

vector* vector_create (vector* vec) { 
	vec = (vector*)malloc(sizeof(vector));
    vec->size = 0;
    vec->elem = NULL;
    return vec;
}

matrix* matrix_create (matrix* mat) {
	mat = (matrix*)malloc(sizeof(matrix));
	mat->row = NULL;
	mat->row = vector_create(mat->row);
	mat->col = NULL;
	mat->col = vector_create(mat->col);
	mat->value = NULL;
	mat->value = vector_create(mat->value);
	return mat;
}

void vector_pushback (vector* vec, int value) {
	vec->size++;
	vec->elem = (int*)realloc(vec->elem, vec->size * sizeof(int));
	vec->elem[vec->size - 1] = value;
}

void vector_print(vector* vec) {
	printf("(");
	for(int i = 0; i < vec->size; i++) {
		printf("%3d ", vec->elem[i]);
	}
	printf(")\n");
}

void spmatrix_print (matrix* mat) {
	vector_print(mat->row);
	vector_print(mat->col);
	vector_print(mat->value);
	printf("\n");
} 

void stdmatrix_print (matrix* mat, int m, int n) {
	int ind = 0;
	for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {   
            if (i == mat->row->elem[ind] && j == mat->col->elem[ind]) {
                printf("%3d ", mat->value->elem[ind]);
                if (ind != mat->value->size - 1) {
                	ind++;
                }

            } else {
                printf("%3d ", 0);
            }

            if (j == n - 1) {
                printf("\n");
            }
        }
    }

    printf("\n");
}

matrix* transpose (matrix* mat, int m, int n) {
	matrix* spmat = NULL;
	spmat = matrix_create(spmat);
	int indcol = 0, indvec = 0;

	if (m == n) {
		for (indcol = n - 1; indcol >= 0; indcol--) {
			for(indvec = mat->col->size - 1; indvec >= 0; indvec--) {
				if(mat->col->elem[indvec] == indcol) {
					vector_pushback(spmat->row, n - indcol - 1);
					vector_pushback(spmat->col, n - mat->row->elem[indvec] - 1);
					vector_pushback(spmat->value, mat->value->elem[indvec]);
				}
			}
		}
	}

	if (n > m) {
		for (indcol = m - 1; indcol >= 0; indcol--) {
			for(indvec = mat->col->size - 1; indvec >= 0; indvec--) {
				if(mat->col->elem[indvec] == indcol) {
					vector_pushback(spmat->row, m - indcol - 1);
					vector_pushback(spmat->col, m - mat->row->elem[indvec] - 1);
					vector_pushback(spmat->value, mat->value->elem[indvec]);
				}
			}
		}

		for (indcol = m; indcol < n; indcol++) {
			for(indvec = 0; indvec < mat->row->size; indvec++) {
				if(mat->col->elem[indvec] == indcol) {
					vector_pushback(spmat->row, indcol);
					vector_pushback(spmat->col, mat->row->elem[indvec]);
					vector_pushback(spmat->value, mat->value->elem[indvec]);
				}
			}
		}
	}

	if (m > n) {
		for (indcol = n - 1; indcol >= 0; indcol--) {
			for(indvec = mat->col->size - 1; indvec >= 0; indvec--) {
				if(mat->col->elem[indvec] == indcol && mat->row->elem[indvec] < n) {
					vector_pushback(spmat->row, n - indcol - 1);
					vector_pushback(spmat->col, n - mat->row->elem[indvec] - 1);
					vector_pushback(spmat->value, mat->value->elem[indvec]);
				}
			}
 
			for (indvec = 0; indvec < mat->row->size; indvec++) {
				if(mat->col->elem[indvec] == n - indcol - 1 && mat->row->elem[indvec] < m && mat->row->elem[indvec] >= n) {
					vector_pushback(spmat->row,	n - indcol - 1);
					vector_pushback(spmat->col, mat->row->elem[indvec]);
					vector_pushback(spmat->value, mat->value->elem[indvec]);
				}
			}
			
		}
	}
	
	matrix_free(mat);
	return spmat;
}

bool is_symmetric (matrix* mat, int m, int n) {
	if (m != n) {
		return false;
	} 

	int indcol = 0, indvec = 0, indvec1 = 0, flag = 0;
	for (indcol = 0; indcol < n/2; indcol++) {
		for (indvec = 0; indvec < mat->row->size; indvec++) {
			if (mat->row->elem[indvec] == mat->col->elem[indvec]) {
				return false;
			}

			if (mat->row->elem[indvec] == indcol && mat->col->elem[indvec] == n - 1 - indcol) {
				for (indvec1 = 0; indvec1 < mat->row->size; indvec1++) {
					if (mat->col->elem[indvec1] == indcol && mat->row->elem[indvec1] == n - 1 - indcol) {
						flag = 1;
						if (mat->value->elem[indvec] != (-1) * mat->value->elem[indvec1]) {
							return false;
						} else {
							break;
						}
					}
				}

				if (flag == 0) {
					return false;
				}

				flag = 0;
			}
		}
	}

	return true;
}

void vector_free (vector* vec) { 
	vec->size = 0;
    free(vec->elem);
}

void matrix_free (matrix* mat) {
	vector_free(mat->row);
	vector_free(mat->col);
	vector_free(mat->value);
	free(mat->row);
	free(mat->col);
	free(mat->value);
	free(mat);
}
