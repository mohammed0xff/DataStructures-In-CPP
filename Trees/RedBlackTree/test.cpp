#include "redBlackTree.hpp"


int main() {

    RedBlackTree bst;
    bst.insert(45);
    bst.insert(30);
    bst.insert(55);
    bst.insert(50);
    bst.insert(25);
    bst.insert(97);

    cout << "Before Deleting 55\n";
    bst.postorder();

    bst.deleteNode(55);

    cout << endl << "After Deleting 55" << endl;
    bst.postorder();

    return 0;
}
