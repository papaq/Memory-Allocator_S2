#include "Page.h"


Page::Page(size_t location, unsigned short size)
{
	this->location = location;
	this->size = size;
}


Page::~Page()
{
}

void Page::setPageState(state newState)
{
	this->pageState = newState;
}

state Page::getPageState() const
{
	return this->pageState;
}

void Page::setBlockState(size_t location, state newState)
{
	for (auto block : this->blocksVector)
		if (block.getLocation() == location)
			block.setState(newState);
}

void Page::buildVectorOfBlocks()
{
	vector<Block> blocks;
	for (unsigned short i = 0; i < this->blocks; i++)
		blocks.push_back(Block(this->location + this->blockSize * i));
	this->blocksVector = blocks;
}

void Page::cutIntoBlocks(unsigned short blockSize)
{
	this->blockSize = blockSize;
	this->blocks = this->freeBlocks = this->size / blockSize;
	buildVectorOfBlocks();
	this->pageState = _blocks;
}

size_t Page::setFreeBlockBusy()
{
	for (auto block : this->blocksVector)
		if (block.isFree())
		{
			block.setState(_busy);
			return block.getLocation();
		}
	return 0;
}
