#pragma once


#include <iostream>
#include<vector>


template<typename T>
class TreeNode
{
public:
    TreeNode(T x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {}
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
};


template<typename T>
class Tree
{

public:
    Tree();
    ~Tree();

    void insert(T val);
    bool search(T val);
    void deleteWithValue(T val);
    void makeTree(std::vector<T> arr);

    void inorderPrint();
    void postorderPrint();
    void preorderPrint();

    bool isEmpty();
    void clear(TreeNode<T> * root);

private:
    TreeNode<T>* insertHelper(TreeNode<T>* root, T val);
    bool searchHelper(TreeNode<T>* root, T val);
    TreeNode <T>* minValue(TreeNode <T>* node);
    TreeNode <T>* deleteHelper(TreeNode <T>* root, const T val);
    void inorderPrintHelper(TreeNode<T>*);
    void postorderPrintHelper(TreeNode<T>*);
    void preorderPrintHelper(TreeNode<T>*);

private:
    TreeNode<T>* m_root;

};


template<typename T>
Tree<T>::Tree()
    :m_root(nullptr)
{};


template<typename T>
Tree<T>::~Tree() {
    clear(m_root);
}




template<typename T>
void Tree<T>::insert(T val) {
    m_root = insertHelper(m_root, val);
}


template<typename T>
TreeNode<T>* Tree<T>::insertHelper(TreeNode <T>* root, T val) {
    if (root == nullptr) {
        return new TreeNode<T>(val);
    }
    if (root->val > val) {
        root->left = insertHelper(root->left, val);
    }
    else if(root->val < val) {
        root->right = insertHelper(root->right, val);
    }
    return root;
}




template<typename T>
bool Tree<T>::search(T val) {
    return searchHelper(m_root, val);
}


template<typename T>
bool Tree<T>::searchHelper(TreeNode<T> * root, T val) {
    if (root == nullptr) {
        return false;
    }
    if (root->val < val) {
        return searchHelper(root->right, val);
    }
    else if (root->val > val) {
        return searchHelper(root->left, val);
    }
    else {
        return true;
    }
}


template<typename T>
void Tree<T>::makeTree(std::vector<T> arr) {
    for (size_t i = 0; i < arr.size(); i++)
    {
        insert(arr[i]);
    }
}




template<typename T>
void Tree<T>::deleteWithValue(T val) 
{
    m_root =  deleteHelper( m_root, val);
}


template<typename T>
TreeNode <T>* Tree<T>::minValue(TreeNode <T>* node)
{
    TreeNode <T>* curr = node;
    while (curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}


template<typename T>
TreeNode <T>* Tree<T>::deleteHelper(TreeNode <T>* root, const T val)
{
    if (root == nullptr) {
        return root;
    }
    if (val < root->val) {
        root->left = deleteHelper(root->left, val);
    }
    else if (val > root->val) {
        root->right = deleteHelper(root->right, val);
    }
    else {

        if (root->right == nullptr && root->left == nullptr)
        {
            return nullptr;
        }
        else if (root->left == nullptr) {
            TreeNode<T>* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode<T>* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode<T>* temp = minValue(root->right);
        root->val = temp->val;
        root->right = deleteHelper(root->right, temp->val);

    }
    return root;
}





template<typename T>
void Tree<T>::inorderPrint() {
    std::cout << "Printing Inorder Traversal .. \n";
    inorderPrintHelper(m_root);
    std::cout << "\n";
}

template<typename T>
void Tree<T>::postorderPrint() {
    std::cout << "Printing Postorder Traversal .. \n";
    postorderPrintHelper(m_root);
    std::cout << "\n";
}

template<typename T>
void Tree<T>::preorderPrint() {
    std::cout << "Printing Preorder Traversal .. \n";
    preorderPrintHelper(m_root);
    std::cout << "\n";
}


template<typename T>
void Tree<T>::preorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    std::cout << root->val << " ";
    inorderPrintHelper(root->left);
    inorderPrintHelper(root->right);
}


template<typename T>
void Tree<T>::inorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    inorderPrintHelper(root->left);
    std::cout << root->val << " ";
    inorderPrintHelper(root->right);

}

template<typename T>
void Tree<T>::postorderPrintHelper(TreeNode<T>*root) 
{
    if (root == nullptr)
        return;
    inorderPrintHelper(root->left);
    inorderPrintHelper(root->right);
    std::cout << root->val << " ";

}



template<typename T>
void Tree<T>::clear(TreeNode<T>* root)
{
    if (root == NULL) return;

    clear(root->left);
    clear(root->right);

    delete root;
}

 
template<typename T>
bool Tree<T>::isEmpty() {
    return m_root == nullptr;
}


