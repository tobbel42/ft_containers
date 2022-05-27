#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft
{
	template<typename T, typename container, typename value>
	class binary_tree_iterator {
		public:
		/*Typdefs-------------------------------------------------------------*/
		typedef T				node_type;

		typedef	value			value_type;
		typedef value_type&		reference;
		typedef value_type*		pointer;
		typedef ptrdiff_t		difference_type;

		typedef typename ft::bidirectional_iterator_tag	iterator_category;
	
		private:
		/*MemberVariabels-----------------------------------------------------*/
		node_type	m_current;

		public:
		
		/*Constructors--------------------------------------------------------*/
		binary_tree_iterator():
			m_current() {};
		binary_tree_iterator(node_type const & other):
			m_current(other) {};
		binary_tree_iterator(const binary_tree_iterator<
			typename container::node_type *, container,
			typename container::value_type> & other):
			m_current(other.base()) {};

		/*Getters-------------------------------------------------------------*/
		const node_type &base() const { return m_current; };
		node_type &base() { return m_current; };

		/*Operators-----------------------------------------------------------*/
		binary_tree_iterator & operator++() { next(); return *this; };
		binary_tree_iterator operator++(int) {
			binary_tree_iterator tmp = *this;
			next();
			return tmp;
		};
		binary_tree_iterator & operator--() { prev(); return *this; };
		binary_tree_iterator operator--(int) {
			binary_tree_iterator tmp = *this;
			prev();
			return tmp;
		};
		reference operator*() { return m_current->m_value; };
		reference operator*() const { return m_current->m_value; };
		pointer operator->() { return &m_current->m_value; };
		pointer operator->() const { return &m_current->m_value; };
		bool operator==(binary_tree_iterator &other) const {
			return m_current == other.m_current;
		};
		bool operator!=(binary_tree_iterator &other) const {
			return m_current != other.m_current;
		};
		private:
		/*Helper--------------------------------------------------------------*/
		void next() {
			if (m_current)
			{
				if (m_current->right)
				{
					m_current = m_current->right;
					while (m_current->left)
						m_current = m_current->left;
				}
				else if (!m_current->parent)
					m_current = NULL;
				else if (m_current == m_current->parent->left)
					m_current = m_current->parent;
				else if (m_current == m_current->parent->right)
				{
					while (m_current->parent 
						&& m_current != m_current->parent->left)
						m_current = m_current->parent;
					m_current = m_current->parent;
				}
			}
		};
		void prev() {
			if (m_current)
			{
				if (m_current->left)
				{
					m_current = m_current->left;
					while (m_current->right)
						m_current = m_current->right;
				}
				else if (!m_current->parent)
					m_current = NULL;
				else if (m_current == m_current->parent->right)
					m_current = m_current->parent;
				else if (m_current == m_current->parent->left)
				{
					while (m_current->parent
						&& m_current != m_current->parent->right)
						m_current = m_current->parent;
					m_current = m_current->parent;
				}
			}	
		};
	};

	template <class T1, class T2, class container, class V1, class V2>
	bool operator==(const binary_tree_iterator<T1, container, V1> & rhs,
					const binary_tree_iterator<T2, container, V2> & lhs) {
	return (void *)rhs.base() == (void *)lhs.base();				
	};

	template <class T1, class T2, class container, class V1, class V2>
	bool operator!=(const binary_tree_iterator<T1, container, V1> & rhs,
					const binary_tree_iterator<T2, container, V2> & lhs) {
	return rhs.base() != lhs.base();				
	};


	enum eRB {RED, BLACK};

	template<class T >
	struct rbNode {
		public:
			typedef T			value_type;
			typedef	rbNode*		node_pointer;
			typedef eRB			color_type;
			node_pointer		left;
			node_pointer		right;
			node_pointer		parent;
			color_type			color;
			value_type			m_value;
	};


	template< class T, class Compare = std::less<T>,
		class Allocator = std::allocator<T> >
	class rbTree {
		public:
		/*--------------------------------------------------------------------*/
		/*Typedefs------------------------------------------------------------*/
		typedef T										value_type;
		typedef Compare									compare_type;
		typedef Allocator								allocator_type;
		typedef allocator_type							value_allocator_type;
		typedef typename Allocator::template rebind<rbNode<value_type> >::other
														node_allocator_type;

		typedef typename value_allocator_type::reference		reference;
		typedef typename value_allocator_type::const_reference	const_reference;
		typedef typename value_allocator_type::pointer			pointer;
		typedef typename value_allocator_type::const_pointer	const_pointer;

		typedef rbNode<value_type>					node_type;
		typedef rbNode<const value_type>				const_node_type;

		typedef binary_tree_iterator<node_type *, rbTree, value_type>
															iterator;
		typedef binary_tree_iterator<const node_type *, rbTree, const value_type>
															const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		typedef	typename node_allocator_type::size_type			size_type;
		typedef	typename node_allocator_type::difference_type	difference_type;

		private:

		/*MemberVariabeles----------------------------------------------------*/
		node_type				*m_root;
		node_type				m_loopback;
		compare_type			m_comp;
		value_allocator_type	m_value_allocator;
		node_allocator_type		m_node_allocator;
		size_type				m_size;

		public:

		/*Constructors--------------------------------------------------------*/
		rbTree(const compare_type & compare = compare_type(),
			const value_allocator_type & v = value_allocator_type(),
			const node_allocator_type & n = node_allocator_type()):
			m_root(NULL),
			m_comp(compare),
			m_value_allocator(v),
			m_node_allocator(n),
			m_size(0) {
				m_loopback.left = &m_loopback;
			};
		rbTree(const rbTree & cpy):
			m_comp(cpy.m_comp) { *this = cpy; };
		//maby iterator based overhaul
		rbTree	&operator=(const rbTree & rhs) {
			clearTree();
			for(iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
				insertValue(*iter, (*iter).first);
			return *this;
		};

		/*Destructors---------------------------------------------------------*/
		~rbTree() { clearTree(); };

		/*Capacity------------------------------------------------------------*/
		size_type	size() const { return m_size; };
		size_type	max_size() const { return m_node_allocator.max_size(); };
		bool		empty() const { return ((m_size == 0)?true:false); };

		/*Iterators-----------------------------------------------------------*/
		iterator	begin() { return iterator(mostLeft(m_loopback.left)); };
		const_iterator	begin() const {
			return const_iterator(mostLeft(m_loopback.left));
		};
		iterator	end() { return iterator(&m_loopback); };
		const_iterator	end() const {
			return const_iterator(&m_loopback);
		};
		reverse_iterator	rbegin() { return reverse_iterator(end()); };
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		};
		reverse_iterator	rend() { return reverse_iterator(begin()); };
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		};
	
		/*Getter--------------------------------------------------------------*/
		iterator getRoot() { return iterator(m_root); };
		iterator getLoopback(){ return iterator(&m_loopback); };

		/*Operations----------------------------------------------------------*/
		template<class _Key>
		iterator findValue(const _Key & key) {
			node_type	*node = m_root;
			while (node)
			{
				if (m_comp(node->m_value, key))
					node = node->right;
				else if (m_comp(key, node->m_value))
					node = node->left;
				else
					return iterator(node);
			}
			return iterator(end());
		};
		template<class _Key>
		const_iterator findValue(const _Key & key) const {
			node_type	*node = m_root;
			while (node)
			{
				if (m_comp(node->m_value, key))
					node = node->right;
				else if (m_comp(key, node->m_value))
					node = node->left;
				else
					return const_iterator(node);
			}
			return const_iterator(end());
		};
		template<class _Key>
		iterator	lower_bound(const _Key& k) {
			iterator iter = begin();
			while (iter != end() && m_comp(iter.base()->m_value, k))
				++iter;
			return iter;
		};
		template<class _Key>
		const_iterator	lower_bound(const _Key& k) const {
			const_iterator iter = begin();
			while (iter != end() && m_comp(iter.base()->m_value, k))
				++iter;
			return iter;
		};
		template<class _Key>
		iterator	upper_bound(const _Key & k) {
			iterator iter = begin();
			while (iter != end() && !m_comp(k, iter.base()->m_value))
				++iter;
			return (iter);
			
		};
		template<class _Key>
		const_iterator	upper_bound(const _Key & k) const {
			const_iterator iter = begin();
			while (iter != end() && !m_comp(k, iter.base()->m_value))
				++iter;
			return (iter);
			
		};		
		template<class _Key>
		ft::pair<iterator, iterator> equal_range (const _Key& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		};

		/*Modifiers-----------------------------------------------------------*/
		//inserts the value in the tree
		template<class _Key>
		ft::pair<iterator, bool> insertValue(const value_type &value,
											const _Key &key) {
			iterator	iter = findValue(key);
			if (iter.base() != &m_loopback)
				return ft::make_pair(iter, false);
			
			//2.Rule
			if (!m_root)
			{
				m_root = createNode(value);
				m_root->color = BLACK;
				m_root->parent = &m_loopback;
				m_loopback.left = m_root;
				++m_size;
				return ft::make_pair(getRoot(), true);
			}
			node_type	*newNode = createNode(value);
			//inserting the value
			for (node_type *node = m_root;;)
			{
				if (m_comp(value, node->m_value))
				{
					if (node->left)
						node = node->left;
					else
					{
						node->left = newNode;
						newNode->parent = node;
						break;
					}
				}
				else
				{
					if (node->right)
						node = node->right;
					else
					{
						node->right = newNode;
						newNode->parent = node;
						break;
					}
				}
			}
			++m_size;
			//3.Rule
			if (newNode->parent->color != BLACK)
				fixInsert(newNode);
			return ft::make_pair(iterator(newNode), true);
		};
		//TODO fix with feedback
		void swap(rbTree & tree) {
			std::swap(m_loopback.left, tree.m_loopback.left);
			std::swap(m_root, tree.m_root);
			std::swap(m_size, tree.m_size);
			m_root->parent = &m_loopback;
			tree.m_root->parent = &tree.m_loopback;
		};
		template <class _Key>
		size_type	deleteValue(const _Key & key) {
			node_type *node = findValue(key).base();
			if (!node || node == &m_loopback)
				return 0;
			deleteNode(node);
			return 1;
		};
		void	deleteNode(node_type *node) {
			node = BSTdeletion(node);
			//Case 1
			if (node->color == RED)
			{
				removeNode(node);
			}
			else
				fixDelete(node);
			--m_size;
		}
		void clearTree() {
			if (m_root)
			{
				clearTreeHelper(m_root);
				m_root = NULL;
				m_loopback.left = &m_loopback;
			}
			m_size = 0;
		};

		/*Utils---------------------------------------------------------------*/
		bool	treeCheck(node_type *startNode) {
			int blackHeight = 0;
			for (node_type *node = startNode; node; node = node->left)
			{
				if (node->color == BLACK)
					++blackHeight;
			}
			return treeCheckHelper(startNode, blackHeight, 0);
		};
		void printTree() const {
			printNode("", m_root, false);
		};

		private:
		/*Utils---------------------------------------------------------------*/
		node_type	*mostLeft(node_type *node) const {
			while (node && node->left && node != &m_loopback)
				node = node->left;
			return (node);
		};
		node_type	*mostRight(node_type *node) const {
			while (node && node->right && node != m_loopback)
				node = node->right;
			return (node);
		};
		node_type *findSuccessor(node_type *node) const {
			node_type *successor = node->right;
			while (successor->left)
				successor = successor->left;
			return successor;
		};
		void clearTreeHelper(node_type * node) {
			if (node->left)
				clearTreeHelper(node->left);
			if (node->right)
				clearTreeHelper(node->right);
			removeNode(node);
		};
		bool	treeCheckHelper(node_type *node, int blackHeight,
								int currentHeight) {
			if (!node)
				return true;
			if (node->color == BLACK)
				++currentHeight;
			if (node->left)
			{
				if (!treeCheckHelper(node->left, blackHeight, currentHeight))
					return false;
				if (node->color == RED && node->left->color == RED)
					return false;
			}
			else
			{
				if (currentHeight != blackHeight)
					return false;
			}
			if (node->right)
			{
				if (!treeCheckHelper(node->right, blackHeight, currentHeight))
					return false;
				if (node->color == RED && node->right->color == RED)
					return false;
			}
			else
			{
				if (currentHeight != blackHeight)
					return false;
			}
			return true;
		};

		void printNode(const std::string & prefix, node_type *node, bool isLeft)
		const {
			if (node)
			{
				std::cout << prefix << (isLeft ? "├──" : "└──") << 
					(node->color == BLACK ? "\033[48;5;0m" : "\033[48;5;9m")
					<< node->m_value << "\033[0m"<< std::endl;
				printNode(prefix + (isLeft ? "│   " : "    "),
					node->left, true);
				printNode(prefix + (isLeft ? "│   " : "    "),
					node->right, false);
			}
		}
		//check
		node_type	*createNode(const value_type & value) {
			node_type	*newNode = m_node_allocator.allocate(1);
			newNode->color = RED;
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->parent = NULL;
			m_value_allocator.construct(&newNode->m_value, value);
			return newNode;
		};
		//check
		void	removeNode(node_type *delNode) {
			if (delNode == m_root)
			{
				m_loopback.left = &m_loopback;
			}
			else
			{
				if (delNode->parent->left == delNode)
					delNode->parent->left = NULL;
				else if (delNode->parent->right == delNode)
					delNode->parent->right = NULL;
			};
			m_value_allocator.destroy(&(delNode->m_value));
			m_node_allocator.deallocate(delNode, 1);
		};
		node_type	*BSTdeletion(node_type *node) {
			node_type *next;
			while (node->left || node->right)
			{
				if (node == &m_loopback)
					break;
				if (node->left && node->right)
					next = findSuccessor(node);
				else if (node->left)
					next = node->left;
				else
					next = node->right;
				
				//node swap, maybe own fkt
				if (node == m_root)
					m_root = next;
				std::swap(next->color, node->color);
				if (node->right)
					node->right->parent = next;
				if (next->right)
					next->right->parent = node;
				if (node->left)
					node->left->parent = next;
				if (next->left)
					next->left->parent = node;
				std::swap(next->right, node->right);
				std::swap(next->left, node->left);
				if (node->parent->left == node)
					node->parent->left = next;
				else if (node->parent->right == node)
					node->parent->right = next;
				if (next->parent->left == next)
					next->parent->left = node;
				else if (next->parent->right == next)
					next->parent->right = node;
				std::swap(next->parent, node->parent);
			}
			return node;
		};
		node_type *getUncle(node_type *node) {
			if (node->parent)
			{
				if (node->parent->left == node)
					return (node->parent->right);
				else
					return (node->parent->left);
			}
			return NULL;
		};
		void	toggleColor(node_type *node) {
			if (node)
			{
				if (node->color == RED)
					node->color = BLACK;
				else
					node->color = RED;
			}
		};

		/*Rotations-----------------------------------------------------------*/
		void	rotate(node_type *node) {
			if (node->parent)
			{
				if (node == node->parent->left)
					rightRotate(node->parent->parent, node->parent, node);
				else
					leftRotate(node->parent->parent, node->parent, node);
			}
		};
		void	rightRotate(node_type *grandParent, node_type *parent,
							node_type *child) {
			if (grandParent != &m_loopback)
			{
				if (grandParent->left == parent)
					grandParent->left = child;
				else
					grandParent->right = child;
			}
			else
			{
				m_root = child;
				m_loopback.left = m_root;
			}
			child->parent = grandParent;
			node_type *tmp = child->right;
			child->right = parent;
			parent->parent = child;
			parent->left = tmp;
			if (tmp)
				tmp->parent = parent;
		};
		void	leftRotate(node_type *grandParent, node_type *parent,
							node_type *child) {
			if (grandParent != &m_loopback)
			{
				if (grandParent->left == parent)
					grandParent->left = child;
				else
					grandParent->right = child;
			}
			else
			{
				m_root = child;
				m_loopback.left = m_root;
			}
			child->parent = grandParent;
			node_type *tmp = child->left;
			child->left = parent;
			parent->parent = child;
			parent->right = tmp;
			if (tmp)
				tmp->parent = parent;
		};

		/*TreeFixes-----------------------------------------------------------*/
		void	fixInsert(node_type *newNode) {
			node_type	*parent = newNode->parent;
			node_type	*grandparent = parent->parent;
			node_type	*uncle = getUncle(parent);
			if (!grandparent || grandparent == &m_loopback)
				return ;
			if (uncle && uncle->color == RED) {
				toggleColor(uncle);
				toggleColor(parent);
				if (grandparent != m_root)
				{
					toggleColor(grandparent);
					if (!treeCheck(grandparent->parent))
					{
						fixInsert(grandparent);
					}
				}
			}
			else
			{
				if (!((newNode == parent->left && parent == grandparent->left)
				 || (newNode == parent->right && parent == grandparent->right)))
				{
					rotate(newNode);
					rotate(newNode);
					toggleColor(newNode);
					toggleColor(grandparent);
				}
				else
				{
					rotate(newNode->parent);
					toggleColor(parent);
					toggleColor(grandparent);
				}
			}
		};
		void	fixDelete(node_type *delNode) {
			//in this part we know that delNode has a sibling
			bool first = true;
			node_type *parent;
			node_type *sibling;
			node_type *farChild;
			node_type *nearChild;
			while (delNode)
			{
				//case 2
				if (delNode == m_root)
				{
					if (first)
					{
						m_root = NULL;
						m_loopback.left = &m_loopback;
						removeNode(delNode);
						first = false;
					}
					delNode = NULL;
				}
				else
				{
					parent = delNode->parent;
					if (parent->left == delNode)
					{
						sibling = parent->right;
						nearChild = sibling->left;
						farChild = sibling->right;
					}
					else
					{
						sibling = parent->left;
						nearChild = sibling->right;
						farChild = sibling->left;
					}
					//case 4
					if (sibling && sibling->color == RED)
					{
						std::swap(sibling->color, parent->color);
						rotate(sibling);

					}
					else
					{
						//case 3
						if ((!farChild || farChild->color == BLACK) &&
							(!nearChild || nearChild->color == BLACK))
						{
							if (first)
							{
								removeNode(delNode);
								first = false;
							}
							sibling->color = RED;
							if (parent->color == RED)
							{
								parent->color = BLACK;
								delNode = NULL;
							}
							else
								delNode = parent;

						}
						//Case 5 & 6
						else
						{
	
							if (nearChild && nearChild->color == RED)
							{
								std::swap(sibling->color, nearChild->color);
								rotate(nearChild);
								farChild = sibling;
								sibling = nearChild;
							}
							std::swap(parent->color, sibling->color);
							rotate(sibling);
							farChild->color = BLACK;
							if (first)
							{
								removeNode(delNode);
								first = false;
							}
							delNode = NULL;
						}
					}
				}
			}
		};
	};	
}; // namespace ft


#endif