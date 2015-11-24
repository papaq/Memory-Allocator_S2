#pragma once
#include "Block.h"
#include <vector>


using namespace std;

class Page
{
	size_t location;
	unsigned short int size;
	state pageState = _free;
	unsigned short blocks = 0;
	unsigned short blockSize = 0;
	unsigned short freeBlocks = 0;
	vector<Block> blocksVector = vector<Block>();

	void buildVectorOfBlocks();

	void cutIntoBlocks(unsigned short blockSize);

public:
	explicit Page(size_t location, unsigned short size);
	~Page();

	size_t getLocation() const;

	unsigned short getBlockSize() const;

	unsigned short getBlocks() const;

	void setBlocks(unsigned short blocks);

	unsigned short getFreeBlocks() const;

	void setPageState(state newState);

	state getPageState() const;

	bool isFree() const;

	// void setBlockState(size_t location, state newState);

	bool findPageForBlock(unsigned short size) const;

	void* allocateBlock();

	void* cutAndAlloc(unsigned short blockSize);

	void setBlockFree(size_t location);
};

