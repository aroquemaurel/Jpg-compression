#include "decompressor.h"

void obtainsSignificativesValues(image* in, image* out) {
	int nbValues = 0;
	int j = 0;
	for(int i = 0 ; i < in->size ; ++i) {
		if(nbValues == 0) {
			while(i % 64 != 0) {
				out->data[j++] = 0;
			}
			nbValues = in->data[i];
		} else {
			--nbValues;
			out->data[j++] = in->size;
		}
	}
}
