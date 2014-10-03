#ifndef __COMPRESSOR
#define __COMPRESSOR
#include "image.h"
#include "block.h"

float* getNormalizeMatrix();
const float* getQuantumMatrix();

/* 
 * Apply the dct on an image
 * @param image Input image
 * @param image Output image
 * @param True if the image is normalize with 8.f, false otherwise
 * @param quantify Matrix contains all quantify values
 * */
void applyDct(image* input, image* output, bool normalize, const float* quantify);

/* 
 * Vectorize the image input
 * @param Input image
 * @param Output image
 * @param Matrix quantify
 * */
void vectorize(image* input, image* output, const float* quantify);

/* 
 * Replace 0 by utiles values in image
 * */
void utilsValues(image*);

/* 
 * Compress the image input and return an output image
 * */
void compress(image* input, image* output, const float* quantify);

/* 
 * Return the value of compression error
 * */
double getCompressionError(image* img);
#endif

