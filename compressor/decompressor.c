#include "decompressor.h"
#include "util.h"
#include "blockiterator.h"
#include "ZIterator.h"
#include "dct-idct.h"

void invUtilsValues(image* in, image* out) {
	int nbValues = 0; 
	int j = 0;
	out->data = calloc(sizeof(char) * out->w * out->h, sizeof(char)); // Init data with 0

	for(int i = 0 ; i < in->size ; ++i) {
		if(nbValues == 0) { // 0 values
			nbValues = in->data[i];
			if(nbValues == 0) { // No significative value
				j += 64;
			}
			while(j % 64 != 0) {
				++j;
			}
		} else {
			--nbValues;
			out->data[j++] = in->data[i]; // SIgnificative value
		}
	}
}

void uncompress(image* in, image* out, const float* quantify) {
	Block block = block_new();
	int colBlock = 0;
	int lineBlock = 0;
	int kIn = 0;
	int n,m;
	out->size = in->h*in->w;
	out->h = in->h;
	out->w = in->w;

	// Iterator on image : block by block
	for(int i = 0 ; i < in->h * in->w ; i += 64) { 
		kIn = 0;
		ZIterator zit = zIterator_new(block, 8);

		// Z Parcours for reposition of blocks
		block.data[0] = in->data[i];  // First iterator value
		while(zIterator_hasNext(zit)) {
			block.data[zit.line*8 + zit.column] = in->data[i + (kIn++)]; 
			zIterator_next(&zit);
		}
		block.data[zit.line*8 + zit.column] = in->data[i + (kIn++)]; // last pixel

		// Quantify
		for(n = 0; n < 8 ; ++n) {
			for(m = 0; m < 8 ; ++m) {
				block.data[n*8 + m] *= quantify[n*8 + m];
			}
		}
		idct(out, block.data, colBlock, lineBlock);
		colBlock += 8;
		if(colBlock >= in->w) {
			colBlock = 0;
			lineBlock += 8;
		}
	}

	block_delete(&block);
}
