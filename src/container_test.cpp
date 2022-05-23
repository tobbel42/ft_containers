#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <stack>

#define NSP ft
#define PLN(txt) std::cout << txt << std::endl
#define START  begin = std::clock()
#define STOP PLN("time: " <<static_cast<double>((std::clock() - begin)) /CLOCKS_PER_SEC << "s")

template <typename T, typename Alloc>
std::ostream &operator<< (std::ostream &s, const NSP::vector<T, Alloc>& vec){
	for (typename NSP::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
		s << "[" << vec[i] << "] ";
	return (s);
};

#define COUNT 100000000

int main() {
/*Vector----------------------------------------------------------------------*/
{
	clock_t begin;
	ft::vector<int> my_vec;

	START;
	for (int i = 0; i < COUNT; ++i) {
		my_vec.push_back(i);
	}
	for (int i = 0; i < COUNT; ++i) {
		int a = my_vec.at(i);
		a = a - 76;
	}
	for (int i = 0; i < COUNT; ++i) {
		my_vec.pop_back();
	}
	PLN("OWN");
	STOP;

	START;
	std::vector<int> sys_vec;
	for (int i = 0; i < COUNT; ++i) {
		sys_vec.push_back(i);
	}
	for (int i = 0; i < COUNT; ++i) {
		int a = sys_vec.at(i);
		a = a - 76;
	}
	for (int i = 0; i < COUNT; ++i) {
		sys_vec.pop_back();
	}
	PLN("SYS");
	STOP;


}

	system("leaks container_test"); 
};

