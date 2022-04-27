#ifndef UTILS_HPP
# define UTILS_HPP

#include <algorithm>

namespace ft{

	template<typename T>
	void	swap(T &a, T &b) {
		T	temp(a);
		a = b;
		b = temp;
	};

	template<typename T>
	T	max(T a, T b) {
		if (a > b)
			return a;
		return b;
	};



}; //</ft>

#endif