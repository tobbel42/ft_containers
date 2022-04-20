#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>

#include <vector>
#include <iterator> 

#define NSP std
#define PLN(txt) std::cout << txt << std::endl;
int main()
{
	NSP::vector<int>	h(5, 7);
	NSP::vector<int> 	f(h.begin(), h.end());

	PLN(h.size());
	PLN(h.max_size());
	PLN(h.capacity());
	PLN(h.empty());
	h.resize(300, 0);
	
	PLN("h Cap: " << h.capacity());
	PLN("f Cap: " << f.capacity());

	for (NSP::vector<int>::iterator iter = h.begin(); iter != h.end(); ++iter)
	 	std::cout << *iter << std::endl;

	return 0;
}
