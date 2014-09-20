#include <stdio.h>
#include <stdlib.h>

#include "../linearization.h"
#include "../util.h"

int main(int argc, char *argv[])
{
	float** data;
	data = (float**)malloc(sizeof(float*)*8);
	for(int i = 0 ; i < 8 ; ++i) {
		data[i] = (float*)malloc(sizeof(float)*8);
	}
	float k = 0;
	for(int i = 0 ; i < 8 ; ++i) {
		for(int j= 0 ; j < 8 ; ++j) {
			data[i][j] = k++;
		}
	}
	printMatrix(data, 8, 8);
	LinearizationIterator it = iterator_new(data, 8);	
	printf("%.1f ", iterator_value(it));
	while(iterator_hasNext(it)) {
		printf("%.1f ", iterator_next(&it));
	}
//	printf("%d", iterator_next(it));
	return EXIT_SUCCESS;
}
