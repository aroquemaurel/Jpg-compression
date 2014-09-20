#include "linearization.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float iterator_next(LinearizationIterator* it) {
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
	} else if(it->line == it->height-1 && it->column % 2 == 0) {
		++it->column;
		it->lastDirection = RIGHT;
	} else if(it->line == it->height-1 && it->column %2 != 0) {
		--it->line;
		++it->column;
		it->lastDirection = TOP_RIGHT;
	} else if(it->column == it->width-1 && it->line%2 !=0) {
		++it->line;
		it->lastDirection = BOTTOM;
	} else if(it->column == it->width-1 && it->line%2 == 0) {
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
	return !(it.column == it.width-1 && it.line == it.height-1);
}

bool iterator_hasPrevious(LinearizationIterator it) {
	return it.column != 0 && it.line != 0;
}

float iterator_value(LinearizationIterator it) {
	return it.data[it.line][it.column];
}

LinearizationIterator iterator_new(float** pdata, const int nbBlocs) {
	LinearizationIterator iterator;
	iterator.data = (float**)malloc(sizeof(float*)*nbBlocs);
	for(int i = 0 ; i <  nbBlocs ; ++i) {
		iterator.data[i] = (float*) malloc(sizeof(float)*8);
	}
	float** buff = iterator.data;

	for(int i = 0 ; i < nbBlocs; ++i) {
		for(int j = 0 ; j < nbBlocs ; ++j) {
			buff[i][j] = pdata[i][j];	
		}
	}

	iterator.line = 0;
	iterator.column = 0;
	iterator.width = nbBlocs;
	iterator.height = nbBlocs; 
	iterator.lastDirection = NONE;

	return iterator;
}



