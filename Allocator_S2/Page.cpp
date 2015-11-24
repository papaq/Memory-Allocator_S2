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

unsigned short Page::getBlockSize() const
{
	return this->blockSize;
}

unsigned short Page::getBlocks() const
{
	return this->blocks;
}

void Page::setBlocks(unsigned short blocks)
{
	this->blocks = blocks;
}

unsigned short Page::getFreeBlocks() const
{
	return this->freeBlocks;
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

//void Page::setBlockState(size_t location, state newState)
//{
//	for (auto block = this->blocksVector.begin();
//	block < this->blocksVector.end(); ++block)
//		if (block->getLocation() == location)
//			block->setState(newState);
//}

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

void Page::setBlockFree(size_t location)
{
	for (auto blockIterator = this->blocksVector.begin();
	blockIterator < this->blocksVector.end(); ++blockIterator)
		if (location == blockIterator->getLocation())
			if (_busy == blockIterator->getState())
			{
				blockIterator->setState(_free);
				this->freeBlocks++;
				if (this->freeBlocks == this->blocks)
				{
					this->pageState = _free;
					this->blocksVector.clear();
				}
				break;
			}
}

bool Page::findPageForBlock(unsigned short size) const
{
	if (this->pageState == _blocks && this->blockSize == size && this->freeBlocks > 0)
		return true;
	return false;
}

void* Page::allocateBlock()
{
	for (auto block = this->blocksVector.begin();
	block < this->blocksVector.end(); ++block)
		if (block->isFree())
		{
			block->setState(_busy);
			this->freeBlocks--;
			return (void*)block->getLocation();
		}

	return nullptr;
}


