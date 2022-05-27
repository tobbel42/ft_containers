
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <deque>

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

template <class T>
struct tmore : std::binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {return x>y;}
};

// template <typename T, typename Alloc>
// std::ostream &operator<< (std::ostream &s, const NSP::vector<T, Alloc>& vec){
// 	for (typename NSP::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
// 		s << "[" << vec[i] << "] ";
// 	return (s);
// };

//#define COUNT 100000000
template<class T>
void printVec(NSP::vector<T> a) {
	for (typename NSP::vector<T>::size_type i = 0; i < a.size(); ++i) {
		PLN(a[i]);
	}
}
template<class T, class U, class V, class W>
void printMap(NSP::map<T, U, V, W> m) {
	for (typename NSP::map<T, U, V, W>::iterator iter = m.begin();
		iter != m.end(); ++iter) {
			PLN("[" << iter->first << ", " << iter->second << "]");
		}
}

int main(int argc, char **argv) {

	clock_t	begin;

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
	//Modifiers
	printVec(thirdVec);
	thirdVec.assign(55, 55);
	printVec(thirdVec);
	thirdVec.assign(forthVec.begin(), --forthVec.end());
	printVec(thirdVec);
	thirdVec.assign(forthVec.rbegin(), forthVec.rend());
	printVec(thirdVec);
	for (size_t i = 0; i < 10000; ++i)
		thirdVec.push_back(i % 42);
	printVec(thirdVec);
	for (size_t i = 0; i < 10000; ++i)
		thirdVec.pop_back();
	printVec(thirdVec);
	thirdVec.insert(thirdVec.end(), 99);
	printVec(thirdVec);
	thirdVec.insert(--thirdVec.end(), 55);
	printVec(thirdVec);
	thirdVec.insert(++thirdVec.begin(), secondVec.begin(), secondVec.end());
	printVec(thirdVec);
	thirdVec.erase(thirdVec.begin());
	printVec(thirdVec);
	thirdVec.erase(thirdVec.begin(), thirdVec.begin() + thirdVec.size() - 9);
	printVec(thirdVec);
	thirdVec.clear();
	forthVec.swap(thirdVec);
	PLN((thirdVec.empty()?"Empty":"Not empty"));
	//allocator
	NSP::vector<int> dummyVec(5, 3, thirdVec.get_allocator());
	printVec(dummyVec);
	//relational Operators
	PLN(((firstVec == secondVec)?"yes":"no"));
	PLN(((thirdVec != forthVec)?"yes":"no"));
	PLN(((firstVec > forthVec)?"yes":"no"));
	PLN(((secondVec >= firstVec)?"yes":"no"));
	PLN(((thirdVec < forthVec)?"yes":"no"));
	PLN(((fifthVec <= sixthVec)?"yes":"no"));
	START;
	NSP::vector<int> speedVec;
	for (size_t i = 0; i < 100000000; ++i) {
		speedVec.push_back(i);
	}
	for (size_t i = 0; i < 100000000; ++i) {
		speedVec.pop_back();
	}
	STOP;

}

/*Map-------------------------------------------------------------------------*/
{
	//Constructor
	NSP::map<char, int> first;
	for(char i = 'a'; i < 'z'; ++i) {
		first[i] = i - 'a';
	}
	NSP::map<char, int> second(first);
	NSP::map<char, int, tmore<char> > third(++first.begin(), --first.end());
	printMap(first);
	printMap(second);
	printMap(third); 
	second = first;
	printMap(second);

	//Iterators
	NSP::map<char, int>::iterator iter = first.begin();
	PLN(iter->first);
	PLN((++iter)->first);
	for (NSP::map<char, int>::const_reverse_iterator riter = second.rbegin();
		riter != second.rend(); ++riter) {
			PLN(riter->first);
	}
	//Capacity
	PLN(first.size());
	first['?'] = 42;
	PLN(first.size());
	PLN((first.empty()?"empty":"not empty"));

	PLN(first.max_size());

	//Modifiers
	PLN(first.insert(NSP::make_pair('@', 99)).first->first);
	first.insert(first.begin(), NSP::make_pair('T', 67));
	NSP::vector<NSP::pair<char, int> > valVec;
	for (int i = 0; i < 10; ++i)
		valVec.push_back(NSP::make_pair('A' + i, 42 + i));
	first.insert(valVec.begin(), valVec.end());
	printMap(first);

	printMap(second);
	second.erase(++second.begin());
	printMap(second);
	PLN(second.erase('a'));
	second.erase(++second.begin(), --second.end());
	PLN((second.empty()?"empty":"not empty"));
	second.clear();
	PLN((second.empty()?"empty":"not empty"));

	//Observers
	NSP::map<char ,int>::key_compare a = second.key_comp();
	NSP::map<char,int>::value_compare b = second.value_comp(); 

	PLN((a('c', 'y')?"Yes":"No"));
	PLN((b(NSP::make_pair('b', 13), NSP::make_pair('c', 12))?"Yes":"No"));

	//Operations

	NSP::map<char, int>::iterator ifind = first.find('a');
	NSP::map<char, int>::const_iterator icfind = first.find('b');

	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	ifind = first.lower_bound('t');
	icfind = first.upper_bound('t');

	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	ifind = first.equal_range('t').first;
	icfind = first.equal_range('t').second;
	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	//allocator

	NSP::map<char, int>::allocator_type allo = first.get_allocator();
	PLN(allo.max_size()); 	
}

/*stack-----------------------------------------------------------------------*/
{
	
}

{
	if (argc > 0)
	{
		std::string leakscmd = "leaks ";
		leakscmd.append(argv[0] + 2);
		PLN(leakscmd);
		system(leakscmd.c_str()); 
	}
};

