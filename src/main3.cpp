#include "map.hpp"
#include <iostream>

int main()
{
{
	ft::map<int, int> a;


	ft::pair<int, int> b;
	b.first = 33;
	b.second = 42;

	a.insert(b);
	a.insert(ft::pair<int, int>(99, 88));
	a.insert(ft::make_pair<int, int>(77, 124));

	for (int i = 0; i < 10; ++i)
		a.insert(ft::pair<int, int>(i, i + 1));

	ft::map<int, int>::iterator iter = a.begin();
	std::cout << *iter << std::endl;
	a.printTree();

	//int x; std::cin >> x;
	a.erase(6);
	a.printTree();

	iter = a.findValue(7);

	std::cout << *iter << std::endl;


	std::cout << "DONE" << std::endl;
}
	system("leaks container_test");

	return 0;
}