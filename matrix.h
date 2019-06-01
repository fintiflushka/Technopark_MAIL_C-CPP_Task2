#include <stddef.h>


typedef struct _Matrix {
    int rows; 
    int cols; 
    double* m; 
} Matrix;


void* create_matrix(int rows, int cols, double def); 
void* copy_matrix(void* matr);
void delete_matrix(void* matr); 
void set_elem(void* matr, int row, int col, double elem);
double get_elem(void* matr, int row, int col);
void* mult(void* matr_1, void* matr_2);
void print_matrix(void* matr, void (*fun)(void*));