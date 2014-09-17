#include "linearization.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char iterator_next(LinearizationIterator* it) {
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
	return it->data[it->line][it->column];
}

bool iterator_hasNext(LinearizationIterator it) {
	return !(it.column == it.size-1 && it.line == it.size-1);
}

bool iterator_hasPrevious(LinearizationIterator it) {
	return it.column != 0 && it.line != 0;
}

char iterator_value(LinearizationIterator it) {
	return it.data[it.line][it.column];
}

LinearizationIterator iterator_new(char** pdata, const int size) {
	LinearizationIterator iterator;
	iterator.data = (char**)malloc(sizeof(char*)*size);
	char** buff = iterator.data;
	for(int i = 0 ; i < size ; ++i) {
		buff[i] = (char*)(malloc(sizeof(char)*size));
	}

	for(int j = 0 ; j < size ; ++j) {
		memcpy(buff[j], pdata[j], size*sizeof(char));
	}
	iterator.line = 0;
	iterator.column = 0;
	iterator.size = size; 
	iterator.lastDirection = NONE;

	return iterator;
}



