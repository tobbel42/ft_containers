#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft
{

	template<typename T>
	class rbTree_iterator
	{
		public:
			typedef iterator<bidirectional_iterator_tag, T> iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type
				difference_type; 
			typedef typename iterator_traits<iterator_type>::value_type
				value_type;
			typedef typename iterator_traits<iterator_type>::pointer
				pointer;
			typedef typename iterator_traits<iterator_type>::reference
				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category
				iterator_category;
		
		private:
		
		pointer	m_ptr;
		
		public:

		rbTree_iterator() : m_ptr(NULL) {};
		rbTree_iterator(pointer ptr) : m_ptr(ptr) {};
		rbTree_iterator(const rbTree_iterator& cpy) {*this = cpy; };

		// template<typename U>
		// rbTree_iterator(const rbTree_iterator<T2>& cpy,
		// 	typename enable_if<std::is_constructible<T, U>::value, T2>::type*
		// 		= NULL) : m_ptr(cpy.base()) {};

		~rbTree_iterator() {};
		pointer	base() const {return m_ptr;};

		rbTree_iterator&	operator=(const rbTree_iterator & rhs) {
			m_ptr = rhs.base();
			return *this;
		};
		reference	operator*() const {return m_ptr->value;};

		void next() {
			if (m_ptr)
			{
				if (m_ptr->right)
				{
					m_ptr = m_ptr->right;
					while (m_ptr->left)
						m_ptr = m_ptr->left;
				}
				else if (!m_ptr->parent)
					m_ptr = NULL;
				else if (m_ptr == m_ptr->parent->left)
					m_ptr = m_ptr->parent;
				else if (m_ptr == m_ptr->parent->right)
				{
					while (m_ptr->parent && m_ptr != m_ptr->parent->left)
						m_ptr = m_ptr->parent;
					m_ptr = m_ptr->parent;
				}
			}	
		};

		void prev() {
			if (m_ptr)
			{
				if (m_ptr->left)
				{
					m_ptr = m_ptr->left;
					while (m_ptr->right)
						m_ptr = m_ptr->right;
				}
				else if (!m_ptr->parent)
					m_ptr = NULL;
				else if (m_ptr == m_ptr->parent->right)
					m_ptr = m_ptr->parent;
				else if (m_ptr == m_ptr->parent->left)
				{
					while (m_ptr->parent && m_ptr != m_ptr->parent->right)
						m_ptr = m_ptr->parent;
					m_ptr = m_ptr->parent;
				}
			}	
		};
	};

	enum rb {RED, BLACK};

	template<class T >
	class rbNode {
		public: // TODO fix
			typedef T		value_type;

			rbNode	*left;
			rbNode	*right;
			rbNode	*parent;
			rb		color;
			T		m_value;
			rbNode():
				left(NULL),
				right(NULL),
				parent(NULL),
				color(RED) {};
			~rbNode() {
				if (parent)
				{
					if (this == parent->left)
						parent->left = NULL;
					else
						parent->right = NULL;
				}
			};
	};


	template< class T, class K, class Compare = ft::less<K>,
		class valueAlloc = std::allocator<T>,
		class nodeAlloc = std::allocator< ft::rbNode<T> > >
	class rbTree {
		public:

		typedef T											value_type;
		typedef K											key_type;
		typedef valueAlloc									value_allocator_type;
		typedef nodeAlloc									node_allocator_type;
		typedef Compare										compare_type;

		typedef typename value_allocator_type::reference		reference;
		typedef typename value_allocator_type::const_reference	const_reference;
		typedef typename value_allocator_type::pointer			pointer;
		typedef typename value_allocator_type::const_pointer	const_pointer;

		typedef class rbNode<value_type>					node_type;
		typedef class rbNode<const value_type>				const_node_type;
		typedef rbTree_iterator<node_type>					iterator;
		typedef rbTree_iterator<const_node_type>			const_iterator;

		typedef class ft::reverse_iterator<iterator>	   reverse_iterator;
		typedef class ft::reverse_iterator<const_iterator> const_reverse_iterator;
		private:

			node_type	*m_root;
			Compare		m_less;
			valueAlloc	m_value_allocator;
			nodeAlloc	m_node_allocator;

		public:
			rbTree(const compare_type & compare = compare_type(),
				const value_allocator_type & v = value_allocator_type(),
				const node_allocator_type & n = node_allocator_type()):
				m_root(NULL),
				m_less(compare),
				m_value_allocator(v),
				m_node_allocator(n) {};
			~rbTree() {/*TODO*/};
			rbTree(const rbTree & cpy) { *this = cpy; };
			rbTree	&operator=(const rbTree & rhs) {
				m_root = NULL;
				node_type *node = leftMost(rhs.getRoot());
				while (node)
				{
					insertValue(node->value);
					node = rhs.next(node);
				}
				return *this;
			};

			iterator getRoot() const { return iterator(m_root);};
			iterator findValue(const value_type & value) {
				node_type	*node = m_root;

				while (node)
				{
					if (m_less(node->m_value, value))
						node = node->right;
					else if (m_less(value, node->m_value))
						node = node->left;
					else
						return iterator(node);
				}
				return iterator(NULL);
			};

			node_type	*createNode(const value_type & value) {
				node_type	*newNode = m_node_allocator.allocate(1);
				m_node_allocator.construct(newNode, node_type());
				m_value_allocator.construct(&newNode->m_value, value);
				return newNode;
			}

			//inserts the value in the tree
			iterator	insertValue(const value_type &value) {
				iterator	iter = findValue(value);
				if (iter.base())
					return iter;
				
				//2.Rule
				if (!m_root)
				{
					m_root = createNode(value);
					m_root->color = BLACK;
					return getRoot();
				}

				node_type	*newNode = createNode(value);
				//inserting the value
				for (node_type *node = m_root;;)
				{
					if (m_less(value, node->m_value))
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

				//3.Rule
				if (newNode->parent->color != BLACK)
					fixInsert(newNode);

				return iterator(newNode);
			};

			node_type	*BSTdeletion(node_type *node) {
			
				node_type *next;

				while (node->left || node->right)
				{
					if (node->left && node->right)
						next = findSuccessor(node);
					else if (node->left)
						next = node->left;
					else
						next = node->right;
					//ToDo, allocator.construct ++ allocator destroy
					m_value_allocator.destroy(&node->m_value);
					m_value_allocator.construct(&node->m_value, next->m_value);
					node = next;
				}
				return node;
			};

			void	nodeDelete(node_type *delNode) {
				m_value_allocator.destroy(&delNode->m_value);
				m_node_allocator.destroy(delNode);
				m_node_allocator.deallocate(delNode, 1);
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
							nodeDelete(delNode);
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
							ft::swap(sibling->color, parent->color);
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
									nodeDelete(delNode);
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
									ft::swap(sibling->color, nearChild->color);
									rotate(nearChild);
									farChild = sibling;
									sibling = nearChild;
								}
								ft::swap(parent->color, sibling->color);
								rotate(sibling);
								farChild->color = BLACK;
								if (first)
								{
									nodeDelete(delNode);
									first = false;
								}
								delNode = NULL;
							}
						}
					}
				}
			};

			size_t	deleteValue(const value_type & value) {
					node_type *node = findValue(value).base();
					if (!node)
						return 0;

					node = BSTdeletion(node);

					//Case 1
					if (node->color == RED)
						nodeDelete(node);
					else
						fixDelete(node);
					return 1;
			};


			iterator	begin() const {
				node_type *node = m_root;
				while (node->left)
					node = node->left;
				return iterator(node);
			};

			bool	treeCheck(node_type *startNode) {
				int blackHeight = 0;
				for (node_type *node = startNode; node; node = node->left)
				{
					if (node->color == BLACK)
						++blackHeight;
				}
				return treeCheckHelper(startNode, blackHeight, 0);
			};

		private:

			node_type *findSuccessor(node_type *node) {
				node_type *successor = node->right;
				while (successor->left)
					successor = successor->left;
				return successor;
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


			bool	treeCheckHelper(node_type *node, int blackHeight, int currentHeight){
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

			void	leftRotate(node_type *grandParent, node_type *parent, node_type *child) {
				if (grandParent)
				{
					if (grandParent->left == parent)
						grandParent->left = child;
					else
						grandParent->right = child;
				}
				else
					m_root = child;
				child->parent = grandParent;
				node_type *tmp = child->left;
				child->left = parent;
				parent->parent = child;
				parent->right = tmp;
				if (tmp)
					tmp->parent = parent;
			};

			void	rightRotate(node_type *grandParent, node_type *parent, node_type *child) {
				if (grandParent)
				{
					if (grandParent->left == parent)
						grandParent->left = child;
					else
						grandParent->right = child;
				}
				else
					m_root = child;
				child->parent = grandParent;
				node_type *tmp = child->right;
				child->right = parent;
				parent->parent = child;
				parent->left = tmp;
				if (tmp)
					tmp->parent = parent;
			};

			void	rotate(node_type *node)
			{
				if (node->parent)
				{
					if (node == node->parent->left)
						rightRotate(node->parent->parent, node->parent, node);
					else
						leftRotate(node->parent->parent, node->parent, node);
				}
			};	

			void	fixInsert(node_type *newNode) {
				node_type	*parent = newNode->parent;
				node_type	*grandparent = parent->parent;
				node_type	*uncle = getUncle(parent);

				if (uncle && uncle->color == RED) {
					toggleColor(uncle);
					toggleColor(parent);
					if (grandparent != m_root)
					{
						toggleColor(grandparent);
						if (!treeCheck(grandparent->parent))
							fixInsert(grandparent);
					}
				}
				else
				{
					if (!((newNode == parent->left && parent == grandparent->left) ||
						(newNode == parent->right && parent == grandparent->right)))
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

		public:
			void printTree() const {
				print("", m_root, false);
			};

			void print(const std::string & prefix, node_type *node, bool isLeft) const
			{
				if (node)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──");
					std::cout << 
						(node->color == BLACK ? "\033[48;5;0m" : "\033[48;5;9m")
						<< node->m_value << "\033[0m"<< std::endl;
					print(prefix + (isLeft ? "│   " : "    "), node->left, true);
					print(prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}
			// node_type	*leftMost(node_type *node) const {
			// 	if (node)
			// 	{
			// 		while (node->left)
			// 			node = node->left;
			// 	}
			// 	return node;
			// };
		// 	void	rotate(rbNode *node);
		// 	void	leftRotate(rbNode *grandParent, rbNode *parent, rbNode *child);
		// 	void	rightRotate(rbNode *grandParent, rbNode *parent, rbNode *child);
					
		// 	rbNode	*findSuccessor(rbNode *node);
		// 	rbNode	*getUncle(rbNode *parent);
		// 	void	toggleColor(rbNode *node);
	
	
		// 	void	fixDelete(rbNode *delNode);
		// 	void	nodeDelete(rbNode *delNode);
		// 	rbNode	*BSTdeletion(rbNode *node);
	
		// 	void 	print(const std::string& prefix, rbNode *x, bool isLeft) const;
		// 	bool	treeCheck(rbNode *startNode);
		// 	bool	treeCheckHelper(rbNode *node, int blackHeight, int currentHeight);
	};	

}; // namespace ft


#endif