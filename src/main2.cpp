#include "utils.hpp"

#include "rbTree.hpp"
#include <iostream>

int main()
{
	int a = 5, b = 7;
	ft::less<int> f;
	std::cout << f(a, b) << std::endl;

	ft::rbTree<int, int> c;

	std::cout << "Here" << std::endl;



	std::cout << c.getRoot().base() << std::endl;
	for (int i = 0; i < 100000; ++i)
		c.insertValue(rand());

	//c.printTree();

	ft::rbTree<int, int>::iterator iter = c.begin();
	while(iter.base())
	{
		//std::cout << iter.base()->m_value << std::endl;
		iter.next();
	}
	return 0;
}