#include "AVL_Tree.hpp"

int main() {

	Tree<int> tree;

	tree.insert(25);
	tree.insert(13);
	tree.insert(19);
	tree.insert(12);
	tree.insert(3);
	tree.insert(8);

	//tree.remove(8);
	//tree.remove(12);
	//tree.remove(25);

	tree.search(6);
	tree.search(19);
	tree.search(3);

	tree.preorderPrint();
	tree.inorderPrint();
	tree.postorderPrint();

	return 0;
}
