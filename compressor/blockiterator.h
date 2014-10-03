#ifndef __BLOCK_ITERATOR
#define __BLOCK_ITERATOR
#include <stdlib.h>
#include "image.h"

typedef struct BlockIterator_h {
	pixel_t* data;
	int pos;
	int width;
	int height;
} BlockIterator;


/* 
 * Create a new block iterator
 */
BlockIterator blockIterator_new(pixel_t* pdata, const int width, const int height);

/**
 * Return the new pixel of the block
 */
pixel_t blockIterator_next(BlockIterator*);

/**
 * Return true if the block as a next pixel
 */
pixel_t blockIterator_hasNext(BlockIterator);

/**
 * Detele the block iterator and free memory
 */
void blockIterator_delete(BlockIterator* it); 


#endif


