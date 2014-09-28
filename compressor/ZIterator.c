#include "ZIterator.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float zIterator_next(ZIterator* it) {
	assert(zIterator_hasNext(*it));
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

bool zIterator_hasNext(ZIterator it) {
	return !(it.column == it.size-1 && it.line == it.size-1);
}

bool zIterator_hasPrevious(ZIterator it) {
	return it.column != 0 && it.line != 0;
}

float zIterator_value(ZIterator it) {
	return it.data[it.line*it.size+it.column];
}

ZIterator zIterator_new(float* pdata, const int size) {
	ZIterator zIterator;
	zIterator.data = (float*)malloc(sizeof(float)*size*size);

	for(int i = 0 ; i < size*size; ++i) {
		zIterator.data[i] = pdata[i];	
	}

	zIterator.line = 0;
	zIterator.column = 0;
	zIterator.size = size;
	zIterator.lastDirection = NONE;

	return zIterator;
}



