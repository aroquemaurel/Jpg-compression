#include "compressor.h"

void utilsValues(image* img) {
	char* buff = malloc(sizeof(char) * img->size);
	int lastBlockCase = 0;
	int firstBlockCase = 0;
	int k = 0;
	bool endZero = false;

	for(BlockIterator it = blockIterator_new(img->data, img->w, img->h) ; 
			blockIterator_hasNext(it) ;
			blockIterator_next(&it)) {
		k = 0;
		for(int j = 63 ; j >= 0 ; --j) {
			if(img->data[it.pos-(63-j)] != 0) {
				if(!endZero) {
					buff[firstBlockCase] = j+1;
					lastBlockCase = firstBlockCase+j+1;
					endZero = true;
				}
			}
			if(endZero) {
				buff[lastBlockCase-(k++)] = img->data[it.pos-(63-j)];
			}
		}
		if(!endZero) {
			lastBlockCase = firstBlockCase;
		}
		firstBlockCase = lastBlockCase+1;
		endZero = false;
	}

	for(int i = 0 ; i < lastBlockCase+1; ++i) {
		img->data[i] = buff[i];
	}
	img->size = lastBlockCase+1;
	free(buff);
}

void testDct(image* input, image* output, Block b, float* quantify) {
	for(int i = 0 ; i < input->w ; i +=8 ) {
		for(int j = 0 ; j < input->h ; j += 8) {
			dct(input,b.data,i,j);
			if(b.normalize) {
				block_setNormalize(&b,quantify[0]);
			} else {
				block_setQuantification(&b,quantify);
			}
			setBlock(output,b, i,j);
		}
	}
}

void vectorize(image* input, image* output, const float* quantify) {
	ZIterator zit;
	output->size = 0;
	output->h = input->h;
	output->w = input->w;
	
	for(int i = 0 ; i < input->w ; i +=8 ) {
		for(int j = 0 ; j < input->h ; j += 8) {
			float block[8*8];			
			dct(input, block, j, i);
			for(int k = 0 ; k < 64 ; ++k) {
				block[k] /= (quantify[k]);
			}
			zit = zIterator_new(block, 8);

			output->data[(output->size)++] = round(zIterator_value(zit)); 
			while(zIterator_hasNext(zit)) {
				output->data[(output->size)++] = round(zIterator_next(&zit));
			}
		}
	}
}
