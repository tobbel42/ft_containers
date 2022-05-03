#include "tree.hpp"
#include "../../inc/utils.hpp"

rbNode::rbNode():
	left(NULL),
	right(NULL),
	parent(NULL),
	color(RED),
	value(0) {};


rbNode::rbNode(rbNode *parent, rb color, int value):
	left(NULL),
	right(NULL),
	parent(parent),
	color(color),
	value(value) {};

rbNode::~rbNode() {
	if (parent)
	{
		if (this == parent->left)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
};

rbTree::rbTree(): m_root(0) {};
rbTree::~rbTree() {};

rbTree::rbTree(const rbTree & cpy) { *this = cpy; };
rbTree &rbTree::operator=(const rbTree & rhs) {
	m_root = 0;
	rbNode *node = leftMost(rhs.getRoot());
	while (node)
	{
		insertValue(node->value);
		node = rhs.next(node);
		std::cout << "hi" << std::endl;
	}
	return *this;
};

rbNode *rbTree::findValue(int value) {
	rbNode	*node = m_root;
	while (node)
	{
		if (node->value == value)
			return node;
		else if (node->value > value)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

void rbTree::insertValue(int value) {
	//1.Rule
	if (!m_root)
	{
		m_root = new rbNode(NULL, BLACK, value);
		return ;
	}

	//2.Rule
	rbNode * newNode = new rbNode(NULL, RED, value);
	//finding and inserting the value
	for (rbNode *node = m_root;;)
	{
		if (value > node->value)
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
		else
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
	}
	//3.Rule
	if (newNode->parent->color == BLACK)
		return ;
	
	//4.Rule
	fixInsert(newNode);

};

void	rbTree::fixInsert(rbNode *newNode) {
	rbNode	*parent = newNode->parent;
	rbNode	*grandparent = parent->parent;
	rbNode	*uncle = getUncle(parent);

	if (uncle && uncle->color == RED) {
		toggleColor(uncle);
		toggleColor(parent);
		if (parent->parent != m_root)
		{
			toggleColor(parent->parent);
			if (!treeCheck(parent->parent->parent))
				fixInsert(parent->parent);
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


void	rbTree::toggleColor(rbNode *node) {
	if (node)
	{
		if (node->color == RED)
			node->color = BLACK;
		else
			node->color = RED;
	}
};

rbNode	*rbTree::getUncle(rbNode *parent) {
	if (parent->parent->left == parent)
		return parent->parent->right;
	return parent->parent->left;
}

void rbTree::printTree() const {
	print("", m_root, false);
};

void rbTree::print(const std::string& prefix, rbNode *x, bool isLeft) const
{
	if (x)
	{
		std::cout << prefix;
		std::cout << (isLeft ? "├──" : "└──");
		std::cout << (x->color == BLACK ? "\033[48;5;0m" : "\033[48;5;9m" ) << x->value << "\033[0m"<< std::endl;
		print(prefix + (isLeft ? "│   " : "    "), x->left, true);
		print(prefix + (isLeft ? "│   " : "    "), x->right, false);
	}
}

rbNode	*rbTree::leftMost(rbNode *node) const {
	if (node)
	{
		while (node->left)
		{
			node = node->left;
		}
	}
	return node;
};

rbNode *rbTree::next(rbNode *node) const {

	if (!node)
		return 0;

	if (node->right)
		return leftMost(node->right);
	
	rbNode * parent = node->parent;

	if (!parent)
		return 0;
	
	if (node == parent->left)
		return parent;
	
	if (node == parent->right)
	{
		while (parent && node != parent->left)
		{
			node = parent;
			parent = node->parent;
		}
	}
	return parent;
};

bool	rbTree::treeCheck() { return treeCheck(m_root); };

bool	rbTree::treeCheck(rbNode *startNode) {
	int blackHeight = 0;
	for (rbNode *node = startNode; node; node = node->left) {
		if (node->color == BLACK)
			++blackHeight;
	}
	return treeCheckHelper(startNode, blackHeight, 0);
};

bool	rbTree::treeCheckHelper(rbNode *node, int blackHeight, int currentHeight){
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


rbNode *rbTree::getRoot() const{
	return m_root;
};

void	rbTree::leftRotate(rbNode *grandParent, rbNode *parent, rbNode *child) {
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
	rbNode *tmp = child->left;
	child->left = parent;
	parent->parent = child;
	parent->right = tmp;
	if (tmp)
		tmp->parent = parent;
};

void	rbTree::rightRotate(rbNode *grandParent, rbNode *parent, rbNode *child) {
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
	rbNode *tmp = child->right;
	child->right = parent;
	parent->parent = child;
	parent->left = tmp;
	if (tmp)
		tmp->parent = parent;
};

void	rbTree::rotate(rbNode *node)
{
	if (node->parent)
	{
		if (node == node->parent->left)
			rightRotate(node->parent->parent, node->parent, node);
		else
			leftRotate(node->parent->parent, node->parent, node);
	}
};


rbNode *rbTree::findSuccessor(rbNode *node) {
	rbNode *successor = node->right;
	while (successor->left)
		successor = successor->left;
	return successor;
};


rbNode	*rbTree::BSTdeletion(rbNode *node) {

	rbNode *next;

	while (node->left || node->right)
	{
		if (node->left && node->right)
			next = findSuccessor(node);
		else if (node->left)
			next = node->left;
		else
			next = node->right;
		//ToDo, allocator.construct ++ allocator destroy
		node->value = next->value;
		node = next;
	}
	return node;
};

void rbTree::deleteValue(int value) {
	rbNode *node = findValue(value);
	if (!node)
		return ;

	node = BSTdeletion(node);

	//Case 1
	if (node->color == RED)
		nodeDelete(node);
	else
		fixDelete(node);

};
void	rbTree::fixDelete(rbNode *delNode) {
	//in this part we know that delNode has a sibling
	bool 	first = true;
	rbNode 	*parent;
	rbNode 	*sibling;
	rbNode 	*farChild;
	rbNode 	*nearChild;

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
}

void	rbTree::nodeDelete(rbNode *delNode) {
	//allocator stuff
	delete delNode;
}