#pragma once

enum state {_free, _blocks, _mult, _busy};
class Block
{
	size_t location;
	//unsigned short size;
	state blockState = _free;
public:
	explicit Block(size_t location);
	~Block();

	bool isFree() const;

	void setState(state newState);

	state getState() const;

	size_t getLocation() const;
};

