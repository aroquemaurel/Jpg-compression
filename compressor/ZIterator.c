#include "ZIterator.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


float zIterator_next(ZIterator* it) {
	assert(zIterator_hasNext(*it));

	if(it->line == 0) {
		if(it->column % 2 == 0) {
			++it->column;
			it->lastDirection = RIGHT;
		} else {
			++it->line;
			--it->column;
			it->lastDirection = BOTTOM_LEFT;
		}
	} else if(it->column == 0 && it->line % 2 == 0) {
		--it->line;
		++it->column;
		it->lastDirection = TOP_RIGHT;
	} else if(it->line == it->size-1) {
		if(it->column % 2 == 0) {
			it->lastDirection = RIGHT;
		} else {
			--it->line;
			it->lastDirection = TOP_RIGHT;
		}
		++it->column;
	} else if(it->column == it->size-1) {
		if(it->line%2 != 0) {
			it->lastDirection = BOTTOM;
		} else {
			--it->column;
			it->lastDirection = BOTTOM_LEFT;
		}
		++it->line;
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
		printf("DEFAULT\n"); // We mustn't go here !
	}

	return it->data[it->line*it->size+it->column];
}

bool zIterator_hasNext(ZIterator it) {
	return !(it.column == it.size-1 && it.line == it.size-1); // Not the end of block
}

bool zIterator_hasPrevious(ZIterator it) {
	return it.column != 0 && it.line != 0; //Not the beginning of block
}

float zIterator_value(ZIterator it) {
	return it.data[it.line*it.size+it.column]; // Value of current case
}

ZIterator zIterator_new(Block block, const int size) {
	ZIterator zIterator;
	zIterator.data = (float*)malloc(sizeof(float)*size*size);

	for(int i = 0 ; i < size*size; ++i) {
		zIterator.data[i] = block.data[i];	
	}

	zIterator.line = 0;
	zIterator.column = 0;
	zIterator.size = size;
	zIterator.lastDirection = NONE;

	return zIterator;
}

void zIterator_delete(ZIterator* it) {
	it->column = 0;
	it->line = 0;
	it->size = 0;
	free(it->data);
}

