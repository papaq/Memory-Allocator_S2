#include <iostream>
#include <string>
#include <list>

#include "Memory.h"

using namespace std;

int main()
{
	auto Me = Memory(7);

	cout << "States:\n" << endl
		<< "0 free" << endl
		<< "1 blocks" << endl
		<< "2 multipage block 1st page" << endl
		<< "3 multipage block" << endl << endl;

	cout << Me.mem_dump() << endl;

	/*
		Alloc memory section
	*/

	Me.mem_alloc(10);
	cout << Me.mem_dump() << endl;

	auto p1 = Me.mem_alloc(35);
	cout << Me.mem_dump() << endl;

	auto p2 = Me.mem_alloc(505);
	cout << Me.mem_dump() << endl;

	Me.mem_alloc(13);
	cout << Me.mem_dump() << endl;

	/*
		Free memory section
	*/

	Me.mem_free(p1);
	cout << Me.mem_dump() << endl;

	//Me.mem_free(p2);
	//cout << Me.mem_dump() << endl;
	
	/*
		Realloc memory section
	*/

	p2 = Me.mem_realloc(p2, 2225);
	cout << Me.mem_dump() << endl;

	p2 = Me.mem_realloc(p2, 8080);
	cout << Me.mem_dump() << endl;

	p2 = Me.mem_realloc(p2, 31);
	cout << Me.mem_dump() << endl;

	p2 = Me.mem_realloc(p2, 50);
	cout << Me.mem_dump() << endl;
}
