#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iostream>

#include <algorithm>


#include "iterator.hpp"
#include "type_traits.hpp"
#include "utils.hpp"

namespace ft
{

	template <typename T>
	class vector_iterator
	{
		public:
			typedef iterator<random_access_iterator_tag, T>	iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;
		
			vector_iterator() : m_ptr() {};
			vector_iterator(pointer ptr) : m_ptr(ptr) {};
			vector_iterator(const vector_iterator& cpy) {*this = cpy;};

			//enable to transform const iter to iter and vice versa
			template<typename T2>
				vector_iterator(const vector_iterator<T2>& other,
				typename enable_if<std::is_constructible<T, T2>::value, T2>::type* = nullptr)
					: m_ptr(other.base()) {};

			~vector_iterator() {};

			vector_iterator&	operator=(const vector_iterator& rhs){m_ptr = rhs.m_ptr; return (*this);};
			difference_type		operator-(const vector_iterator&rhs) const {return m_ptr - rhs.base();};

			vector_iterator&	operator++(void) {++m_ptr; return (*this);};
			vector_iterator		operator++(int) {vector_iterator tmp(*this); ++m_ptr; return (tmp);};
			vector_iterator&	operator--(void) {--m_ptr; return (*this);};
			vector_iterator		operator--(int) {vector_iterator tmp(*this); --m_ptr; return (tmp);};

			reference			operator[](difference_type i) const {return *(m_ptr + i);};
			pointer				operator->() const {return (m_ptr);};
			reference			operator*() const {return (*m_ptr);};

			vector_iterator&	operator+=(difference_type n) {m_ptr += n; return(*this);};
			vector_iterator&	operator-=(difference_type n) {m_ptr -= n; return(*this);};

			vector_iterator		operator+(difference_type n) const {return(vector_iterator(m_ptr + n));};
			vector_iterator		operator-(difference_type n) const {return(vector_iterator(m_ptr - n));};

			pointer				base() const {return(m_ptr);};

		
		private:
			pointer	m_ptr;
	};
	template <typename T, typename U>
	bool	operator==(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() == rhs.base();}

	template <typename T, typename U>
	bool	operator!=(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() != rhs.base();}

	template <typename T, typename U>
	bool	operator<=(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() <= rhs.base();}

	template <typename T, typename U>
	bool	operator<(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() < rhs.base();}

	template <typename T, typename U>
	bool	operator>=(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() >= rhs.base();}

	template <typename T, typename U>
	bool	operator>(const vector_iterator<T> lhs, const vector_iterator<U> rhs) { return lhs.base() > rhs.base();}


	template< class T,class Alloc = std::allocator<T> >
	class vector{
		private:
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;

			typedef vector_iterator<value_type>					iterator;
			typedef vector_iterator<const value_type>			const_iterator;
			typedef class ft::reverse_iterator<iterator>		reverse_iterator;
			typedef class ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef std::size_t						size_type;
			typedef std::ptrdiff_t					difference_type;

			explicit vector(const allocator_type & alloc = allocator_type()):
				start(NULL),
				finish(NULL),
				end_of_storage(NULL),
				allocator(alloc) {};
			explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
				start(NULL),
				finish(NULL),
				end_of_storage(NULL),
				allocator(alloc) {assign(n, val);};
			template<class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()):
				start(NULL),
				finish(NULL),
				end_of_storage(NULL),
				allocator(alloc) {assign(first, last);};
			vector(const vector & x):
				start(NULL),
				finish(NULL),
				end_of_storage(NULL),
				allocator(x.get_allocator())
			{
				size_type	xSize = x.size();
				reserve(xSize);
				for (size_type i = 0; i < xSize; ++i)
					allocator.construct(start.base() + i, x[i]);
				finish = start + xSize;
				end_of_storage = start + xSize;
			};
			~vector()
			{
				clear();
				if (start.base())
					allocator.deallocate(start.base(), capacity());
			};
			vector & operator=(const vector& x)
			{
				allocator = x.allocator;
				if (this != &x)
				{
					size_type	xSize = x.size();
					reserve(xSize);
					end_of_storage = start + xSize;
					for (size_type i = 0; i < xSize; ++i)
						allocator.construct(start.base() + i, x[i]);
					finish = start + xSize;
				}
				return (*this);
			};

