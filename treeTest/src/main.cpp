#include "tree.hpp"


int main(){
	rbTree	tree;


	// tree.m_root = new rbNode(NULL, BLACK, 10);
	// tree.m_root->left = new rbNode(tree.m_root, BLACK, 7);
	// tree.m_root->right = new rbNode(tree.m_root, RED, 16);

	// tree.m_root->right->right = new rbNode(tree.m_root->right, BLACK, 18);
	// tree.m_root->right->left = new rbNode(tree.m_root->right, BLACK, 15);

	// tree.m_root->right->right->right = new rbNode(tree.m_root->right->right, RED, 30);
	// tree.m_root->right->right->right->left = new rbNode(tree.m_root->right->right->right, RED, 25);

	// tree.print("", tree.m_root, false);

	// tree.m_root->right->right->color = RED;
	// tree.m_root->right->right->right->left->color = BLACK;
	// tree.rotate(tree.m_root->right->right->right->left);
	// tree.print("", tree.m_root, false);
	// tree.rotate(tree.m_root->right->right->right);
	// tree.print("", tree.m_root, false);
	// tree.rotate(tree.m_root->right);
	// tree.m_root->color = BLACK;
	// tree.m_root->left->color = RED;
	// tree.print("", tree.m_root, false);


	// std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	// std::cout << "Tree valid: " << (tree.treeCheck(tree.m_root->left)?"yes":"no") << std::endl;
	// std::cout << "Tree valid: " << (tree.treeCheck(tree.m_root->right)?"yes":"no") << std::endl;

	tree.insertValue(10);
	tree.printTree();
	std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	tree.insertValue(18);
	tree.printTree();
	std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	tree.insertValue(7);
	tree.printTree();
	std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;

	return 0;
}