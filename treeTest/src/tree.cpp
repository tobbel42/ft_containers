#include "tree.hpp"

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

void rbTree::insertValue(int value) {
	//1.Rule
	if (!m_root)
	{
		m_root = new rbNode(NULL, BLACK, value);
		return ;
	}

	//finding and inserting the value
	rbNode * newNode = new rbNode(NULL, RED, value);
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

	//2.Rule
	if (newNode->parent->color == BLACK)
		return ;
};

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

rbNode::~rbNode() {};

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