#pragma once
#include <vector>
#include "Page.h"

using namespace std;

class Memory
{
	unsigned int memorySize;
	// Size of page in bytes
	unsigned short pageSize = 1024;
	unsigned short pages = 10;
	vector<Page> pagesVector;
	int *startPtr = nullptr;

	unsigned short countBlockSize(unsigned int mem) const;

	bool checkPagesFree(vector<Page>::iterator pagesIterator, unsigned short pagesToAlloc);

	void setPagesMult(vector<Page>::iterator* pagesIterator, unsigned short pagesToAlloc);

	void freeBlockOfPages(vector<Page>::iterator pagesIterator);

	void* reallocBlockOfPages(vector<Page>::iterator pagesIterator, size_t size);

	void* reallocPageBlock(void * addr, vector<Page>::iterator pagesIteratorrator, size_t size);

public:
	Memory();

	explicit Memory(unsigned short pages);

	~Memory();

	void * mem_alloc(size_t size);

	void * mem_realloc(void * addr, size_t size);

	void mem_free(void * addr);

	string mem_dump();
};

