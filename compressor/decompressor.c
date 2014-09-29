#include "decompressor.h"
#include "util.h"

void obtainsSignificativesValues(image* in, image* out) {
	int nbValues = 0; 
	int j = 0;
	out->data = calloc(sizeof(char) * out->w * out->h, sizeof(char));
	printCharVector(in->data,in->size);

	for(int i = 0 ; i < in->size ; ++i) {
		if(nbValues == 0) {
			nbValues = in->data[i];
			if(nbValues == 0) {
				j += 64;
			}
			while(j % 64 != 0) {
				++j;
			}
		} else {
			--nbValues;
			out->data[j++] = in->data[i];
		}
	}
}
