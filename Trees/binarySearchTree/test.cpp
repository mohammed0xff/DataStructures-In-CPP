#include "binarySearchTree.hpp"


int main() {

    Tree<int> tree;

    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(10);
    tree.insert(30);
    tree.insert(60);
    tree.insert(80);

    // making tree with vector
    std::vector<int> vec = { 50, 25, 75, 10, 30, 60, 80 };
    Tree<int> tree2;
    tree2.makeTree(vec);
    
    //tree.deleteWithValue(50);
    //tree.deleteWithValue(25);
    //tree.deleteWithValue(75);
    //tree.deleteWithValue(10);
    //tree.deleteWithValue(30);
    //tree.deleteWithValue(60);
    //tree.deleteWithValue(80);

    std::cout << "search result :" << tree.search(80) << "\n";

    tree.inorderPrint();
    tree.postorderPrint();
    tree.preorderPrint();

    return 0;
}

