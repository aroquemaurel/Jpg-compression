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
	//	float* buff = calloc(sizeof(float), 8*8);
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
		for(int n = lineBlock; n < lineBlock+8 ; ++n) {
			for(int m = colBlock; m < colBlock+8 ; ++m) {
				buff[n*in->w+m] = block.data[kOut] * quantify[kOut];
				++kOut;
			}
		}
		colBlock += 8;
		if(colBlock >= in->w) {
			colBlock = 0;
			lineBlock += 8;
		}
	}
	for(int i = 0 ; i < in->h * in->w ; ++i) {
		out->data[i] = round(buff[i]);
	}
		out->size = in->size;

	block = block_new();
	for(int i = 0 ; i < in->w ; i+= 8) {
		for(int j = 0 ; j < in->h ; j += 8) {
			idct(out,block.data,i,j);
			printMatrixAsAFloatVector(block.data, 8, 8);
			printf("\n");
//			for(int k = 0 ; k < 64 ; ++k) {
//				out->data[(j+k/8) * out->w + (i+k%8)] = block.data[k];
//			}
		}
	}
	
//	for(int i = 0 ; i < in->h * in->w ; i += 64) { // Iterator on image : block by block
//			int kOut= 0;
//		for(int n = lineBlock; n < lineBlock+8 ; ++n) {
//			for(int m = colBlock; m < colBlock+8 ; ++m) {
//			//	out->data[n*in->w+m] = block.data[kOut]; 
//				++kOut;
//			}
//		}
//		colBlock += 8;
//		if(colBlock >= in->w) {
//			colBlock = 0;
//			lineBlock += 8;
//		}
//	}
}
