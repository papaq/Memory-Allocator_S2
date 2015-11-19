#pragma once
#include "Block.h"
#include <vector>

enum state {_free, blocks, mult};

using namespace std;
class Page
{
	size_t location;
	unsigned short int size;
	state type = _free;
	unsigned short blockSize = 0;
	vector<Block> freeBlocks = vector<Block>();
	vector<Block> busyBlocks = vector<Block>();
public:
	Page(size_t location, unsigned short size);
	~Page();
};

