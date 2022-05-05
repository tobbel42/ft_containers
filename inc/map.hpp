#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "iterator.hpp"
#include "rbTree.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft {

	template <class T>
	class map_iterator: public rbTree_iterator<T>
	{
		public:
			typedef T					value_type;
			map_iterator(const rbTree_iterator<value_type> & iter) {
				m_ptr = iter.base();
			};

			value_type	&operator*() { return *m_ptr; }
		private:
			value_type	*m_ptr;
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

			
			typedef typename ft::rbTree<value_type>::node_type
				node_type;
			typedef typename ft::rbTree<value_type>
				tree_type;

			typedef	ft::map_iterator<node_type>					
				iterator;
			typedef ft::map_iterator<const node_type>
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
				return m_tree.insertValue(value);
			}


			void	printTree() { m_tree.printTree(); };


	};

}; //<\ft>

#endif
