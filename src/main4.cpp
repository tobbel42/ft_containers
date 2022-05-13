#include "utils.hpp"
#include <iostream>
#include "rbTree.hpp"

#define PLN(txt) std::cout << txt << std::endl

int main() {
	ft::rbNode<ft::pair<int, int> > a;

	a.m_value = ft::make_pair(33, 111);

	const ft::pair<int, int> b(a.m_value);

	ft::rbNode<const ft::pair<int, int> > c(b);



	PLN(a.m_value);
	PLN(b);

	return 0;
};