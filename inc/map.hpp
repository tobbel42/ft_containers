#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "iterator.hpp"
#include "rbTree.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft {
	template <class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		/*Typedefs------------------------------------------------------------*/
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

		typedef typename ft::rbTree<value_type, map_compare, allocator_type>
																tree_type;
		typedef typename tree_type::node_type			node_type;
		typedef typename tree_type::iterator			iterator;
		typedef typename tree_type::reverse_iterator 	reverse_iterator;
		typedef typename tree_type::const_iterator		const_iterator;
		typedef typename tree_type::const_reverse_iterator
														const_reverse_iterator;
		typedef	typename ft::iterator_traits<iterator>::difference_type
														difference_type;

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
			for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
				m_tree.insertValue(*iter, iter->first);
			return *this;
		};
		iterator getLoopback() { return m_tree.getLoopback(); };
		iterator getRoot() { return m_tree.getRoot(); };
		/*destructor----------------------------------------------------------*/
		~map() { clear(); };

		/*Iterators-----------------------------------------------------------*/
		iterator		begin()	{ return m_tree.begin(); };
		const_iterator	begin() const { return m_tree.begin();};
		iterator		end() { return m_tree.end(); };
		const_iterator	end() const { return m_tree.end(); };
		reverse_iterator rbegin() { return m_tree.rbegin(); };
		const_reverse_iterator rbegin() const {
			return m_tree.rbegin();
		};
		reverse_iterator rend() { return m_tree.rend(); };
		const_reverse_iterator rend() const {
			return m_tree.rend();
		};
		/*Element access------------------------------------------------------*/
		mapped_type & operator[] (const key_type& k) {
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
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
				m_tree.insertValue(*first, (*first).first);
		};
		void erase (iterator position) {
			m_tree.deleteNode(position.base());
		}
		size_type erase(const key_type & key) {
			return m_tree.deleteValue(key);
		};
		void erase (iterator first, iterator last) {
			iterator tmp;
			while (first != last) 
			{
				tmp = first;
				++first;
				erase(tmp);
			}
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
			const_iterator iter = find(k);
			if (iter != end())
				return 1;
			return 0;
		};
		iterator lower_bound(const key_type & k) {
			return m_tree.lower_bound(k);
		};
		const_iterator lower_bound(const key_type & k) const {
			return m_tree.lower_bound(k);
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


	template <class Key, class T, class Compare, class Alloc>
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(),
						rhs.begin());
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end());
	};


	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	};
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	};
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	};
	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& lhs,
                map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	};

}; //<\ft>

#endif
