#ifndef __LINEARISATION
#define __LINEARISATION

#include <stdbool.h>
typedef enum {TOP, BOTTOM, RIGHT, LEFT, TOP_RIGHT, BOTTOM_LEFT, NONE} Direction;
typedef struct LinearizationIterator_t {
	float** data;
	int line;
	int column;
	int width;
	int height;
	Direction lastDirection;
	
} LinearizationIterator;

LinearizationIterator iterator_new(float** pdata, const int nbBlocs);

/* 
 * Return the next element  
 */
float iterator_next(LinearizationIterator* it);
bool iterator_hasNext(LinearizationIterator it);
bool iterator_hasPrevious(LinearizationIterator it);
float iterator_value(LinearizationIterator it);

#endif


