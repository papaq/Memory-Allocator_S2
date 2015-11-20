#include "Page.h"


Page::Page(size_t location, unsigned short size)
{
	this->location = location;
	this->size = size;
}


Page::~Page()
{
}

size_t Page::getLocation() const
{
	return this->location;
}

void Page::setPageState(state newState)
{
	this->pageState = newState;
}

state Page::getPageState() const
{
	return this->pageState;
}

bool Page::isFree() const
{
	return this->pageState == _free ? true : false;
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

void* Page::cutAndAlloc(unsigned short blockSize)
{
	this->cutIntoBlocks(blockSize);
	return this->allocateBlock();
}

bool Page::findPageForBlock(unsigned short size) const
{
	if (this->pageState == _blocks || this->blockSize == size || this->freeBlocks > 0)
		return true;
	return false;
}

void* Page::allocateBlock()
{
	for (auto block : this->blocksVector)
		if (block.isFree())
		{
			block.setState(_busy);
			this->freeBlocks--;
			return (void*)block.getLocation();
		}

	return nullptr;
}


