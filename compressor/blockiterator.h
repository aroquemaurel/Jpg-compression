#ifndef __BLOCK_ITERATOR
#define __BLOCK_ITERATOR
#include "image.h"

typedef struct BlockIterator_h {
	pixel_t* data;
	int pos;
	int width;
	int height;
} BlockIterator;

BlockIterator blockIterator_new(pixel_t* pdata, const int width, const int height);

pixel_t blockIterator_next(BlockIterator*);
pixel_t blockIterator_hasNext(BlockIterator);


#endif


