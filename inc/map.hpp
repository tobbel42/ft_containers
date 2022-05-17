#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include <map>

#include "iterator.hpp"
#include "rbTree.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft {

	template <class T>
	class map_iterator: public rbTree_iterator<ft::rbNode<T> >
	{
		public:
			typedef T					value_type;
			typedef	ft::rbNode<T>		node_type;
			// typedef	&T			reference;
			// typedef	*T					pointer;
			map_iterator() {};
			map_iterator(const typename rbTree_iterator<node_type>::pointer ptr):
				rbTree_iterator<node_type>(ptr) {};
			map_iterator(const rbTree_iterator<node_type> & iter):
				rbTree_iterator<node_type>(iter) {};
			map_iterator(const map_iterator<value_type> & cpy):
				rbTree_iterator<node_type>(cpy.base()) {};
			
	
	
			map_iterator & operator=(const map_iterator<value_type> & rhs) {
				rbTree_iterator<node_type>::m_ptr = rhs.base();
				return *this;
			};

			map_iterator & operator++() { this->next(); return *this; } ;
			map_iterator & operator--() { this->prev(); return *this; } ;
			value_type	&operator*() const { return rbTree_iterator<node_type>::m_ptr->m_value; }
			value_type	*operator->() const { return &(rbTree_iterator<node_type>::m_ptr->m_value);}

	};

	template <typename T, typename U>
	bool operator==(const map_iterator<T> & lhs, const map_iterator<U> & rhs) {
		return lhs.base() == rhs.base();
	};

	template <typename T, typename U>
	bool operator!=(const map_iterator<T> & lhs, const map_iterator<U> & rhs) {
		return lhs.base() != rhs.base();
	};


	template <class T >
	class const_map_iterator: public rbTree_iterator<ft::rbNode<const T> >
	{
		public:
			typedef const T				value_type;
			typedef	ft::rbNode<value_type>	node_type;
			// const_map_iterator(const typename rbTree_iterator<node_type>::pointer ptr):
			// 	rbTree_iterator<node_type>(ptr) {};
			// const_map_iterator(const rbTree_iterator<node_type> & iter):
			// 	rbTree_iterator<node_type>(iter) {};
			const_map_iterator() {};
			const_map_iterator(const map_iterator<T>& cpy):
				rbTree_iterator<node_type>((node_type *)((void *)cpy.base())) {};
	
			value_type	&operator*() const { return rbTree_iterator<node_type>::m_ptr->m_value; }
			value_type	*operator->() const { return &(rbTree_iterator<node_type>::m_ptr->m_value);}

			const_map_iterator & operator=(const const_map_iterator<T> & rhs) {
				rbTree_iterator<node_type>::m_ptr = rhs.base();
				return *this;
			};

			const_map_iterator &	operator++() {this->next(); return *this; };


	};

	template <typename T, typename U>
	bool operator==(const_map_iterator<T> & lhs, const_map_iterator<U> & rhs) {
		return lhs.base() == rhs.base();
	};

	template <typename T, typename U>
	bool operator!=(const_map_iterator<T> & lhs, const_map_iterator<U> & rhs) {
		return lhs.base() != rhs.base();
	};

