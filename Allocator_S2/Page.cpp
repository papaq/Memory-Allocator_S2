#include "Page.h"



Page::Page(size_t location, unsigned short size)
{
	this->location = location;
	this->size = size;
}


Page::~Page()
{
}