			//<Iterators>
			iterator				begin() 		{return start;};
			const_iterator			begin()	const	{return start;};
			iterator				end() 			{return finish;};
			const_iterator			end() const 	{return finish;};
			reverse_iterator		rbegin() 		{return reverse_iterator(finish);};
			const_reverse_iterator	rbegin() const	{return const_reverse_iterator(finish);};
			reverse_iterator		rend() 			{return reverse_iterator(start);};
			const_reverse_iterator	rend() const	{return const_reverse_iterator(start);};
			//</Iterators>

			//<Capacity>
			size_type	size() const {return finish - start;};
			size_type	max_size() const {return allocator.max_size();};
			size_type	capacity() const {return end_of_storage - start;};
			bool		empty() const { return !size();};
			void		resize(size_type n, value_type val = value_type()) {
				if (n > max_size())
					throw std::length_error("vector: resize: requested size too big.");
				if (n < size())
				{
					iterator	newStart = allocator.allocate(n);

					for (size_type i = 0; i < n; ++i)
					{
						allocator.construct(newStart.base() + i, start[i]);
						allocator.destroy(start.base() + i);
					}
					for (size_type i = n; i < size(); ++i)
						allocator.destroy(start.base() + i);	
					if (start.base())
						allocator.deallocate(start.base(), capacity());
					start = newStart;
					finish = newStart + n;
					end_of_storage = newStart + n;
				}
				else if (n > size() && n < capacity())
				{
					for (size_type i = size(); i < n; ++i)
						allocator.construct(start.base() + i, val);
					finish = start + n;
				}
				else if (n > capacity())
				{
					iterator	newStart = allocator.allocate(n);

					for (size_type i = 0; i < size(); ++i)
					{
						allocator.construct(newStart.base() + i, start[i]);
						allocator.destroy(start.base() + i);
					}
					if (start.base())
						allocator.deallocate(start.base(), capacity());
					for (size_type i = size(); i < n; ++i)
						allocator.construct(newStart.base() + i, val);
					start = newStart;
					finish = newStart + n;
					end_of_storage = newStart + n;
				}
			};

			void		reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector: reserve: requested size too big.");
				if (n <= capacity())
					return ;
				iterator	newStart = allocator.allocate(n);
				size_type	oldSize = size();

