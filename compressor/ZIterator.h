#ifndef __LINEARISATION
#define __LINEARISATION

#include <stdbool.h>
typedef enum {TOP, BOTTOM, RIGHT, LEFT, TOP_RIGHT, BOTTOM_LEFT, NONE} Direction;
typedef struct ZIterator_t {
	float* data;
	int line;
	int column;
	int size;
	Direction lastDirection;
	
} ZIterator;

ZIterator iterator_new(float* pdata, const int size);

/* 
 * Return the next element  
 */
float iterator_next(ZIterator* it);
bool iterator_hasNext(ZIterator it);
bool iterator_hasPrevious(ZIterator it);
float iterator_value(ZIterator it);

#endif


