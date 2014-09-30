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
	//	float* buff = calloc(sizeof(float), 8*8);
	char* buff = malloc(sizeof(char) * in->w * in->h);
	Block block = block_new();
	float v;
	int colBlock = 0;
	int lineBlock = 0;
	printMatrixAsACharVector(in->data,16,16);  
	for(int i = 0 ; i < in->h * in->w ; i += 64) { // Iterator on image : block by block
		int kIn = 0;
		ZIterator zit = zIterator_new(block.data,8);
		block.data[0] = in->data[i]; 
		while(zIterator_hasNext(zit)) {
			block.data[zit.line * 8 + zit.column] = in->data[i+(kIn++)];
			zIterator_next(&zit);
		}
		printf("\n");
		int kOut = 0;
		for(int n = lineBlock; n < lineBlock+8 ; ++n) {
			for(int m = colBlock; m < colBlock+8 ; ++m) {
				buff[n*in->w+m] = block.data[kOut++];
			}
		}
		colBlock += 8;
		if(colBlock >= in->w) {
			colBlock = 0;
			lineBlock += 8;
		}
	}
	printMatrixAsACharVector(buff, 16,16);
	for(int i = 0 ; i < in->h * in->w ; ++i) {
		out->data[i] = buff[i];
	}
	out->size = in->size;

}
