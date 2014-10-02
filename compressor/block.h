#ifndef __BLOCK
#define __BLOCK

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "image.h"

typedef struct {
	float* data;
	float* quantum;
	bool normalize; 
} Block;

Block block_new();
void block_normalize(Block* b, float v);
void block_setQuantification(Block* b, const float* quantum);
void block_applyQuantify(Block* b, const float* quantum);
void block_setNormalize(Block* b, float v);
void block_applyQuantum(Block* b, int i);
void block_delete(Block* block);
void setBlock(image* img, Block block, const int i, const int j);

#endif


