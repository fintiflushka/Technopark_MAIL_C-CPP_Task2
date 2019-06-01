#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


void* create_matrix(int rows, int cols, double def) {
    Matrix* matr = (Matrix*)malloc(sizeof(Matrix));
    if (!matr) return NULL;

    matr->rows = rows;
    matr->cols = cols;

    matr->m = (double*)malloc(sizeof(double) * cols * rows);
    if (!matr->m) return NULL;

    void* tmp = matr->m;
    for (int i = 0; i < rows; i++) {
        for (int j; j < cols; j++) {
            *(double*)tmp = def;
            tmp++;
        }
    }

    return matr;
} 


void* copy_matrix(void* matr) {
    Matrix* tmp = matr;

    Matrix* cp_m = create_matrix(tmp->rows, tmp->cols, 0);
    cp_m->m = tmp->m;

    return cp_m;
}


void delete_matrix(void* matr) {
 
    free(matr);
    (matr) = NULL;
}


void set_elem(void* matr, int row, int col, double elem) {
    Matrix* tmp = matr;

    *(double*)(tmp->m + (tmp->cols * row + col)) = elem;
}


double get_elem(void* matr, int row, int col) {
    Matrix* tmp = matr;

    return *(double*)(tmp->m + (tmp->cols * row + col));
}


void* mult(void* matr_1, void* matr_2) {
    Matrix* tmp_1 = matr_1;
    Matrix* tmp_2 = matr_2;

    if (tmp_1->cols != tmp_2->rows) {
        return NULL; 
    }

    Matrix* mult_m = create_matrix(tmp_1->rows, tmp_2->cols, 0);

    for (int i = 0; i < tmp_1->rows; i++) {
        for (int j = 0; j < tmp_2->cols; j++) {
            double elem = 0;
            for (int k = 0; k < tmp_1->cols; k++) {
                elem += get_elem(tmp_1, i, k ) * get_elem(tmp_2, k, j);
            }
            set_elem(mult_m, i, j, elem);
        }
    }

    return mult_m;
}


void print_matrix(void* matr, void (*fun)(void*)) {
    Matrix* tmp = matr;
    for (int i = 0; i < tmp->rows; i++) {
        for (int j = 0; j < tmp->cols; j++) {
            fun(tmp->m);
            tmp->m++;
        }
        printf("\n");
    }
}
