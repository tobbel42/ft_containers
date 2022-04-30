#pragma once

#include <iostream>
#include <vector>

enum	rb{
	RED,
	BLACK
};

class rbNode {
	public:
		rbNode	*left;
		rbNode	*right;
		rbNode	*parent;
		rb		color;
		int		value;
	
		rbNode(void);
		~rbNode();
		rbNode(rbNode *parent, rb color, int value);
};

struct rbDia {
	rbNode	*child;
	rbNode	*parent;
	rbNode	*grandparent;
	rbNode	*uncle;
};

class	rbTree{
	public:
		rbNode	*m_root;

		bool	treeCheck();
		bool	treeCheck(rbNode *startNode);
		bool	treeCheckHelper(rbNode *node, int blackHeight, int currentHeight);

	public:
		rbTree(void);
		~rbTree();
		rbTree(const rbTree & cpy);
		rbTree	&operator=(const rbTree & rhs);

		rbNode	*getRoot() const;

		void	insertValue(int val);
		void	printTree() const;


		rbNode	*leftMost(rbNode *node) const;
		rbNode	*next(rbNode *node) const;



		//rotates the node with his parent
		void	rotate(rbNode *node);

	private:
		void print(const std::string& prefix, rbNode *x, bool isLeft) const;

		void	leftRotate(rbNode *grandParent, rbNode *parent, rbNode *child);
		void	rightRotate(rbNode *grandParent, rbNode *parent, rbNode *child);

};

