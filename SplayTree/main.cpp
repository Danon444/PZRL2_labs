#include "splay_tree_api.h"
#include <iostream>
#include <string>

int main()
{
	SplayTree<int, std::string> tree;
	tree.insert(50, "fifty");
	tree.insert(30, "thirty");
	tree.insert(70, "seventy");
	tree.insert(20, "twenty");
	tree.insert(40, "forty");
	tree.insert(60, "sixty");
	tree.insert(80, "eighty");
	auto* val = tree.search(30);
	if (val)
	       	std::cout << *val << std::endl;
	tree.insert(40, "forty_updated");
	val = tree.search(40);
	if (val)
	       	std::cout << *val << std::endl;
	tree.remove(20);
	tree.remove(50);
	std::cout << tree.size() << std::endl;
	std::cout << tree.empty() << std::endl;
	return 0;
}
