#include "util.h"
#include <stdio.h>

void printMatrix(float** matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i][j] < 10) {
				printf("0%.1f ", matrix[i][j]);
			} else {
				printf("%.1f ", matrix[i][j]);
			}
		}
		printf("\n");
	}
}
