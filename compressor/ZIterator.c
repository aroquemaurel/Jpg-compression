#include "ZIterator.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float iterator_next(ZIterator* it) {
	assert(iterator_hasNext(*it));
	if(it->line == 0 && it->column % 2 == 0) {
		++it->column;
		it->lastDirection = RIGHT;
	} else if(it->line == 0 && it->column % 2 != 0) {
		++it->line;
		--it->column;
		it->lastDirection = BOTTOM_LEFT;
	} else if(it->column == 0 && it->line % 2 == 0) {
		--it->line;
		++it->column;
		it->lastDirection = TOP_RIGHT;
	} else if(it->line == it->size-1 && it->column % 2 == 0) {
		++it->column;
		it->lastDirection = RIGHT;
	} else if(it->line == it->size-1 && it->column %2 != 0) {
		--it->line;
		++it->column;
		it->lastDirection = TOP_RIGHT;
	} else if(it->column == it->size-1 && it->line%2 !=0) {
		++it->line;
		it->lastDirection = BOTTOM;
	} else if(it->column == it->size-1 && it->line%2 == 0) {
		++it->line;
		--it->column;
		it->lastDirection = BOTTOM_LEFT;
	} else if(it->column == 0 && it->line %2 != 0) {
		++it->line;
		it->lastDirection = BOTTOM;
	} else if(it->lastDirection == TOP_RIGHT) {
		--it->line;
		++it->column;
	} else if(it->lastDirection == BOTTOM_LEFT) {
		++it->line;
		--it->column;
	} else {
		printf("DEFAULT");
	}

	return it->data[it->line*it->size+it->column];
}

bool iterator_hasNext(ZIterator it) {
	return !(it.column == it.size-1 && it.line == it.size-1);
}

bool iterator_hasPrevious(ZIterator it) {
	return it.column != 0 && it.line != 0;
}

float iterator_value(ZIterator it) {
	return it.data[it.line*it.size+it.column];
}

ZIterator iterator_new(float* pdata, const int size) {
	ZIterator iterator;
	iterator.data = (float*)malloc(sizeof(float)*size*size);

	for(int i = 0 ; i < size*size; ++i) {
		iterator.data[i] = pdata[i];	
	}

	iterator.line = 0;
	iterator.column = 0;
	iterator.size = size;
	iterator.lastDirection = NONE;

	return iterator;
}



