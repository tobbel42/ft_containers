#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>

#include <vector>
#include <iterator> 

#define NSP ft
#define PLN(txt) std::cout << txt << std::endl;
int main()
{
	NSP::vector<int>	h(1, 7);
	NSP::vector<int>	g(h);
	

	NSP::vector<int> 	f(h.begin(), h.end());


	// PLN(h.size());
	// PLN(h.max_size());
	// PLN(h.capacity());
	// PLN(h.empty());
	
	// PLN("h Cap: " << h.capacity());
	// PLN("f Cap: " << f.capacity());

	// PLN(h[400]);

	// h.reserve(300);
	// PLN(h.capacity());

	PLN(g.size() << " " << g.capacity());
	g.resize(6);
	PLN(g.size() << " " << g.capacity());
	for (int i = 0; i < 5; ++i)
		g[i] = i;

	//g = f;

	PLN(g[4]);
	PLN(g.front());
	PLN(g.back());
	PLN(g.at(4));

	NSP::vector<int> j(9, 7);

	g.assign(j.begin(), j.end());
	g.clear();
	for (int i = 0; i < 11; ++i)
	{
		g.push_back(i);
	}
	g.insert(g.begin(), 444);
	g.insert(g.end(), 2, 666);
	NSP::vector<int> t(4, 999);
	g.insert(g.begin(), t.begin(), t.end());
	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
		std::cout << *iter << std::endl;
	
	for (NSP::vector<int>::reverse_iterator iter = g.rbegin(); iter != g.rend(); ++iter)
		std::cout << *iter << std::endl;

	g.clear();
	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
		std::cout << *iter << std::endl;

	return 0;
}
