#include "Block.h"


Block::Block(size_t location, unsigned short size)
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

void Block::setFree()
{
	this->blockState = _free;
}

void Block::setBusy()
{
	this->blockState = _busy;
}

size_t Block::getLocation() const
{
	return size_t(this->location);
}
