#include "block.h"

void applyQuantum(Block* b, int i) {
	if(b->normalize) {
		b->data[i] = (b->data[i]/b->quantum[i]);
	} else {
		b->data[i] = round(b->data[i]/b->quantum[i]);
	}
}

Block block_new() {
	Block b;
	b.data = (float*)malloc(8*8*sizeof(float));
	b.quantum = (float*)malloc(8*8*sizeof(float));
	return b;
}

void block_setNormalize(Block* b, float v) {
	for(int i = 0 ; i < 8*8 ; ++i) {
		b->quantum[i] = v;
	}
	b->normalize = true;
}

void block_setQuantification(Block* b, const float* quantum) {
	for(int i = 0 ; i < 8*8 ; ++i) {
		b->quantum[i] = quantum[i];
	}
	b->normalize = false;
}

void block_applyQuantum(Block* b, int i) {
	b->data[i] /= b->quantum[i]; 
	if(!b->normalize) {
		b->data[i] = round(b->data[i]); 
	} 
}

void block_delete(Block* block) {
	block->normalize = false;
	free(block->quantum);
	free(block->data);
}