				for (size_type i = 0; i < size(); ++i)
				{
					allocator.construct(newStart.base() + i, start[i]);
					allocator.destroy(start.base() + i);
				}
				if (start.base())
					allocator.deallocate(start.base(), capacity());
				start = newStart;
				finish = newStart + oldSize;
				end_of_storage = newStart + n;
			}
		//</Capacity>

		//<ElementAccess>
			reference 		operator[] (size_type n)		{return start[n];};
			const_reference	operator[] (size_type n) const	{return start[n];};
			reference 		at (size_type n) {
				if (n >= size())
					throw std::out_of_range("vector: at: n out of bounds");
				return start[n];
			};
			const_reference at (size_type n) const {
				if (n >= size())
					throw std::out_of_range("vector: at: n out of bounds");
				return start[n];
			};
			reference 		front() 		{return *start;};
			const_reference front() const	{return *start;};
			reference 		back() 			{return *(finish - 1);};
			const_reference back() const	{return *(finish - 1);};

		//</ElementAccess>

		//<Modifiers>
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
					size_type n = static_cast<size_type>(ft::distance(first, last));
					clear();
					if (n > capacity())
						reserve(n);
					for (size_type i = 0; first != last; ++i, ++first)
						allocator.construct(start.base() + i, *first);
					finish = start + n;
			};

			void assign (size_type n, const value_type& val) {
				clear();
				if (n > capacity())
					reserve(n);
				for (size_type i = 0; i < n; ++i)
					allocator.construct(start.base() + i, val);
				finish = start + n;
			};

			void push_back (const value_type& val) {
				if (size() == capacity())
					reserve(size() * 2 + 1);
				allocator.construct(finish.base(), val);
				++finish;
			};

			void pop_back() {
				allocator.destroy(finish.base() - 1);
				--finish;
			};

			iterator insert (iterator position, const value_type& val) {
				if (size() >= capacity())
				{
					difference_type offset = position - start;
					reserve(size() * 2 + 1);
					position = start + offset;
				}
				if (position != finish)
				{
					for (reverse_iterator iter = rbegin(); iter.base() != position; ++iter)
					{
						allocator.construct(iter.base().base(), *iter);
						allocator.destroy(iter.base().base());
					}
				}
				*position = val;
				++finish;
				return position;
			};

			void insert (iterator position, size_type n, const value_type& val) {
				if (size() + n > capacity())
				{
					difference_type offset = position - start;
					reserve(ft::max(size() + n, size() * 2));
					position = start + offset;
				}
				if (position != finish)
				{
					for (reverse_iterator iter = rbegin(); iter.base() != position; ++iter)
					{
						allocator.construct(iter.base().base() + n - 1, *iter);
						allocator.destroy(iter.base().base());
					}
				}
				for (size_type i = 0; i < n; ++i)
					allocator.construct(position.base() + i, val);
				finish += n;				
			};

			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
					size_type n = static_cast<size_type>(ft::distance(first, last));
					if (size() + n > capacity())
					{
						difference_type offset = position - start;
						reserve(ft::max(size() + n, size() * 2));
						position = start + offset;
					}
					if (position != finish)
					{
						for (reverse_iterator iter = rbegin(); iter.base() != position; ++iter)
						{
							allocator.construct(iter.base().base() + n - 1, *iter);
							allocator.destroy(iter.base().base());
						}
					}
					for (;first != last; ++position, ++first)
						allocator.construct(position.base(), *first);
					finish += n;					
			};

			iterator erase (iterator position) {
				allocator.destroy(position.base());
				for (iterator iter = position + 1; iter != end(); ++iter)
				{
					allocator.construct(iter.base() - 1, *iter);
					allocator.destroy(iter.base());
				}
				--finish;
				return position;
			};

			iterator erase (iterator first, iterator last) {
				for (iterator iter = first; iter != last; ++iter)
					allocator.destroy(iter.base());
				for (iterator isrc = last, idest = first; isrc != finish; ++isrc, ++idest)
				{
					allocator.construct(idest.base(), *isrc);
					allocator.destroy(isrc.base());
				}
				finish -= ft::distance(first, last);
				return(first);
			};

			void swap (vector& x) {
				ft::swap(start, x.start);
				ft::swap(finish, x.finish);
				ft::swap(end_of_storage, x.end_of_storage);
				ft::swap(allocator, x.allocator);
			};

			void clear () {
				for (size_type i = 0; i < size(); ++i)
					allocator.destroy(start.base() + i);
				finish = start;
			};

		//</Modifiers>

		//<Allocator>
			allocator_type get_allocator() const {return allocator;};
		//</Allocator>

		private:
			iterator	start;
			iterator	finish;
			iterator	end_of_storage;
			Alloc		allocator;

	};

	template <class T, class Alloc>
  		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			x.swap(y);
		};

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() != rhs.size())
				return false;
			for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); ++i)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		};
	
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		};


	template <class T, class Alloc>
  		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			for(typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); ++i)
			{
				if (lhs[i] != rhs[i])
				{
					if (lhs[i] < rhs[i])
						return true;
					else
						return false;
				}
			}
			if (lhs.size() < rhs.size())
				return true;
			return false;
		};	

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		};
	
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return rhs < lhs;
		};

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		};



};

template <class Iter>
ft::vector_iterator<Iter> operator+(typename ft::vector_iterator<Iter>::difference_type n, const ft::vector_iterator<Iter>& it) {
	return (ft::vector_iterator<Iter>(it.base() + n));
};

template <class T, class Alloc>
std::ostream& operator<< (std::ostream& s, const ft::vector<T, Alloc> vec){
	for (typename ft::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
		s << "[" << vec[i] << "] ";
	return s;
};

#endif

