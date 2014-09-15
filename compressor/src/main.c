#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "dct-idct.h"

typedef struct {
  int compress;
  char inFilename[256];
  char outFilename[256];
} s_args;

void parseArgs(char *argv[], s_args* args);
inline void usage(char * progname);

int main(int argc, char** argv) {
  s_args args;
  if(argc != 4) {
    usage(argv[0]);
  } else {
    parseArgs(argv, &args);
  }

  image img;
  image output;
	
  switch(args.compress) {
	case 0 :
		// decompression
		
		break;
	case 1 :
		// compression
		
		break;
	case 2 :
		// test dct
		
		break;
	case 3 :
		// test quantify
		
		break;
	case 4 :
		// test vectorize
		
		break;
	case 5 :
		// compute and print error
		
		break;
	default :
		usage(argv[0]);
		return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void parseArgs(char** argv, s_args* args) {
  args->compress = atoi(argv[1]);
  strncpy(args->inFilename, argv[2], 256);
  strncpy(args->outFilename, argv[3], 256);
}

inline void usage(char* progname) {
    printf("usage : %s mode in out\n", progname);
    printf("mode \t 0 : decompression, 1 : compression, 2 : save dct (pgm format),\n\t 3 : save quantize (pgm format), 4 : save vectorize (xxx format), 5 output compression loss\n");
    printf("in : input filename, pgm if compression, save dct or save quantize, xxx if decompression\n");
    printf("out : output filename, xxx if compression, pgm if decompression, save dct or save quantize\n");
}
