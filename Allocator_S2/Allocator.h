#pragma once
#include "Page.h"

class Allocator
{
	vector<Page> pages = vector<Page>();
public:
	Allocator();
	~Allocator();
	
	void * mem_alloc(size_t size);
	void * mem_realloc(void * addr, size_t size);
	void mem_free(void * addr);
};

