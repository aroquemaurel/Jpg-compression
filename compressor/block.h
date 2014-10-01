#ifndef __BLOCK
#define __BLOCK

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct {
	float* data;
	float* quantum;
	bool normalize; 
} Block;

Block block_new();
void block_normalize(Block* b, float v);
void block_setQuantification(Block* b, const float* quantum);
void block_setNormalize(Block* b, float v);
void block_applyQuantum(Block* b, int i);
void block_delete(Block* block);

#endif


