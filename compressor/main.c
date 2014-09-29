#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "ZIterator.h"
#include "blockiterator.h"
#include "dct-idct.h"
#include "block.h"
#include "util.h"
#include "compressor.h"

typedef struct{
	int compress;
	char inFilename[256];
	char outFilename[256];
} s_args;


void usage(char * progname);
void parseArgs(char *argv[], s_args* args);
const float* getQuantumMatrix();
float* getNormalizeMatrix();
void allocPgmOutput(image* img, image* output, char inFileName[256]);
void allocCompressedOutput(image* img, image* output, char inFileName[256]);
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


	switch(args.compress) {
		case 0 : // decompression
			break;
		case 1 : // compression
			allocPgmOutput(&img,&output,args.inFilename);
			vectorize(&img, &output, getQuantumMatrix());
				
			utilsValues(&output);
			writeCompressed(args.outFilename,&output);
			break;
		case 2 : // test dct
			allocPgmOutput(&img,&output,args.inFilename);
			block.normalize = true;
			applyDct(&img, &output, block, getNormalizeMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 3 : // test quantify
			allocPgmOutput(&img,&output,args.inFilename);
			block.normalize = false;
			applyDct(&img, &output, block, getQuantumMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 4 : // test vectorize
			allocPgmOutput(&img,&output,args.inFilename);
			vectorize(&img, &output, getQuantumMatrix());
			writePgm(args.outFilename,&output);
			break;
		case 5 : // compute and print error

			break;
		case 6: // Inverse utils values
			allocCompressedOutput(&img,&output,args.inFilename);
			obtainsSignificativesValues(&img,&output);
			writePgm(args.outFilename, &output);
			break;
		case 7: // Inverse vectorize
			allocPgmOutput(&img,&output,args.inFilename);
			invVectorize(&img, &output);
			writePgm(args.outFilename, &output);
			break;
		case 8: // Inverse Quantify
			break;
		case 9: // Inverse dct
			break;
		default :
			usage(argv[0]);
	}

	free(img.data);
	free(output.data);

	return 0;
}
void allocPgmOutput(image* img, image* output, char inFileName[256]) {
	readPgm(inFileName, img);
	output->data = (char*)malloc(img->h*img->w*sizeof(char));
	output->h = img->h;
	output->w = img->w;
}

void allocCompressedOutput(image* img, image* output, char inFileName[256]) {
	readCompressed(inFileName, img);
	output->data = (char*)malloc(img->h*img->w*sizeof(char));
	output->h = img->h;
	output->w = img->w;
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
