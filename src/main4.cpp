#include "utils.hpp"
#include <iostream>
#include "map.hpp"
#include <map>
#include <ctime>

#define PLN(txt) std::cout << txt << std::endl

#define START  begin = std::clock()
	
#define STOP PLN("time: " <<static_cast<double>((std::clock() - begin)) /CLOCKS_PER_SEC << "s")



#define NSP std


int main() {


	clock_t begin = std::clock();	
	// std::cout << "How many Elements?" << std::endl;
	// int x; std::cin >> x;
	for(int x = 1; x <= 10000000; x *= 10)
	{
	PLN(x);
	START;
	PLN("OWN");
	ft::map<int, int> omap;
	for (int i = 0; i < x; ++i)
		omap.insert(ft::make_pair(i, i + 1));
	for (int i = 0; i < x; ++i)
		omap.find(i);
	for (int i = 0; i < x; ++i)	
		omap.erase(i);
	STOP;
	START;
	PLN("STD");
	std::map<int, int> smap;
	for (int i = 0; i < x; ++i)
		smap.insert(std::make_pair(i, i + 1));
	for (int i = 0; i < x; ++i)
		smap.find(i);
	for (int i = 0; i < x; ++i)	
		smap.erase(i);
	STOP;
	}

	return 0;
};