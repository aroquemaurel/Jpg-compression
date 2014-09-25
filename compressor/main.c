#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "ZIterator.h"
#include "dct-idct.h"
#include "block.h"

typedef struct{
	int compress;
	char inFilename[256];
	char outFilename[256];
} s_args;


void usage(char * progname);
void parseArgs(char *argv[], s_args* args);
void testDct(image* input, image* output, Block b, float* quantify);
const float* getQuantumMatrix();
float* getNormalizeMatrix();
void vectorize(image* input, image* output, const float* quantify);

int main(int argc, char** argv) {
	s_args args;
	if(argc!=4) {
		usage(argv[0]);
	} else {
		parseArgs(argv, &args);
	}

	image img;
	image output;
	Block block = block_new();

	readPgm(args.inFilename, &img);
	output.data = (char*)malloc(img.h*img.w*sizeof(char));
	output.h = img.h;
	output.w = img.w;

	switch(args.compress) {
		case 0 : // decompression

			break;
		case 1 : // compression
			break;
		case 2 : // test dct
			block.normalize = true;
			testDct(&img, &output, block, getNormalizeMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 3 : // test quantify
			block.normalize = false;
			testDct(&img, &output, block, getQuantumMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 4 : // test vectorize
			vectorize(&img, &output, getQuantumMatrix());
			writeCompressed(args.outFilename,&output);
			break;
		case 5 : // compute and print error

			break;
		default :
			usage(argv[0]);
	}

	return 0;
}
void vectorize(image* input, image* output, const float* quantify) {
	ZIterator zit;
	output->size = 0;
	output->h = input->h;
	output->w = input->w;
	
	for(int i = 0 ; i < input->w ; i +=8 ) {
		for(int j = 0 ; j < input->h ; j += 8) {
			float block[8*8];			
			float block2[8*8];			
			int z = 0;
			dct(input,block,i,j);
			zit = iterator_new(block, 8);

			block2[z++] = block[0]; 
			while(iterator_hasNext(zit)) {
				block2[z++] = iterator_next(&zit);
			}
			for(int k = 0 ; k < 64 ; ++k) {
				block2[k] /= round(quantify[k]);
				output->data[(output->size)++] = block2[k];
			}
			
		}
	}
//	for(int i = 0 ; i < output->size ; ++i) {
//	output->data[i] = 0x42;
//}
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
void usage(char * progname) {
	printf("usage : %s mode in out\n", progname);
	printf("mode \t 0 : decompression, 1 : compression, 2 : save dct (pgm format),\n\t 3 : save quantize (pgm format), 4 : save vectorize (xxx format), 5 output compression loss\n");
	printf("in : input filename, pgm if compression, save dct or save quantize, xxx if decompression\n");
	printf("out : output filename, xxx if compression, pgm if decompression, save dct or save quantize\n");
	exit(EXIT_FAILURE);
}

void parseArgs(char *argv[], s_args* args) {
	args->compress = atoi(argv[1]);
	strncpy(args->inFilename, argv[2], 256);
	strncpy(args->outFilename, argv[3], 256);
}

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
