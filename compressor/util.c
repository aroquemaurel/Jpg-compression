#include "util.h"
#include <stdio.h>

void printMatrix(float** matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i][j] < 10 && matrix[i][j] >= 0) {
				printf("0%.1f ", matrix[i][j]);
			} else {
				printf("%.1f ", matrix[i][j]);
			}
		}
		printf("\n");
	}
}

void printMatrixAsACharVector(char* matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i*width+j] < 10 && matrix[i*width+j] >= 0) {
				printf("0%d ", matrix[i*width+j]);
			} else {
				printf("%d ", matrix[i*width+j]);
			}
		}
		printf("\n");
	}
}

void printMatrixAsAFloatVector(float* matrix, const int width, const int height) {
	for(int i = 0 ; i < height ; ++i) {
		for(int j = 0 ; j < width ; ++j) {
			if(matrix[i*width+j] < 10 && matrix[i*width+j] >= 0) {
				printf("0%.1f ", matrix[i*width+j]);
			} else {
				printf("%.1f ", matrix[i*width+j]);
			}
		}
		printf("\n");
	}
}

void printCharVector(char* vector, const int size) {
	for(int i = 0 ; i < size ; ++i) {
		printf("%d ", vector[i]);
	}
}
