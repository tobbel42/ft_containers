#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>

#include <vector>
#include <iterator> 

int main()
{
	ft::vector<int>	h(5, 7);
	//std::vector<char>	j(5, 0);

	// if (h.begin() >= j.begin())
	// 	std::cout << "works" << std::endl;

	for (ft::vector<int>::iterator iter = h.begin(); !(iter == h.end()); ++iter)
		std::cout << iter << std::endl;

	return 0;
}
