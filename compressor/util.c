#include "util.h"
#include <stdio.h>

void printMatrix(char** matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i][j] < 10) {
				printf("0%d ", matrix[i][j]);
			} else {
				printf("%d ", matrix[i][j]);
			}
		}
		printf("\n");
	}
}
