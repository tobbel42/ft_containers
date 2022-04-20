#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <memory>

namespace ft
{ 

//iterator traits
struct	input_iterator_tag {};
struct	output_iterator_tag {};
struct	forward_iterator_tag		: public input_iterator_tag {};
struct	bidirectional_iterator_tag	: public forward_iterator_tag {};
struct	random_access_iterator_tag	: public bidirectional_iterator_tag {};

template <class Iterator>
class iterator_traits
{
	public:
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
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
		typedef	Category	iterator_category;
};



template <class _Iter>
class reverse_iterator
	:public iterator<class iterator_traits<_Iter>::difference_type,
					class iterator_traits<_Iter>::value_type,
					class iterator_traits<_Iter>::pointer,
					class iterator_traits<_Iter>::reference,
					class iterator_traits<_Iter>::iterator_category>
{
	protected:
		_Iter current;
	public:
		typedef _Iter											iterator_type;
		typedef	class iterator_traits<_Iter>::difference_type	difference_type;
		typedef class iterator_traits<_Iter>::reference			reference;
		typedef class iterator_traits<_Iter>::pointer			pointer;
		
		reverse_iterator(): current() {};
		reverse_iterator(_Iter cpy): current(cpy) {};
		reverse_iterator(const reverse_iterator<_Iter>& cpy) {*this = cpy;};
		reverse_iterator&	operator=(const reverse_iterator<_Iter>& rhs) {current = rhs.current();};

		reference	operator*() const {_Iter tmp = current; return *(--tmp);};
		pointer		operator->() const {_Iter tmp = current; return ((--tmp).operator->());};
		reference	operator[](difference_type n) const {return *(*this + n);};

		reverse_iterator&	operator++() {--current; return *this;};
		reverse_iterator	operator++(int) {reverse_iterator tmp(*this); --current; return tmp;};
		reverse_iterator&	operator--() {++current; return *this;};
		reverse_iterator	operator--(int) {reverse_iterator tmp(*this); ++current; return tmp;};

		reverse_iterator&	operator+=(difference_type n) {current -= n; return *this;}; 
 		reverse_iterator	operator+(difference_type n) {return reverse_iterator(current - n);};
		reverse_iterator&	operator-=(difference_type n) {current += n; return *this;};
		reverse_iterator	operator-(difference_type n) {return reverse_iterator(current + n);};
};

// template <class InputIter>
// typename iterator_traits<InputIter>::difference_type
// distance(InputIter first, InputIter last)
// {
// 	typename iterator_traits<InputIter>::difference_type dist = 0;
// 	for(;first != last; ++first)
// 		++dist;
// 	return dist;
// };


}; //NSP ft


#endif