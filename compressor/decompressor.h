#ifndef __DECOMPRESSOR
#define __DECOMPRESSOR
#include "image.h"
#include "ZIterator.h"

/* 
 * Add all 0 removing by compression 
 * */
void invUtilsValues(image* in, image* out);

/* 
 * Uncompress an image
 * */
void uncompress(image* in, image* out, const float* quantify);
#endif


