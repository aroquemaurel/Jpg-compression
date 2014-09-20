#include "util.h"
#include <stdio.h>

void printMatrix(char* matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i*width+j] < 10) {
				printf("0%d ", matrix[i*width+j]);
			} else {
				printf("%d ", matrix[i*width+j]);
			}
		}
		printf("\n");
	}
}
