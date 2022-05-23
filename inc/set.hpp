#ifndef SET_HPP
#define SET_HPP

#include <memory>


#include "iterator.hpp"
#include "rbTree.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft {
	template <class T, class Compare = std::less<T>,
		class Alloc = std::allocator<T> >
	class set {
		/*Typedefs------------------------------------------------------------*/
		public:

		typedef T									key_type;
		typedef T									value_type;
		typedef	Compare								key_compare;
		typedef Compare								value_compare;
		typedef	Alloc								allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;

		typedef typename ft::rbTree<value_type, key_compare, allocator_type>
																tree_type;
		typedef typename tree_type::node_type				node_type;
		typedef typename tree_type::const_iterator			iterator;
		typedef typename tree_type::const_reverse_iterator 	reverse_iterator;
		typedef typename tree_type::const_iterator			const_iterator;
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
		explicit set(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()):
			m_allocator(alloc),
			m_compare(comp) {};
		template <class InputIterator>
		set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type & alloc = allocator_type()):
			m_allocator(alloc),
			m_compare(comp) {
				for (; first != last; ++first)
					m_tree.insertValue(*first, *first);
		};
		set (const set & x):
			m_allocator(x.get_allocator()),
			m_compare(x.key_comp()) { *this = x; };
		set & operator=(const set & rhs){
			m_tree.clearTree();
			for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
				m_tree.insertValue(*iter, *iter);
			return *this;
		};
		iterator getLoopback() { return m_tree.getLoopback(); };
		iterator getRoot() { return m_tree.getRoot(); };
		/*destructor----------------------------------------------------------*/
		~set() { clear(); };

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
		/*Capacity------------------------------------------------------------*/
		bool		empty() const { return !m_tree.size(); };
		size_type 	size() const { return m_tree.size(); };
		size_type	max_size() const { return m_tree.max_size(); };

		/*Modifiers-----------------------------------------------------------*/
		iterator insert (iterator position, const value_type& val) {
			return m_tree.insertValue(val, val).first;
			(void)position;
		};
		ft::pair<iterator, bool> insert(const value_type & value) {
			return m_tree.insertValue(value, value);
		};
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				m_tree.insertValue(*first, *first);
		};
		void erase (iterator position) { // dirty hack pls remove
			m_tree.deleteNode((rbNode<T> *)((void *)position.base()));
		};
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
		void swap(set & x) {
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
		//need overhaul, infinity on empty set
		void	printTree() { m_tree.printTree(); };

		/*Allocator-----------------------------------------------------------*/
		allocator_type get_allocator() const { return m_allocator; };

	};

	/*NonMemberOperators------------------------------------------------------*/
	template <class T, class Compare, class Alloc>
  	bool operator== ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(),
						rhs.begin());
	};
	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	};
	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end());
	};
	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	};
	template <class T, class Compare, class Alloc>
  	bool operator>  ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	};
	template <class T, class Compare, class Alloc>
  	bool operator>= ( const set<T,Compare,Alloc>& lhs,
                    const set<T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	};

}; //<\ft>

#endif
