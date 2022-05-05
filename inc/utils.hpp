#ifndef UTILS_HPP
# define UTILS_HPP

#include <algorithm>
#include <iostream>

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

	template <class T1, class T2>
	struct pair {
		public:
			typedef T1 first_type;
			typedef T2 second_type;
		
			first_type	first;
			second_type second;

			pair() {};
			template<class U, class V>
			pair (const pair<U, V>& pr):
				first(pr.first),
				second(pr.second) {};
			pair (const first_type& a, const second_type& b):
				first(a),
				second(b) {};
			pair & operator=(const pair & rhs) {
				if (rhs != *this)
				{
					first = rhs.first;
					second =rhs.second;
				}
				return *this;
			};
	};

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
    	return pair<T1,T2>(x,y);
	}

	template <class T1, class T2>
	std::ostream & operator<<(std::ostream & s, const ft::pair<T1, T2> p) {
		s << "(" << p.first << ", " << p.second << ")";
		return s; 
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	};

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	};

	template <class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	};

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	};

	template <class T1, class T2>
	bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	};

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs);
	};


	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                            	InputIterator2 first2, InputIterator2 last2) {
		for (; first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || *first2< *first1)
				return false;
			else if (*first1 < *first2)
				return true;
		}
		return (first2 != last2);
	};


	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp) {
		for (; first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
		}
		return (first2 != last2);
		
	};


}; //</ft>

#endif