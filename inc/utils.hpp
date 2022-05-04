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

	template <class T>
	struct less : std::binary_function <T,T,bool> {
  		bool operator() (const T& x, const T& y) const {return x<y;}
	};

	//redo
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
  		while (first1 != last1) {
    		if (!(*first1 == *first2))
    			return false;
    		++first1; ++first2;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool equal (InputIterator1 first1, InputIterator1 last1,
            		InputIterator2 first2, BinaryPredicate pred) {
  		while (first1!=last1) {
    		if (!pred(*first1,*first2))
      			return false;
    		++first1; ++first2;
  		}
  		return true;
	};


}; //</ft>

#endif