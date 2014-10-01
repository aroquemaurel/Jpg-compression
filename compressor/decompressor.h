#ifndef __DECOMPRESSOR
#define __DECOMPRESSOR
#include "image.h"
#include "ZIterator.h"

void invUtilsValues(image* in, image* out);
void uncompress(image* in, image* out, const float* quantify);
#endif


