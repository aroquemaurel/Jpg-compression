#include "blockiterator.h"

BlockIterator blockIterator_new(pixel_t* pdata, const int width, const int height) {
	BlockIterator iterator;
	iterator.pos = 63;
	iterator.width = width;
	iterator.height = height;
	iterator.data = malloc(sizeof(pixel_t) * width * height);
	for (int i = 0 ; i < height*width; ++i) {
		iterator.data[i] = pdata[i];	
	}

	return iterator;
}

pixel_t blockIterator_next(BlockIterator* it) {
	it->pos += 64;

	return it->data[it->pos];
}
pixel_t blockIterator_hasNext(BlockIterator it) {
	return (it.pos < it.width*it.height);
}
