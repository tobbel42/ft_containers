#include "map.hpp"
#include <iostream>

int main()
{
{
	ft::map<int, int> a;

	ft::map<int, int>::iterator iter = a.begin();
	std::cout << iter.base() << std::endl;

	ft::pair<int, int> b;
	b.first = 33;
	b.second = 42;

	a.insert(b);
	a.insert(ft::pair<int, int>(99, 88));
	a.insert(ft::make_pair<int, int>(77, 124));

	for (int i = 0; i < 10000; ++i)
		a.insert(ft::pair<int, int>(rand()%1000, rand()%1000));

	a.printTree();

	std::cout << "DONE" << std::endl;
}
	system("leaks container_test");

	return 0;
}