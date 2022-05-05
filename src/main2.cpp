#include "utils.hpp"

#include "rbTree.hpp"
#include <iostream>

int main()
{
	// int a = 5, b = 7;
	// ft::less<int> f;
	// std::cout << f(a, b) << std::endl;

	// ft::rbTree<int, int> c;

	// std::cout << "Here" << std::endl;



	// std::cout << c.getRoot().base() << std::endl;
	
	// for (int i = 0; i < 100000; ++i)
	// 	c.insertValue(rand()%1000000);

	// c.printTree();
	// c.clearTree();
	// std::cout << "EMPTY_TREE" << std::endl;
	// c.printTree();

	// ft::rbTree<int, int>::iterator iter = c.begin();
	// std::cout << iter.base() << std::endl;

	ft::pair<int, double> a;
	a.first = 22;
	a.second = 35;
	ft::pair<int, double> b(15, 4.333);
	ft::pair<int, double> c(b);

	std::cout << a.first << " " << a.second << std::endl;
	std::cout << b.first << " " << b.second << std::endl;
	std::cout << c.first << " " << c.second << std::endl;

	c.first = 981246;
	b = ft::make_pair(1, 23523.235);
	std::cout << b.first << " " << b.second << " " << (c > b) <<  std::endl;

	std::string u = "Hello World";
	std::string v = "Hello World1";

	std::cout << ft::lexicographical_compare(u.begin(), u.end(), v.begin(), v.end(), ft::less<char>()) << std::endl;

	return 0;
}