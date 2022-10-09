#pragma once

#include <iostream>
using namespace std;


template<typename T>
class TreeNode
{
public:
    TreeNode(T x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
        , height(0)
    {}
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    int height;
};


template<typename T>
class Tree
{
public:
    Tree();
    ~Tree();

    void insert(T val);
    bool search(T val);
    void remove(T val);

    void inorderPrint();
    void postorderPrint();
    void preorderPrint();
    
    bool isEmpty();
    void clear();

private:

    TreeNode<T>* insertHelper(TreeNode<T>* root, T val);
    bool searchHelper(TreeNode<T>* root, T val);
    TreeNode <T>* deleteHelper(TreeNode<T>* root, T val);
    TreeNode<T>* minValue(TreeNode <T>* node);

    TreeNode <T>* rightRotate(TreeNode<T>* Ynode);
    TreeNode <T>* leftRotate(TreeNode<T>* Xnode);
    int getHeight(TreeNode<T>* node);
    int getBalance(TreeNode <T>* node);

    void inorderPrintHelper(TreeNode<T>*);
    void postorderPrintHelper(TreeNode<T>*);
    void preorderPrintHelper(TreeNode<T>*);

    void clearTree(TreeNode<T>* root);

private:
    TreeNode<T>* root;
};


template<typename T>
Tree<T>::Tree()
    :root(nullptr)
{
}

template<typename T>
Tree<T>::~Tree() {
    clearTree(root);
}


// ::::
//      Insertion
// ::::

template<typename T>
void Tree<T>::insert(T val) {
    root = insertHelper(root, val);
}

template<typename T>
TreeNode<T>* Tree<T>::insertHelper(TreeNode <T>* root, T val) {
    if (root == nullptr) {
        return new TreeNode<T>(val);
    }

    if (root->val < val) {
        root->right = insertHelper(root->right, val);
    }
    else {
        root->left = insertHelper(root->left, val);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // left left
    if (balance > 1 && val < root->left->val)
        return rightRotate(root);

    // right right
    if (balance < -1 && val > root->right->val)
        return leftRotate(root);

    // left right 
    if (balance > 1 && val > root->left->val)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // right left 
    if (balance < -1 && val < root->right->val)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// ::::
//      Deletion
// ::::


template<typename T>
void Tree<T>::remove(T val) {
    deleteHelper(root, val);

}

template<typename T>
TreeNode<T>* Tree<T>::minValue(TreeNode <T>* node) {
    TreeNode <T>* curr = node;
    while (curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

template<typename T>
TreeNode <T>* Tree<T>::deleteHelper(TreeNode <T>* root, T val)
{
    if (root == nullptr)
        return root;

    if (val < root->val) {
        root->left = deleteHelper(root->left, val);
    }
    else if (val > root->val) {
        root->right = deleteHelper(root->right, val);
    }else {
        // the node has only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            TreeNode <T>* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr){
                temp = root;
                root = nullptr;
            }
            else { // One child case
                *root = *temp; // Copy the non-empty child
            }
            delete temp;
        }
        else
        {
            // Node with two children case --> copy the smallest 
            // node in the right subtree (inorder successor)
            // to the root
            TreeNode <T>* temp = minValue(root->right);
            root->val = temp->val;

            // remove the inorder successor
            root->right = deleteHelper(root->right, temp->val);
        }
    }

    // If the tree had only one node return -no need to balance-
    if (root == NULL)
        return root;

    // update height of the current node.
    root->height = 1 + max(getHeight(root->left),
        getHeight(root->right));

    // getting balance of the currnet node.
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// ::::
//      Search
// ::::


template<typename T>
bool Tree<T>::search(T val) {
    if (searchHelper(root, val)) {
        std::cout << "Value " << val << " exists in the tree.\n";
        return true;
    }
    else {
        std::cout << "Value " << val << " doesn't exist in the tree.\n";
        return false;
    }
}


template<typename T>
bool Tree<T>::searchHelper(TreeNode<T> *root, T val) {
    if (root == nullptr) {
        return false;
    }
    if (root->val == val) {
        return true;
    }
    else if (val > root->val) {
        return searchHelper(root->right, val);
    }
    else {
        return searchHelper(root->left, val);
    }
}


// ::::
//      Balancing functions
// ::::


template<typename T>
int Tree<T>::getHeight(TreeNode <T>* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

template<typename T>
TreeNode <T>* Tree<T>::rightRotate(TreeNode <T>* Ynode) {

    TreeNode <T>* Xnode = Ynode->left;
    TreeNode <T>* T2 = Xnode->right;

    // right rotation
    Xnode->right = Ynode;
    Ynode->left = T2;

    // update hights
    Ynode->height = max(getHeight(Ynode->left), getHeight(Ynode->right)) + 1;
    Xnode->height = max(getHeight(Xnode->left), getHeight(Xnode->right)) + 1;

    return Xnode;
}

template<typename T>
TreeNode <T>* Tree<T>::leftRotate(TreeNode <T>* Xnode) {

    TreeNode <T>* Ynode = Xnode->right;
    TreeNode <T>* T2 = Ynode->left;

    // left rotation 
    Ynode->left = Xnode;
    Xnode->right = T2;

    // update hights
    Xnode->height = max(getHeight(Xnode->left), getHeight(Xnode->right)) + 1;
    Ynode->height = max(getHeight(Ynode->left), getHeight(Ynode->right)) + 1;

    return Ynode;
}


template<typename T>
int Tree<T>::getBalance(TreeNode <T>* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}


// ::::
//      Printing
// ::::



template<typename T>
void Tree<T>::inorderPrint() {
    if (not isEmpty()) {
        std::cout << "Printing Inorder Traversal .. \n";
        inorderPrintHelper(root);
        std::cout << "\n";
    } else {
        std::cout << "BST is empty! \n";
    }
}

template<typename T>
void Tree<T>::postorderPrint() {
    if (not isEmpty()) {
        std::cout << "Printing Postorder Traversal .. \n";
        postorderPrintHelper(root);
        std::cout << "\n";
    }
    else {
        std::cout << "BST is empty! \n";
    }
}

template<typename T>
void Tree<T>::preorderPrint() {
    if (not isEmpty()) {
        std::cout << "Printing Preorder Traversal .. \n";
        preorderPrintHelper(root);
        std::cout << "\n";
    }
    else {
        std::cout << "BST is empty! \n";
    }
}

template<typename T>
void Tree<T>::inorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    inorderPrintHelper(root->right);
    std::cout << root->val << " ";
    inorderPrintHelper(root->left);

}

template<typename T>
void Tree<T>::postorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    inorderPrintHelper(root->right);
    inorderPrintHelper(root->left);
    std::cout << root->val << " ";

}

template<typename T>
void Tree<T>::preorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    std::cout << root->val << " ";
    inorderPrintHelper(root->right);
    inorderPrintHelper(root->left);
}


// ::::
//      Other utilities
// ::::

template<typename T>
bool Tree<T>::isEmpty() {
    return root == nullptr;
}

template<typename T>
void Tree<T>::clearTree(TreeNode<T> * root) {
    if (root != nullptr) {
        clearTree(root->left);
        clearTree(root->right);
        delete root;
    }
}

template<typename T>
void Tree<T>::clear() {
    clearTree(root);
}
