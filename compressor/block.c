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
	b.normalize = false;
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
void block_applyQuantify(Block* b, const float* quantum) {
	for(int i = 0 ; i < 8*8 ; ++i) {
		b->data[i] /= quantum[i];
	}
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

void setBlock(image* img, Block block, const int i, const int j) {
	for(int k = 0 ; k < 64 ; ++k) {
	block_applyQuantum(&block, k);
		img->data[(j+k/8) * img->w + (i+k%8)] = block.data[k];
	}
}


