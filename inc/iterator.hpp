#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <memory>
#include <iterator>

namespace ft
{ 

//iterator traits //for compatiblity with the std::containers
typedef std::input_iterator_tag	input_iterator_tag ;
typedef std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

template <class Iterator>
class iterator_traits
{
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef	typename	Iterator::difference_type	difference_type;
	typedef	typename	Iterator::value_type		value_type;
	typedef	typename	Iterator::pointer			pointer;
	typedef	typename	Iterator::reference			reference;
	typedef	typename	Iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*>
{
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef	ptrdiff_t					difference_type;
	typedef	T							value_type;
	typedef	T*							pointer;
	typedef	T&							reference;
	typedef	random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef	ptrdiff_t					difference_type;
	typedef	T							value_type;
	typedef	const T*					pointer;
	typedef	const T&					reference;
	typedef	random_access_iterator_tag	iterator_category;
};

template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class iterator
{
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef	T			value_type;
	typedef	Distance	difference_type;
	typedef	Pointer		pointer;
	typedef	Reference	reference;
	typedef	Category	iterator_category;
};



template <class _Iter>
class reverse_iterator
	:public iterator<typename	iterator_traits<_Iter>::difference_type,
					typename	iterator_traits<_Iter>::value_type,
					typename	iterator_traits<_Iter>::pointer,
					typename	iterator_traits<_Iter>::reference,
					typename	iterator_traits<_Iter>::iterator_category>
{
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef _Iter												iterator_type;
	typedef	typename iterator_traits<_Iter>::difference_type	difference_type;
	typedef typename iterator_traits<_Iter>::reference			reference;
	typedef typename iterator_traits<_Iter>::pointer			pointer;
		
	protected:
	/*MemberVariabels---------------------------------------------------------*/
	iterator_type m_current;

	public:
	/*Constructor-------------------------------------------------------------*/
	reverse_iterator(): m_current() {};
	reverse_iterator(_Iter cpy): m_current(cpy) {};
	template <class T>
	reverse_iterator(const reverse_iterator<T>& cpy) { *this = cpy; };
	template <class T>
	reverse_iterator& operator=(const reverse_iterator<T>& rhs) {
		m_current = rhs.base();
		return *this;
	};

	/*Operators---------------------------------------------------------------*/

	reference	operator*() const {
		iterator_type tmp = m_current;
		return *(--tmp);
	};
	pointer		operator->() const {
		iterator_type tmp = m_current;
		return ((--tmp).operator->());
	};
	reference	operator[](difference_type n) const {
		return *(base() - n - 1);
	};
	reverse_iterator&	operator++() {
		--m_current;
		return *this;
	};
	reverse_iterator	operator++(int) {
		reverse_iterator tmp(*this);
		--m_current;
		return tmp;
	};
	reverse_iterator&	operator--() {
		++m_current;
		return *this;
	};
	reverse_iterator	operator--(int) {
		reverse_iterator tmp(*this);
		++m_current;
		return tmp;
	};
	reverse_iterator&	operator+=(difference_type n) {
		m_current -= n;
		return *this;
	}; 
 	reverse_iterator	operator+(difference_type n) {
		return reverse_iterator(m_current - n);
	};
	reverse_iterator&	operator-=(difference_type n) {
		m_current += n;
		return *this;
	};
	reverse_iterator	operator-(difference_type n) { 
		return reverse_iterator(m_current + n); };
	/*Getter------------------------------------------------------------------*/	
	iterator_type	base() const { return m_current; };
};

template <class Iter>
reverse_iterator<Iter> operator+(
	typename reverse_iterator<Iter>::difference_type n,
	const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - n);
};
template <class Iter1, class Iter2>
typename reverse_iterator<Iter1>::difference_type operator-(
	const reverse_iterator<Iter1> & lhs,
	const reverse_iterator<Iter2> &rhs) {
		return (rhs.base().base() - lhs.base().base());
};
template <class Iter1, class Iter2>
bool operator==(const reverse_iterator<Iter1> & rhs,
				const reverse_iterator<Iter2> & lhs) { 
					return rhs.base() == lhs.base();
};
template <class Iter1, class Iter2>
bool operator!=(const reverse_iterator<Iter1> & rhs,
				const reverse_iterator<Iter2> & lhs) {
					return rhs.base() != lhs.base();
};
template <class Iter1, class Iter2>
bool operator>=(const reverse_iterator<Iter1> & rhs,
				const reverse_iterator<Iter2> & lhs) { 
					return rhs.base() <= lhs.base();
};
template <class Iter1, class Iter2>
bool operator>(const reverse_iterator<Iter1> & rhs, 
				const reverse_iterator<Iter2> & lhs) { 
					return rhs.base() < lhs.base();
};
template <class Iter1, class Iter2>
bool operator<=(const reverse_iterator<Iter1> & rhs,
				const reverse_iterator<Iter2> & lhs) { 
					return rhs.base() >= lhs.base();
};
template <class Iter1, class Iter2>
bool operator<(const reverse_iterator<Iter1> & rhs, 
				const reverse_iterator<Iter2> & lhs) { 
					return rhs.base() > lhs.base();
};
template <class InputIter>
typename iterator_traits<InputIter>::difference_type distance(
	InputIter first, InputIter last) {
		typename iterator_traits<InputIter>::difference_type dist = 0;
		for(;first != last; ++first)
			++dist;
		return dist;
};

};


#endif