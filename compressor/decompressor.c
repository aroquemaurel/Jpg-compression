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
	Block block = block_new();
	int k = 0;
	float v;

	for(int i = 0  ;i < in->h * in->w ; i += 64) {
		k = 0;
			for(ZIterator zit = zIterator_new((in->data)+i, 8); 
					zIterator_hasNext(zit) ; 
					v = zIterator_next(&zit)
			   ) {
//				block.data[zit.line*8 + zit.column] = in->data[k++];
				block.data[k++] = v; 
			}
			// TODO SUppress me
			for(int l = 0 ; l < 64 ; ++l) {
				out->data[in->h*in->w * 64 + l] = block.data[l];
//				out->data[(j+l/8) * out->w + (i+l%8)] = block.data[l];
			}
//			setBlock(out,`< Block block>`,`< const int i>`,`< const int j>`)
	}

}
