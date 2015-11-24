#pragma once
#include "Memory.h"
#include "string"

unsigned short Memory::countBlockSize(unsigned int mem)
{
	if (mem <= 4)
		return 4;
	unsigned short blockSize = 8;
	while (blockSize < mem)
		blockSize *= 2;
	return blockSize;
}

bool Memory::checkPagesFree(vector<Page>::iterator pagesIterator, unsigned short pagesToAlloc)
{
	unsigned short pageNumber = 2;

	// Check other pages whether they are free
	for (auto nextPageIterator = pagesIterator;
	nextPageIterator != this->pagesVector.end(); ++nextPageIterator)
	{
		if (nextPageIterator->isFree())
		{
			if (pageNumber++ == pagesToAlloc)
				return true;
			continue;
		}
		break;
	}
	return false;
}

void Memory::setPagesMult(vector<Page>::iterator pagesIterator, unsigned short pagesToAlloc)
{
	unsigned short pageNumber = 1;

	// Set first page _mult
	pagesIterator->setPageState(_mult);

	// Set other pages _busy
	for (auto nextPageIterator = ++pagesIterator;
	nextPageIterator != this->pagesVector.end()
		&& pageNumber < pagesToAlloc++; ++nextPageIterator)
		nextPageIterator->setPageState(_busy);
}

void Memory::freeBlockOfPages(vector<Page>::iterator pagesIterator)
{
	pagesIterator->setPageState(_free);
	for (auto page = ++pagesIterator;
	this->pagesVector.end() > page; ++page)
		if (_busy == page->getPageState())
			page->setPageState(_free);
		else
			break;
}

Memory::Memory()
{
	// Size of memory, we allocate for this project
	this->memorySize = this->pageSize * this->pages;

	// Allocate fourth part of memorySize, because sizeof(int) = 4
	this->startPtr = new int[this->memorySize / 4];
	for (unsigned short i = 0; i < this->pages; i++)
	{
		// Add all pages into pagesVector
		this->pagesVector.push_back(Page(size_t(this->startPtr) + this->pageSize * i, this->pageSize));
	}
}

Memory::Memory(unsigned short pages)
{
	// Set number of pages
	this->pages = pages;

	// Size of memory, we allocate for this project
	this->memorySize = this->pageSize * this->pages;

	// Allocate fourth part of memorySize, because sizeof(int) = 4
	this->startPtr = new int[this->memorySize / 4];
	for (unsigned short i = 0; i < this->pages; i++)
	{
		// Add all pages into pagesVector
		this->pagesVector.push_back(Page(size_t(this->startPtr) + this->pageSize * i, this->pageSize));
	}
}

Memory::~Memory()
{
	delete[] this->startPtr;
}

void* Memory::mem_alloc(size_t size)
{
	if (size > this->memorySize || size < 1)
		return nullptr;
	auto blockSize = this->countBlockSize(size);

	// Alloc a block with size less then a page
	if (blockSize < this->pageSize)
	{

		// Find a page with same block size and a free block
		for (auto page = this->pagesVector.begin();
		page < this->pagesVector.end(); ++page)

			if (page->findPageForBlock(blockSize))

				// get pointer to this block 
				return page->allocateBlock();

		// No page with the same size free block

		// Find a free page
		for (auto page = this->pagesVector.begin();
		page < this->pagesVector.end(); ++page)
			if (page->isFree())

				// Cut page and get ptr to the first block
				return page->cutAndAlloc(blockSize);

		// No free page

		// Find an existing block size, smaller then page
		// and compatible with needed size
		for (auto i = blockSize; i <= this->pageSize; )
		{
			// Find a page with new block size and a free block
			for (auto page = this->pagesVector.begin();
			page < this->pagesVector.end(); ++page)

				if (page->findPageForBlock(blockSize))

					// get pointer to this block 
					return page->allocateBlock();
			i *= 2;
		}
	}

	// Alloc a block with size of page or several
	else
	{
		unsigned short pagesInBlock = blockSize / this->pageSize;

		// There are more pages in mem, then we need
		if (this->pages > pagesInBlock)
		{
			for (auto pageIterator = this->pagesVector.begin();
			pageIterator != this->pagesVector.end(); ++pageIterator)

				// First page is free && other 
				if (pageIterator->getPageState() == _free && checkPagesFree(pageIterator, pagesInBlock))
				{
					this->setPagesMult(pageIterator, pagesInBlock);
					return (void*)pageIterator->getLocation();
				}
		}
	}

	// No opportunity to find a compatible block
	return nullptr;
}

void* Memory::mem_realloc(void* addr, size_t size)
{
	return nullptr;
}

void Memory::mem_free(void* addr)
{
	auto location = size_t(addr);
	auto relative_loc = location - size_t(this->startPtr);
	if (0 <= relative_loc && this->memorySize >= relative_loc + 4)
		for (auto pageIterator = this->pagesVector.begin();
		     this->pagesVector.end() > pageIterator; ++pageIterator)
		{
			auto thisPageLocation = pageIterator->getLocation();

			// Multiple-page block
			if (thisPageLocation == location &&
				_mult == pageIterator->getPageState())
			{
				this->freeBlockOfPages(pageIterator);
				break;
			}

			// Page of blocks
			if (thisPageLocation == location - ((location - size_t(this->startPtr)) % this->pageSize) &&
				_blocks == pageIterator->getPageState())
			{
				pageIterator->setBlockFree(location);
				break;
			}
		}
}

string Memory::mem_dump()
{
	string outString;
	outString = "N  State  Blocks  Free\n";
	unsigned short i = 0;
	for (auto page : this->pagesVector)
	{
		outString += std::to_string(i) + "   " + std::to_string(page.getPageState()) + "      " +
			std::to_string(page.getBlocks()) + "       " +
			std::to_string(page.getFreeBlocks()) + "\n";
		++i;
	}
	return outString;
}
