#ifndef __LINEARISATION
#define __LINEARISATION

#include <stdbool.h>
typedef enum {TOP, BOTTOM, RIGHT, LEFT, TOP_RIGHT, BOTTOM_LEFT, NONE} Direction;
typedef struct LinearizationIterator_t {
	char** data;
	int line;
	int column;
	int size;
	Direction lastDirection;
	
} LinearizationIterator;

LinearizationIterator iterator_new(char** pdata, const int size);

/* 
 * Return the next element  
 */
char iterator_next(LinearizationIterator* it);
bool iterator_hasNext(LinearizationIterator it);
bool iterator_hasPrevious(LinearizationIterator it);

#endif


