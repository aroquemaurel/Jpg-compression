#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "linearization.h"
#include "dct-idct.h"

typedef struct{
	int compress;
	char inFilename[256];
	char outFilename[256];
} s_args;


void usage(char * progname);
void parseArgs(char *argv[], s_args* args);

int main(int argc, char** argv) {
	s_args args;
	if(argc!=4) {
		usage(argv[0]);
	} else {
		parseArgs(argv, &args);
	}

	image img;
	image output;
	float* data = (float*)malloc(sizeof(float)*8*8); 

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

			for(int i = 0 ; i < img.w ; i +=8 ) {
				for(int j = 0 ; j < img.h ; j += 8) {
					dct(&img,(float*)data,i,j);
					for(int k = 0 ; k < 64 ; ++k) {
						data[k] /= 8.f;
						output.data[(j+k/8) * output.w + (i+k%8)] = data[k];
					}
				}
			}

			writePgm(args.outFilename,&output);
			break;
		case 3 : // test quantify

			break;
		case 4 : // test vectorize

			break;
		case 5 : // compute and print error

			break;
		default :
			usage(argv[0]);
	}
	return 0;
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
