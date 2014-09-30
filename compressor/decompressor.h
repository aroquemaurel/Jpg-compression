#ifndef __DECOMPRESSOR
#define __DECOMPRESSOR
#include "image.h"
#include "ZIterator.h"

void obtainsSignificativesValues(image* in, image* out);
void invVectorize(image* in, image* out, float* quantify);
#endif


