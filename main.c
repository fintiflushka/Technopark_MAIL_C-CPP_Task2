#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


void print_elem(void* elem);
void* read_matrix(FILE* input);


int main(int argc, char** argv) {
	if (argc < 2) {
		perror("Недостаточно аргументов командной строки.");
		return 0;
	}

	void* matr_1 = NULL;

	int i = 1;
	for (i = 1; i < argc; i++) {
		char* file_name = argv[i];
		FILE* input = fopen(file_name, "r");

	  	if (input == NULL) { 
	  		perror(file_name);
	  		perror("Не удалось открыть файл"); // read about strerror
			exit(0);
		}

		void* matr_2 = read_matrix(input);
		fclose(input);
		if (!matr_2) {
			perror(file_name);
			perror("Ошибка создания матрицы");
			exit(0);
		}

		if(matr_1) {
			void* matr_3 = mult(matr_1, matr_2);
			delete_matrix(matr_1);
			delete_matrix(matr_2);
			matr_1 = matr3;
		}
		else {
			matr_1 = matr_2;
		}
	}

	if (matr_1) {
		print_matrix(matr_1, print_elem);
	}
	else {
		perror("Не удалось перемножить матрицы");
	}

	delete_matrix(matr_1);

  	return 0;
}


void print_elem(void* elem) {
	printf("%lf ", *((double*) elem));
}


void* read_matrix(FILE* input) {
	int rows_count;
	int cols_count;
	int elem_count;

	if (fscanf(input, "%d\n%d\n%d\n", &rows_count, &cols_count, &elem_count) < 3){
		return NULL;
    }; 

    void* matr = create_matrix(rows_count, cols_count, 0);
    if (!matr){
    	return NULL;
    }

    int row;
    int col;
    double elem;

    int j;
    for(j = 0; fscanf(input, "%d%*c%d%*c%lf\n", &row, &col, &elem) == 3; j++) {
    	set_elem(matr, row - 1, col - 1, elem);
    }

    if (j != elem_count) {
    	return NULL;
    }

    return matr;
}
