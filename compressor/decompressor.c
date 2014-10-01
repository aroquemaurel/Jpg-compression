#include "decompressor.h"
#include "util.h"
#include "blockiterator.h"
#include "ZIterator.h"
#include "dct-idct.h"

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

void invVectorize(image* in, image* out, float* quantify) {
	char* buff = malloc(sizeof(char) * in->w * in->h);
	Block block = block_new();
	float v;
	int colBlock = 0;
	int lineBlock = 0;
	for(int i = 0 ; i < in->h * in->w ; i += 64) { // Iterator on image : block by block
		int kIn = 0;
		ZIterator zit = zIterator_new(block.data,8);
		block.data[0] = in->data[i]; 
		while(zIterator_hasNext(zit)) {
			block.data[zit.line * 8 + zit.column] = in->data[i+(kIn++)];
			zIterator_next(&zit);
		}
		int kOut = 0;
		for(int n = 0; n < 8 ; ++n) {
			for(int m = 0; m < 8 ; ++m) {
				block.data[n*8+m] *= quantify[n*8+m];
			}
		}
		idct(out, block.data, colBlock, lineBlock);
		colBlock += 8;
		if(colBlock >= in->w) {
			colBlock = 0;
			lineBlock += 8;
		}
	}
}
