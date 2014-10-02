#ifndef __LINEARISATION
#define __LINEARISATION

#include <stdbool.h>
#include "block.h"
typedef enum {TOP, BOTTOM, RIGHT, LEFT, TOP_RIGHT, BOTTOM_LEFT, NONE} Direction;
typedef struct ZIterator_t {
	float* data;
	int line;
	int column;
	int size;
	Direction lastDirection;
} ZIterator;

ZIterator zIterator_new(Block pdata, const int size);

/* 
 * Return the next element  
 */
float zIterator_next(ZIterator* it);
bool zIterator_hasNext(ZIterator it);
bool zIterator_hasPrevious(ZIterator it);
float zIterator_value(ZIterator it);
void zIterator_delete(ZIterator* it);

#endif


