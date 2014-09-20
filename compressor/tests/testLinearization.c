#include <stdio.h>
#include <stdlib.h>

#include "../linearization.h"
#include "../util.h"

int main(int argc, char *argv[])
{
	char* data;
	int k = 0;
	data = (char*)malloc(sizeof(char)*8*8);
	for(int i = 0 ; i < 8*8 ; ++i) {
		data[i] = k++;
	}
	printMatrix(data, 8, 8);
	LinearizationIterator it = iterator_new(data, 8);	
	while(iterator_hasNext(it)) {
		printf("%d ", iterator_next(&it));
	}
//	printf("%d", iterator_next(it));
	return EXIT_SUCCESS;
}
