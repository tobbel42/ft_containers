#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "iterator.hpp"
#include "rbTree.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft {

	template <class T, class node = ft::rbNode<T> >
	class map_iterator: public rbTree_iterator<node>
	{
		public:
			typedef T					value_type;
			typedef	node				node_type;
			map_iterator(const rbTree_iterator<node_type> & iter) {
				m_ptr = iter.base();
			};

			value_type	&operator*() const { return m_ptr->m_value; }
		private:
			node_type	*m_ptr;
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

			struct map_less : std::binary_function <value_type, value_type, bool> {
				bool operator() (const value_type& x, const value_type& y) const {
					Compare f;
					return f(x.first, y.first);
				};
				bool operator() (const value_type& x, const key_type& y) const {
					Compare f;
					return f(x.first, y);
				};
				bool operator() (const key_type& x, const value_type& y) const {
					Compare f;
					return f(x, y.first);
				};
			};
			
			typedef typename ft::rbTree<value_type, key_type, map_less>
				tree_type;
			typedef typename tree_type::node_type
				node_type;

			typedef	ft::map_iterator<value_type>		
				iterator;
			typedef ft::map_iterator<const value_type>
				const_iterator;
			typedef class ft::reverse_iterator<iterator>
				reverse_iterator;
			typedef class ft::reverse_iterator<const_iterator>
				const_reverse_iterator;

		private:

			tree_type	m_tree;

			

		public:
			map() {};
			~map() {};

			iterator	begin() const { return iterator(m_tree.begin()); };

			iterator	insert(const value_type & value) {
				return m_tree.insertValue(value, value.first);
			};

			size_t		erase(const key_type & key) {
				return m_tree.deleteValue(key);
			};

			iterator	findValue(const key_type & key) {
				return m_tree.findValue(key);
			};

			void	printTree() { m_tree.printTree(); };


	};

}; //<\ft>

#endif
