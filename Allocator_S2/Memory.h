#pragma once
#include <vector>
#include "Page.h"

using namespace std;

class Memory
{
	int memorySize;
	// Size of page in bytes
	unsigned short pageSize = 1024;
	unsigned short pages = 10;
	vector<Page> pagesVector;
	int *startPtr = nullptr;

	static unsigned short countBlockSize(unsigned int mem);
public:
	Memory();
	explicit Memory(unsigned short pages);
	~Memory();

	void * mem_alloc(size_t size);
	void * mem_realloc(void * addr, size_t size);
	void mem_free(void * addr);
	string mem_dump();
};

