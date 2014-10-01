#ifndef __COMPRESSOR
#define __COMPRESSOR
#include "image.h"
#include "block.h"

float* getNormalizeMatrix();
const float* getQuantumMatrix();

void applyDct(image* input, image* output, Block b, const float* quantify);
void vectorize(image* input, image* output, const float* quantify);
void utilsValues(image*);
void compress(image* input, image* output, const float* quantify);
double getCompressionError(image* img);
#endif

