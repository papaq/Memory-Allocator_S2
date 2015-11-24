#include <iostream>
#include <string>
#include <list>

#include "Memory.h"

using namespace std;

int main()
{
	auto Me = Memory(5);

	cout << "States:\n" << endl
		<< "0 free" << endl
		<< "1 blocks" << endl
		<< "2 multipage block 1st page" << endl
		<< "3 multipage block" << endl << endl;

	cout << Me.mem_dump() << endl;
	Me.mem_alloc(10);
	cout << Me.mem_dump() << endl;

	auto p1 = Me.mem_alloc(35);
	cout << Me.mem_dump() << endl;

	auto p2 = Me.mem_alloc(2555);
	cout << Me.mem_dump() << endl;

	Me.mem_alloc(13);
	cout << Me.mem_dump() << endl;

	Me.mem_free(p1);
	cout << Me.mem_dump() << endl;

	Me.mem_free(p2);
	cout << Me.mem_dump() << endl;

	Me.mem_alloc(9);
	cout << Me.mem_dump() << endl;

	/*Me.mem_realloc(p2, 15);
	cout << Me.mem_dump() << endl;
	Me.mem_realloc(p2, 13);
	cout << Me.mem_dump() << endl;
	Me.mem_realloc(p2, 11);
	cout << Me.mem_dump() << endl;
	Me.mem_realloc(p2, 18);
	cout << Me.mem_dump() << endl;*/
}
