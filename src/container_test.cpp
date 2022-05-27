
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <stack>

#ifdef FT
#define NSP ft
#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#else
#define NSP std
#endif
#define PLN(txt) std::cout << txt << std::endl
#define START  begin = std::clock()
#define STOP PLN("time: " <<static_cast<double>((std::clock() - begin)) /CLOCKS_PER_SEC << "s")

// template <typename T, typename Alloc>
// std::ostream &operator<< (std::ostream &s, const NSP::vector<T, Alloc>& vec){
// 	for (typename NSP::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
// 		s << "[" << vec[i] << "] ";
// 	return (s);
// };

//#define COUNT 100000000
template<class T>
void printVec(NSP::vector<T> a) {
	for (size_t i = 0; i < a.size(); ++i) {
		PLN(a[i]);
	}
}

int main(int argc, char **argv) {
/*Vector----------------------------------------------------------------------*/
{
	//Constructors + assignment
	NSP::vector<int> firstVec;
	NSP::vector<int> secondVec(9, 42);
	printVec(firstVec);
	printVec(secondVec);
	firstVec = secondVec;
	printVec(firstVec);
	NSP::vector<int> thirdVec;
	for (int i = 1; i < 1000; i *= 2)
		thirdVec.push_back(i);
	printVec(thirdVec);	
	NSP::vector<int> forthVec(thirdVec.begin(), thirdVec.end());
	printVec(forthVec);
	NSP::vector<std::string> fifthVec(42, "LOL");
	NSP::vector<std::string> sixthVec(fifthVec);
	printVec(fifthVec);
	printVec(sixthVec);
	//iterators
	for (NSP::vector<int>::iterator iter = secondVec.begin();
		iter != secondVec.end(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::reverse_iterator iter = secondVec.rbegin();
		iter != secondVec.rend(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::const_iterator iter = secondVec.begin();
		iter != secondVec.end(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::const_reverse_iterator iter = secondVec.rbegin();
		iter != secondVec.rend(); ++iter)
		PLN(*iter);
	//Capacity
	PLN(fifthVec.size());
	fifthVec.pop_back();
	PLN(fifthVec.size());
	PLN(fifthVec.max_size());
	fifthVec.resize(300, "Hello");
	printVec(fifthVec);
	fifthVec.resize(10);
	PLN(fifthVec.capacity());
	printVec(fifthVec);
	PLN(fifthVec.capacity());
	fifthVec.reserve(5000);
	PLN(fifthVec.capacity());
	fifthVec.reserve(325);
	PLN(fifthVec.capacity());
	PLN((fifthVec.empty()?"Empty":"Not empty"));
	//access
	PLN(firstVec[1]);
	PLN(firstVec[2]);
	try{
		PLN(firstVec.at(300));
	}
	catch (std::exception & e)
	{
		PLN("Exception: " << e.what());
	}
	PLN(firstVec.front() << " " << firstVec.back());
	firstVec.push_back(99);
	PLN(firstVec.front() << " " << firstVec.back());
	
}
	if (argc > 0)
	{
		std::string leakscmd = "leaks ";
		leakscmd.append(argv[0] + 2);
		PLN(leakscmd);
		system(leakscmd.c_str()); 
	}
};

