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


/* 
 * Create a new block
 * */
Block block_new();

/* 
 *
 * Apply the normalize value of block b
 * */
void block_normalize(Block* b, float v);

/*
 * Set the quantum matrix to the block
 */
void block_setQuantification(Block* b, const float* quantum);

/*
 * Apply the quantify of quantum matrix in block b
 */
void block_applyQuantify(Block* b, const float* quantum);

/* *
 * Set the normalize value 
 */
void block_setNormalize(Block* b, float v);

/*
 * Apply the quantum matrix who is in block b
 */
void block_applyQuantum(Block* b, int i);

/*
 * Delete the block and free memory
 */
void block_delete(Block* block);

/* 
 * Set the block block in image img to (i,j) position
 */
void setBlock(image* img, Block block, const int i, const int j);

#endif


