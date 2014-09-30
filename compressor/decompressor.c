#include "decompressor.h"
#include "util.h"
#include "blockiterator.h"
#include "ZIterator.h"

void obtainsSignificativesValues(image* in, image* out) {
	int nbValues = 0; 
	int j = 0;
	out->data = calloc(sizeof(char) * out->w * out->h, sizeof(char));

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

void invVectorize(image* in, image* out) {
	float* buff = calloc(sizeof(float), 8*8);
	int k = 0;
	Block block = block_new();

	for(int i = 0 ; i < in->w ; i +=8 ) {
		for(int j = 0 ; j < in->h ; j += 8) {
			for(ZIterator zit = zIterator_new(buff, 8); 
					zIterator_hasNext(zit) ; 
					zIterator_next(&zit)
			   ) {
				buff[zit.line*8 + zit.column] = in->data[k++];
			}
			// TODO SUppress me
			for(int l = 0 ; l < 64 ; ++l) {
				out->data[(j+l/8) * out->w + (i+l%8)] = buff[l];
			}
		}	
	}

	free(buff);
}
