#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iostream>


#include "iterator.hpp"
#include "type_traits.hpp"

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
			~vector_iterator() {};

			vector_iterator&	operator=(const vector_iterator& rhs){m_ptr = rhs.m_ptr; return (*this);};
			difference_type		operator-(const vector_iterator&rhs) const {return m_ptr - rhs.base();};

			vector_iterator&	operator++(void) {++m_ptr; return (*this);};
			vector_iterator		operator++(int) {vector_iterator tmp(*this); ++m_ptr; return (*this);};
			vector_iterator&	operator--(void) {--m_ptr; return (*this);};
			vector_iterator		operator--(int) {vector_iterator tmp(*this); --m_ptr; return (*this);};

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
				allocator(alloc)
			{
				start = allocator.allocate(n);
				finish = start + n;
				end_of_storage = finish;
				for (size_type i = 0; i < n; ++i)
					allocator.construct(start.base() + i, val);
			};
			template<class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()):
				start(NULL),
				finish(NULL),
				end_of_storage(NULL),
				allocator(alloc)
			{
				size_type	n = 0;
				for(difference_type i = 0;first + i != last; ++i)
					++n;
				start = allocator.allocate(n);
				finish = start + n;
				end_of_storage = finish;
				for (size_type i = 0; i < n; ++i)
					allocator.construct(start.base(), first[i]);
			}
			// vector(const vector & x);
			~vector()
			{
				for (size_type i = 0; i < size(); ++i)
					allocator.destroy(start.base() + i);
				if (start.base())
					allocator.deallocate(start.base(), capacity());
			}

			//<Iterators>
			iterator				begin() {return start;};
			const_iterator			begin()	const {return start;};
			iterator				end() {return finish;};
			const_iterator			end() const {return finish;};
			reverse_iterator		rbegin() {return reverse_iterator(finish);};
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(finish);};
			reverse_iterator		rend() {return reverse_iterator(start);};
			const_reverse_iterator	rend() const {return const_reverse_iterator(start);};
			//</Iterators>

			//<Capacity>
			size_type	size() const {return finish - start;};
			size_type	max_size() const {return allocator.max_size();};
			size_type	capacity() const {return end_of_storage - start;};
			bool		empty() const { return !size();};
			void		resize(size_type n, value_type val = value_type()){
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

			void		reserve(size_type n){
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
				if (start)
					allocator.deallocate(start, capacity());
				start = newStart;
				finish = newStart + oldSize;
				end_of_storage = newStart + n;
			}
		//</Capacity>

		private:
			iterator	start;
			iterator	finish;
			iterator	end_of_storage;
			Alloc		allocator;


	};
}

#endif

