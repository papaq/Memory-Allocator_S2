#include "Block.h"


Block::Block(size_t location)
{
	this->location = location;
	//this->size = size;
}


Block::~Block()
{
}

bool Block::isFree() const
{
	return this->blockState == _free ? true : false;
}

void Block::setState(state newState)
{
	this->blockState = newState;
}

state Block::getState() const
{
	return this->blockState;
}

size_t Block::getLocation() const
{
	return size_t(this->location);
}