template <class MapIterator>
	class reverse_map_iterator
	// :public iterator<typename	iterator_traits<MapIterator>::difference_type,
	// 			typename	iterator_traits<MapIterator>::value_type,
	// 			typename	iterator_traits<MapIterator>::pointer,
	// 			typename	iterator_traits<MapIterator>::reference,
	// 			typename	iterator_traits<MapIterator>::iterator_category>
	{
		protected:
		MapIterator	m_current;
		public:
		reverse_map_iterator() {};
		reverse_map_iterator(MapIterator x) : m_current(x) {};
		MapIterator base() const { return m_current; };

		reverse_map_iterator&	operator++() { --m_current; return *this; };
		reverse_map_iterator	operator++(int) {
			MapIterator tmp = m_current;
			--m_current;
			return tmp; }
		reverse_map_iterator&	operator--() { ++m_current; return *this; };
		reverse_map_iterator	operator--(int) {
			MapIterator tmp = m_current;
			++m_current;
			return tmp; };

		typename MapIterator::value_type&	operator*() const { return *m_current; };
		typename MapIterator::value_type*	operator->() const { return m_current.operator->(); };
	};

	template <class T1, class T2>
	bool operator==(const reverse_map_iterator<T1> & rhs,
					const reverse_map_iterator<T2> &lhs) {
		return rhs.base() == lhs.base();
	};
	template <class T1, class T2>
	bool operator!=(const reverse_map_iterator<T1> & rhs,
					const reverse_map_iterator<T2> &lhs) {
		return rhs.base() != lhs.base();
	};


	template <class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef	Compare								key_compare;
		typedef	Alloc								allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef	typename allocator_type::difference_type	difference_type;

		class map_compare:
		std::binary_function <value_type, value_type, bool> {
			friend class map;
			protected:

			Compare comp;
			map_compare (Compare c) : comp(c) {};
		
			public:
			map_compare () : comp(key_compare()) {};
			bool operator() (const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			};
			bool operator() (const value_type& x, const key_type& y) const {
				return comp(x.first, y);
			};
			bool operator() (const key_type& x, const value_type& y) const {
				return comp(x, y.first);
			};

		};

		class value_compare:
		std::binary_function <value_type, value_type, bool> {  
			friend class map;
			protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {};

			public:

			bool operator() (const value_type& x, const value_type& y) const {
		    	return comp(x.first, y.first);
			};
		};

		typedef typename ft::rbTree<value_type, map_compare>	tree_type;
		typedef typename tree_type::node_type					node_type;

		typedef	ft::map_iterator<value_type>			iterator;
		typedef ft::const_map_iterator<value_type>		const_iterator;
		typedef ft::reverse_map_iterator<iterator>		reverse_iterator;
		typedef ft::reverse_iterator<const iterator>	const_reverse_iterator;

		private:

		/*memberVariables-----------------------------------------------------*/
		tree_type			m_tree;
		allocator_type		m_allocator;
		key_compare			m_compare;

		public:

		/*constructors--------------------------------------------------------*/
		explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()):
			m_allocator(alloc),
			m_compare(comp) {};
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type & alloc = allocator_type()):
			m_allocator(alloc),
			m_compare(comp) {
				for (; first != last; ++first)
					m_tree.insertValue(*first, first->first);
		};
		map (const map & x):
			m_allocator(x.get_allocator()),
			m_compare(x.key_comp()) { *this = x; };
		map & operator=(const map & rhs){
			m_tree.clearTree();
			for (iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
				m_tree.insertValue(*iter, iter->first);
			return *this;
		};
		
		/*destructor----------------------------------------------------------*/
		~map() { clear(); };

		/*Iterators-----------------------------------------------------------*/
		iterator		begin()	{ return m_tree.begin(); };
		const_iterator	begin() const { return const_iterator(m_tree.begin());};
		iterator		end() { return m_tree.end(); };
		const_iterator	end() const { return const_iterator(m_tree.end()); };
		reverse_iterator rbegin() { return iterator(m_tree.rbegin()); };
		const_reverse_iterator rbegin() const {
			return const_iterator(m_tree.rbegin());
		};
		reverse_iterator rend() { return iterator(m_tree.rend()); };
		const_reverse_iterator rend() const {
			return const_iterator(m_tree.rend());
		};

		/*Capacity------------------------------------------------------------*/
		bool		empty() const { return !m_tree.size(); };
		size_type 	size() const { return m_tree.size(); };
		size_type	max_size() const { return m_tree.max_size(); };

		/*Modifiers-----------------------------------------------------------*/
		iterator insert (iterator position, const value_type& val) {
			return m_tree.insertValue(val, val.first).first;
			(void)position;
		};
		ft::pair<iterator, bool> insert(const value_type & value) {
			return m_tree.insertValue(value, value.first);
		};
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				m_tree.insertValue(*first, first->second);
		};
		void erase (iterator position) {
			m_tree.deleteNode(position.base());
		}
		size_type erase(const key_type & key) {
			return m_tree.deleteValue(key);
		};
		void erase (iterator first, iterator last) {
			for (; first != last; ++first)
				erase(first);
		};
		void swap(map & x) {
			m_tree.swap(x.m_tree);
		};
		void clear() { m_tree.clearTree(); };

		/*Observers-----------------------------------------------------------*/
		key_compare key_comp() const { return m_compare; };
		value_compare value_comp() const { return value_compare(m_compare); };

		/*Operations----------------------------------------------------------*/
		iterator	find(const key_type & key) {
			return m_tree.findValue(key);
		};
		const_iterator find(const key_type & key) const {
			return m_tree.findValue(key);
		}
		size_type count (const key_type & k) const {
			iterator iter = find(k);
			if (iter.base())
				return 1;
			return 0;
		};
		iterator lower_bound(const key_type & k) {
			return m_tree.lower_bound(k);
		};
		const_iterator lower_bound(const key_type & k) const {
			return const_iterator(m_tree.lower_bound(k));
		};
		iterator upper_bound(const key_type & k) {
			return m_tree.upper_bound(k);
		};
		const_iterator upper_bound(const key_type & k) const {
			return const_iterator(m_tree.upper_bound(k));
		};
		ft::pair<iterator, iterator> equal_range(const key_type& k) {
			return ft::make_pair(m_tree.lower_bound(k), m_tree.upper_bound(k));
		};
		ft::pair<const_iterator, const_iterator>
		equal_range(const key_type & k) const {
			return ft::make_pair(const_iterator(m_tree.lower_bound(k)),
								const_iterator(m_tree.upper_bound(k)));
		};

		/*Utils---------------------------------------------------------------*/
		void	printTree() { m_tree.printTree(); };

		/*Allocator-----------------------------------------------------------*/
		allocator_type get_allocator() const { return m_allocator; };

	};

}; //<\ft>

#endif
