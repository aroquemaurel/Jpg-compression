#include "compressor.h"
#include "decompressor.h"
#include "blockiterator.h"
#include "ZIterator.h"
#include "dct-idct.h"

const float* getQuantumMatrix() {
	static const float matrix[64] = {16, 11, 10, 16, 24,  40,  51,  61,
		12,  12, 14, 19, 26,  58,  60,  55,
		14,  13, 16, 24, 40,  57,  69,  56,
		14,  17, 22, 29, 51,  87,  80,  62,
		18,  22, 37, 56, 68,  109, 103, 77,
		24,  35, 55, 64, 81,  104, 113, 92,
		49,  64, 78, 87, 103, 121, 120, 101,
		72,  92, 95, 98, 112, 100, 103, 99
	};

	return matrix;
}

float* getNormalizeMatrix() {
	static float matrix[64];
	for(int i=0 ; i < 64 ; ++i) {
		matrix[i] = 8.f;
	}

	return matrix;
}

void utilsValues(image* img) {
	char* buff = malloc(sizeof(pixel_t) * img->size);
	int lastBlockCase = 0;
	int firstBlockCase = 0;
	int k = 0;
	bool endZero = false;
	int j;
	BlockIterator it;

	for(it = blockIterator_new(img->data, img->w, img->h) ; 
			blockIterator_hasNext(it) ;
			blockIterator_next(&it)) {
		k = 0;
		for(j = 63 ; j >= 0 ; --j) {
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
	blockIterator_delete(&it);
}

void applyDct(image* input, image* output, bool normalize, const float* quantify) {
	Block b = block_new();
	for(int i = 0 ; i < input->w ; i +=8 ) {
		for(int j = 0 ; j < input->h ; j += 8) {
			dct(input,b.data,i,j);
			if(normalize) {
				block_setNormalize(&b,quantify[0]);
			} else {
				block_setQuantification(&b,quantify);
			}
			setBlock(output,b, i,j);
		}
	}
}
double getCompressionError(image* img) {
	double error = 0;		
	image compressImg;			
	image uncompressImg;		

	compressImg.data = malloc(sizeof(pixel_t) * img->h * img->w);
	uncompressImg.data = malloc(sizeof(pixel_t) * img->h * img->w);
	compress(img, &compressImg, getQuantumMatrix());
	uncompress(&compressImg, &uncompressImg, getQuantumMatrix());

	for (int i = 0; i < img->h*img->w; i++) {
		error += pow(img->data[i] - uncompressImg.data[i], 2);	
	}
	error /= img->h*img->w;

	free(compressImg.data);
	free(uncompressImg.data);

	return error;
}

void vectorize(image* input, image* output, const float* quantify) {
	ZIterator zit;
	Block block; 
	int i, j;
	output->size = 0;
	output->h = input->h;
	output->w = input->w;

#pragma omp parralel for private(i,j)	
	for(i = 0 ; i < input->w ; i +=8 ) {
		for(j = 0 ; j < input->h ; j += 8) {
			block = block_new();
			dct(input, block.data, j, i);
			block_applyQuantify(&block,quantify);
			zit = zIterator_new(block, 8);

			output->data[(output->size)++] = round(zIterator_value(zit)); 
			while(zIterator_hasNext(zit)) {
				output->data[(output->size)++] = round(zIterator_next(&zit));
			}

			zIterator_delete(&zit);
			block_delete(&block);
		}
	}
}

void compress(image* input, image* output, const float* quantify) {
	vectorize(input, output, quantify);
	utilsValues(output);
}
