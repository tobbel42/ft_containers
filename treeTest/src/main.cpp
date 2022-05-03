#include "tree.hpp"


int main(){
	rbTree	tree;


	// tree.m_root = new rbNode(NULL, BLACK, 50);
	// tree.m_root->left = new rbNode(tree.m_root, BLACK, 30);
	// tree.m_root->left->left = new rbNode(tree.m_root->left, BLACK, 15);
	// tree.m_root->left->right = new rbNode(tree.m_root->left, BLACK, 35);

	// tree.m_root->right = new rbNode(tree.m_root, BLACK, 65);

	// tree.m_root->right->left = new rbNode(tree.m_root->right, BLACK, 55);
	// tree.m_root->right->right = new rbNode(tree.m_root->right, RED, 70);

	// tree.m_root->right->right->left = new rbNode(tree.m_root->right->right, BLACK, 68);
	// tree.m_root->right->right->right = new rbNode(tree.m_root->right->right, BLACK, 80);
	// tree.m_root->right->right->right->right = new rbNode(tree.m_root->right->right->right, RED, 90);

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

	//int	nbrs[12] = {10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70};

	for (size_t i = 0; i < 100; ++i)
	{
		tree.insertValue(i);
	}
	std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;


		// std::cout << "Enter Value to be deleted: ";
		// int x;
		// std::cin >> x;
		// std::cout << std::endl;
		// tree.deleteValue(x);
		tree.printTree();
		// std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;

	for (int i = 0; i < 100 && tree.treeCheck(); ++i)
	{
		tree.deleteValue(i);
	}
	tree.printTree();
	std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	std::cout << "DONE" << std::endl;
	return 0;
}