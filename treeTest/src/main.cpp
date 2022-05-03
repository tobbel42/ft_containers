#include "tree.hpp"


int main(int argc, char **argv){
	rbTree	tree;
	if (argc < 2)
		std::cerr << "error" << std::endl;
	size_t  n = (argv[1][0] - '0') * 1000000;
	for (size_t i = 0; i < n; ++i)
	{
		tree.insertValue(rand());
	}
	//std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	for (size_t i = 0; i < n; ++i)
	{
		tree.deleteValue(rand());
	}
	//std::cout << "Tree valid: " << (tree.treeCheck()?"yes":"no") << std::endl;
	//std::cout << "DONE" << std::endl;
	//system("leaks tree_test");
	return 0;
}