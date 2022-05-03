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

class	rbTree{
	private:
		rbNode	*m_root;

		//rotates the node with his parent
		void	rotate(rbNode *node);
		void	leftRotate(rbNode *grandParent, rbNode *parent, rbNode *child);
		void	rightRotate(rbNode *grandParent, rbNode *parent, rbNode *child);
				
		rbNode	*leftMost(rbNode *node) const;
		rbNode	*findSuccessor(rbNode *node);
		rbNode	*getUncle(rbNode *parent);
		void	toggleColor(rbNode *node);


		void	fixInsert(rbNode *newNode);
		void	fixDelete(rbNode *delNode);
		void	nodeDelete(rbNode *delNode);
		rbNode	*BSTdeletion(rbNode *node);

		void 	print(const std::string& prefix, rbNode *x, bool isLeft) const;
		bool	treeCheck(rbNode *startNode);
		bool	treeCheckHelper(rbNode *node, int blackHeight, int currentHeight);

	public:
		rbTree(void);
		~rbTree();
		rbTree(const rbTree & cpy);
		rbTree	&operator=(const rbTree & rhs);

		rbNode	*getRoot() const;
		rbNode	*findValue(int value);
		rbNode	*next(rbNode *node) const;

		void	insertValue(int value);
		void	deleteValue(int value);
		void	printTree() const;
		bool	treeCheck();
};

