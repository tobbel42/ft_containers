#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>

#include <vector>
#include <iterator> 

#define NSP std
#define PLN(txt) std::cout << txt << std::endl;

template <typename T, typename Alloc>
std::ostream &operator<< (std::ostream &s, const NSP::vector<T, Alloc>& vec){
	for (typename NSP::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
		s << "[" << vec[i] << "] ";
	return (s);
};

int main()
// {
// 	NSP::vector<int>	h(1, 7);
// 	NSP::vector<int>	g(h);
// 	NSP::vector<int> 	f(h.begin(), h.end());

// 	PLN(h.size());
// 	PLN(h.max_size());
// 	PLN(h.capacity());
// 	PLN(h.empty());
	
// 	PLN("h Cap: " << h.capacity());
// 	PLN("f Cap: " << f.capacity());

// 	PLN(h[400]);

// 	h.reserve(300);
// 	PLN(h.capacity());

// 	PLN(g.size() << " " << g.capacity());
// 	g.resize(6);
// 	PLN(g.size() << " " << g.capacity());
// 	for (int i = 0; i < 5; ++i)
// 		g[i] = i;

// 	// //g = f;

// 	PLN(g[4]);
// 	PLN(g.front());
// 	PLN(g.back());
// 	PLN(g.at(4));

// 	NSP::vector<int> j(9, 7);

// 	g.assign(j.begin(), j.end());
// 	g.clear();
// 	for (int i = 0; i < 11; ++i)
// 	{
// 		g.push_back(i);
// 	}
// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 		std::cout << *iter << std::endl;
// 	g.insert(g.begin(), 444);
// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 		std::cout << *iter << std::endl;
// 	PLN("i back");
// 	g.insert(g.end(), 2, 666);
// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 		std::cout << *iter << std::endl;

// 	NSP::vector<int> t(4, 999);
// 		PLN("i front");

// 	g.insert(g.begin(), t.begin(), t.end());
// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 		std::cout << *iter << std::endl;
// 		PLN("erase front");

// 	g.erase(g.begin(), g.begin() + 4);

// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 	std::cout << *iter << std::endl;


// 	PLN(g.capacity() << " " << g.size());
// 	g.swap(h);
// 	PLN(g.capacity() << " " << g.size());
// 	NSP::swap(h, g);
// 	PLN(g.capacity() << " " << g.size());

// 	PLN(((g==h)?"yes":"no"));
// 	PLN(((f==h)?"yes":"no"));

// 	for (NSP::vector<int>::iterator iter = g.begin(); iter != g.end(); ++iter)
// 		std::cout << *iter << std::endl;

// 	NSP::vector<int> foo (3,100);   // three ints with a value of 100
// 	NSP::vector<int> bar (2,200);   // two ints with a value of 200	
// 	if (foo==bar) std::cout << "foo and bar are equal\n";
// 	if (foo!=bar) std::cout << "foo and bar are not equal\n";
// 	if (foo< bar) std::cout << "foo is less than bar\n";
// 	if (foo> bar) std::cout << "foo is greater than bar\n";
// 	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
// 	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

// 	return 0;
// }

	{
	// Basic functionality
		NSP::vector<int, std::allocator<int> > vectorTest;
		// non-iterator assign
			vectorTest.assign(5, 20);
			PLN("5 * 20: " << vectorTest);
		// get allocator test
			NSP::vector<int>::allocator_type vectorAllocator = vectorTest.get_allocator();
			int *intPointer = vectorAllocator.allocate(1);
			vectorAllocator.construct(intPointer, 5);
			PLN("allocated 1 int with value of 5: " << *intPointer);
			vectorAllocator.destroy(intPointer);
			vectorAllocator.deallocate(intPointer, 1);
		// copy construct
			NSP::vector<int> vectorTest2(vectorTest);
			PLN("After copy construct, vectorTest2: " << vectorTest2);
		// at
			// non-const version
				try
				{
					PLN("vectorTest.at(0): " << vectorTest.at(0));
					vectorTest2.at(1) = 42;
					PLN("vectorTest2.at(1): " << vectorTest2.at(1));
					PLN(vectorTest.at(10)); // should throw exception
				}
				catch (std::exception &e)
				{
					PLN("Exception caught: " << e.what());
				}
			// const-version
				//const NSP::vector<int>& vectorTestConstReference = vectorTest;
				//PLN("Still 5 * 20: " << vectorTestConstReference);
				// vectorTestConstReference.at(0) = 5; can't assign to const reference
		// operator[]
			vectorTest[0] = 8;
			vectorTest2[0] = 10;
			vectorTest[4] = -12;
			vectorTest2[4] = 9;
			PLN("vectorTest[0] = 8: " << vectorTest[0]);
			PLN("vectorTest2[0] = 10: " << vectorTest2[0]);
			PLN("vectorTest[4] = -12: " << vectorTest[4]);
			PLN("vectorTest2[4] = 9: " << vectorTest2[4]);
		// front, back, data
			PLN("vectorTest.front(): " << vectorTest.front());
			PLN("vectorTest.back(): " << vectorTest.back());
			//PLN("vectorTest.data(): " << vectorTest.data() << " *vectorTest.data(): " << *vectorTest.data());
			PLN("vectorTest2.front(): " << vectorTest2.front());
			PLN("vectorTest2.back(): " << vectorTest2.back());
			//PLN("vectorTest2.data(): " << vectorTest2.data() << " *vectorTest.data(): " << *vectorTest2.data());
		// empty, size, max_size, reserve, capacity, resize
			NSP::vector<double> vectorTest3;
			PLN("vectorTest.empty(): " << vectorTest.empty());
			PLN("vectorTest2.empty(): " << vectorTest2.empty());
			PLN("vectorTest3.empty(): " << vectorTest3.empty());
			PLN("vectorTest.size(): " << vectorTest.size());
			PLN("vectorTest3.size(): " << vectorTest3.size());
			PLN("vectorTest.max_size(): " << vectorTest.max_size());
			PLN("vectorTest3.max_size(): " << vectorTest3.max_size());
			PLN("vectorTest.capacity(): " << vectorTest.capacity());
			PLN("vectorTest3.capacity(): " << vectorTest3.capacity());
			vectorTest.reserve(100);
			PLN("vectorTest.reserve(100);");
			PLN("vectorTest.capacity(): " << vectorTest.capacity());
			PLN("vectorTest.resize(1000);"); vectorTest.resize(1000);
			PLN("vectorTest: " << vectorTest);
		// assign iterator version
			vectorTest.assign(vectorTest2.begin(), vectorTest2.end());
			PLN("vectorTest.assign(vectorTest2.begin(), vectorTest2.end());");
			PLN("vectorTest2: " << vectorTest2);
			PLN("vectorTest: " << vectorTest);
			PLN("vectorTest.capacity(): " << vectorTest.capacity());
			PLN("vectorTest.size(): " << vectorTest.size());
		// iterators
			PLN("*vectorTest.begin(): " << *vectorTest.begin());
			PLN("*--vectorTest.end(): " << *--vectorTest.end());
			PLN("Const iterator");
			PLN("for (NSP::vector<int>::const_iterator cit = vectorTest.begin(); cit != vectorTest.end(); ++cit)\n"\
				"\tPLN(\"*cit: \" << *cit);\n{");
			//for (NSP::vector<int>::const_iterator cit = vectorTest.begin(); cit != vectorTest.end(); ++cit)
			// 	PLN("\t*cit: " << *cit);
			PLN("}");
			PLN("Non-const iterator");
			PLN("for (NSP::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end(); ++it)\n"\
				"\tPLN(\"*cit: \" << *cit);\n{");
			for (NSP::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end(); ++it)
				PLN("\t*it: " << *it);
			PLN("}");
		// clear, insert, erase
			PLN("vectorTest.clear()"); vectorTest.clear();
			PLN("vectorTest.size(): " << vectorTest.size() << " vectorTest: " << vectorTest << "vectorTest.capacity(): " << vectorTest.capacity());
			PLN("vectorTest.insert(vectorTest.end(), 3, 10);"); vectorTest.insert(vectorTest.end(), 3, 10);
			PLN("vectorTest: " << vectorTest);
			PLN("vectorTest.erase(vectorTest.begin());"); vectorTest.erase(vectorTest.begin());
			PLN("vectorTest: " << vectorTest);
			PLN("vectorTest.insert(vectorTest.begin(), vectorTest2.begin(), vectorTest2.end());"); vectorTest.insert(vectorTest.begin(), vectorTest2.begin(), vectorTest2.end());
			PLN("for (NSP::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end();)\n"\
				"\tit = vectorTest.erase(it);;\n\tPLN(\"vectorTest: \" << vectorTest);\n{");
			for (NSP::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end();)
			{
				it = vectorTest.erase(it);
				PLN("\tvectorTest: " << vectorTest);
			}
			PLN("}");
		// push_back, pop_back
			PLN("vectorTest.push_back(5);"); vectorTest.push_back(5);
			PLN("vectorTest.push_back(4);"); vectorTest.push_back(4);
			PLN("vectorTest.push_back(3);"); vectorTest.push_back(3);
			PLN("vectorTest.push_back(2);"); vectorTest.push_back(2);
			PLN("vectorTest.push_back(1);"); vectorTest.push_back(1);
			PLN("vectorTest: " << vectorTest);
			PLN("vectorTest.pop_back();"); vectorTest.pop_back();
			PLN("vectorTest.pop_back();"); vectorTest.pop_back();
			PLN("vectorTest.pop_back();"); vectorTest.pop_back();
			PLN("vectorTest.pop_back();"); vectorTest.pop_back();
			PLN("vectorTest: " << vectorTest);
		// swap
			PLN("vectorTest.swap(vectorTest2);"); vectorTest.swap(vectorTest2);
			PLN("vectorTest: " << vectorTest << " vectorTest2: " << vectorTest2);
			PLN("vectorTest.size(): " << vectorTest.size() << " vectorTest2.size(): " << vectorTest2.size());
			PLN("vectorTest.capacity(): " << vectorTest.capacity() << " vectorTest2.capacity(): " << vectorTest2.capacity());
			PLN("swap(vectorTest, vectorTest2);"); swap(vectorTest, vectorTest2);
			PLN("vectorTest: " << vectorTest << " vectorTest2: " << vectorTest2);
			PLN("vectorTest.size(): " << vectorTest.size() << " vectorTest2.size(): " << vectorTest2.size());
			PLN("vectorTest.capacity(): " << vectorTest.capacity() << " vectorTest2.capacity(): " << vectorTest2.capacity());
		// compare operators
			PLN("vectorTest == vectorTest2: " << (vectorTest == vectorTest2));
			PLN("vectorTest != vectorTest2: " << (vectorTest != vectorTest2));
			PLN("vectorTest < vectorTest2: " << (vectorTest < vectorTest2));
			PLN("vectorTest <= vectorTest2: " << (vectorTest <= vectorTest2));
			PLN("vectorTest > vectorTest2: " << (vectorTest > vectorTest2));
			PLN("vectorTest >= vectorTest2: " << (vectorTest >= vectorTest2));
		// iterator constructor
			PLN("NSP::vector<int> vectorTest4(vectorTest2.begin(), vectorTest2.end());");
			NSP::vector<int> vectorTest4(vectorTest2.begin(), vectorTest2.end());
			PLN("vectorTest4: " << vectorTest4);
			PLN("vectorTest2: " << vectorTest2);
	// Performance test
		clock_t begin = std::clock();
		PLN("push_back 100.000 ints");
		for (size_t i = 0; i < 100000; ++i)
			vectorTest.push_back(std::rand());
		PLN("vectorTest.size(): " << vectorTest.size());
		PLN("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		begin = std::clock();
		PLN("insert 100.000 ints");
		for (size_t i = 0; i < 100000; ++i)
			vectorTest.insert(vectorTest.end(), 2, std::rand());
		PLN("vectorTest.size(): " << vectorTest.size());
		PLN("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		begin = std::clock();
		PLN("vectorTest5(vectorTest);");
		NSP::vector<int> vectorTest5(vectorTest);
		PLN("vectorTest5.size(): " << vectorTest5.size());
		PLN("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		begin = std::clock();
		PLN("vectorTest2.assign(vectorTest5.begin(), vectorTest5.end());"); vectorTest2.assign(vectorTest5.begin(), vectorTest5.end());
		PLN("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		system("leaks container_test");
	}
