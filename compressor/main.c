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
#include "decompressor.h"

typedef struct{
	int compress;
	char inFilename[256];
	char outFilename[256];
} s_args;

void usage(char * progname);
void parseArgs(char *argv[], s_args* args);
void allocOutput(image* img, image* output);

int main(int argc, char** argv) {
	s_args args;
	if(argc != 4) {
		usage(argv[0]);
	} else {
		parseArgs(argv, &args);
	}

	image img;
	image output;
	Block block = block_new();

	switch(args.compress) {
		case 0 : // decompression
			readCompressed(args.inFilename, &img);
			allocOutput(&img,&output);
			invUtilsValues(&img,&output);
			free(img.data);
			img.data = malloc(sizeof(char) * output.h*output.w);
			for(int i = 0 ; i < output.h * output.w ; ++i ) {
				img.data[i] = output.data[i];
			}
			uncompress(&img, &output, getQuantumMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 1 : // compression
			readPgm(args.inFilename, &img);
			allocOutput(&img, &output);
			compress(&img, &output, getQuantumMatrix());
			writeCompressed(args.outFilename,&output);
			break;
		case 2 : // test dct
			readPgm(args.inFilename, &img);
			allocOutput(&img,&output);
			applyDct(&img, &output, true, getNormalizeMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 3 : // test quantify
			readPgm(args.inFilename, &img);
			allocOutput(&img,&output);
			applyDct(&img, &output, false, getQuantumMatrix());
			writePgm(args.outFilename, &output);
			break;
		case 4 : // test vectorize
			readPgm(args.inFilename, &img);
			allocOutput(&img,&output);
			vectorize(&img, &output, getQuantumMatrix());
			writePgm(args.outFilename,&output);
			break;
		case 5 : // compute and print error
			readPgm(args.inFilename, &img);
			allocOutput(&img,&output);
			printf("Erreur compression of %s : %.1f\n", args.inFilename, getCompressionError(&img));
			break;
		case 6: // Inverse utils values
			readCompressed(args.inFilename, &img);
			allocOutput(&img,&output);
			invUtilsValues(&img,&output);
			writePgm(args.outFilename, &output);
			break;
		default :
			usage(argv[0]);
	}

	free(img.data);
	free(output.data);
	free(getCos());

	return EXIT_SUCCESS;
}
void allocOutput(image* img, image* output) {
	output->data = (char*)malloc(img->h*img->w*sizeof(pixel_t));
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

