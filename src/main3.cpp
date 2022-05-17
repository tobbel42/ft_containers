#include "map.hpp"
#include "vector.hpp"
#include <iostream>
#include <map>

int main()
{
	{
		ft::map<int, int> a;
		ft::pair<int, int> b;
		ft::vector< ft::pair<int, int> > c;

		b.first = 33;
		b.second = 42;

		a.insert(b);
		a.insert(ft::pair<int, int>(99, 88));
		a.insert(ft::make_pair<int, int>(77, 124));

		for (int i = 0; i < 10; ++i)
		{
			a.insert(ft::pair<int, int>(i, i + 1));
			c.push_back(ft::make_pair(i, i + 1));
			std::cout << a.size() << std::endl;
		}



		ft::map<int, int>::const_iterator iter = a.begin();
		std::cout << *iter << std::endl;
		a.printTree();

		//int x; std::cin >> x;
		a.erase(6);
		a.printTree();

		iter = a.find(7);

		std::cout << *iter << std::endl;

		std::cout << "new Map" << std::endl;

		ft::map<int, int> d(c.begin(), c.end());
		ft::map<int, int> f;
		f.insert(c.begin(), c.end());
		f.insert(f.end(), ft::make_pair<int, int>(2414, 12415));
		d.printTree();
		f.printTree();
		d.swap(f);
		d.printTree();
		f.printTree();


		ft::map<int, int>::value_compare comp = d.value_comp();

		// std::cout << *d.lower_bound(4) << std::endl;
		// iter = d.upper_bound(6);
		// ft::pair<ft::map<int, int>::iterator,
		// 		ft::map<int, int>::iterator> pi;
		// pi = d.equal_range(7);
		std::map<int, int> smap;
		for (int i = 0; i < 10; ++i) {
			smap.insert(std::make_pair(i, i + 1));
		}
		std::pair< std::map<int, int>::iterator, std::map<int, int>::iterator> pa;

		pa = smap.equal_range(7);
		// std::cout << *(pi.first) << " " << *(pi.second) << std::endl;
		std::cout << (pa.first)->second << " " << (pa.second)->second << std::endl;
		std::cout << comp(ft::make_pair(13, 20), ft::make_pair(11, 20)) << std::endl;

		for (ft::map<int, int>::reverse_iterator iter = a.rbegin(); iter != a.rend(); ++iter)
			std::cout << *iter << std::endl;
		
		d[30] = 65234;
		d.printTree();
		std::cout << "DONE" << std::endl;
	}	
	system("leaks container_test");

	return 0;
}