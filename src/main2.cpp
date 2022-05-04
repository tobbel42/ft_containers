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
	
	for (int i = 0; i < 10; ++i)
		c.insertValue(rand()%100);

	c.printTree();

	int x;
	std::cin >> x;

	c.deleteValue(x);
	c.printTree();

	ft::rbTree<int, int>::iterator iter = c.begin();

	std::cout << iter.base()->m_value << std::endl;
	iter.next();
	std::cout << iter.base()->m_value << std::endl;
	iter.next();
	std::cout << iter.base()->m_value << std::endl;
	iter.prev();
	std::cout << iter.base()->m_value << std::endl;
	return 0;
}