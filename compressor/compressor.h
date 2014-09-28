#ifndef __COMPRESSOR
#define __COMPRESSOR
#include "image.h"
#include "block.h"
#include "blockiterator.h"
#include "ZIterator.h"
void applyDct(image* input, image* output, Block b, float* quantify);
void vectorize(image* input, image* output, const float* quantify);
void utilsValues(image*);
#endif

