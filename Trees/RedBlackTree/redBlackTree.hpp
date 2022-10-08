#pragma once

#include <iostream>
using namespace std;

enum class NodeColor { Black, RED };

struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    NodeColor color;
    int key;
};

class RedBlackTree {

public:

    RedBlackTree();

    void insert(int key);
    void deleteNode(int key);

    void preorder();
    void inorder();
    void postorder();

private:

    void initializeNULLNode(TreeNode* node, TreeNode* parent);

    void leftRotate(TreeNode* x);
    void rightRotate(TreeNode* x);

    void fixDelete(TreeNode* x);
    void fixInsert(TreeNode* k);

    TreeNode* minimum(TreeNode* node);
    void transplant(TreeNode* u, TreeNode* v);
    void deleteNodeHelper(TreeNode* node, int key);

    void preOrderHelper(TreeNode* node);
    void inOrderHelper(TreeNode* node);
    void postOrderHelper(TreeNode* node);

private:

    TreeNode* root;
    TreeNode* N;

};


RedBlackTree::RedBlackTree() 
{
    N = new TreeNode;
    N->color = NodeColor::Black;
    N->left = nullptr;
    N->right = nullptr;
    root = N;
}


void RedBlackTree::initializeNULLNode(TreeNode* node, TreeNode* parent) {
    node->key = 0;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;
    node->color = NodeColor::Black;
}

void RedBlackTree::insert(int key) {
    TreeNode* node = new TreeNode;
    node->parent = nullptr;
    node->key = key;
    node->left = N;
    node->right = N;
    node->color = NodeColor::RED;

    TreeNode* y = nullptr;
    TreeNode* x = this->root;

    while (x != N) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->key < y->key) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = NodeColor::Black;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}

// to balance tree after insertion operation
void RedBlackTree::fixInsert(TreeNode* k) {
    TreeNode* u;
    while (k->parent->color == NodeColor::RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == NodeColor::RED) {
                u->color = NodeColor::Black;
                k->parent->color = NodeColor::Black;
                k->parent->parent->color = NodeColor::RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = NodeColor::Black;
                k->parent->parent->color = NodeColor::RED;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->color == NodeColor::RED) {
                u->color = NodeColor::Black;
                k->parent->color = NodeColor::Black;
                k->parent->parent->color = NodeColor::RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = NodeColor::Black;
                k->parent->parent->color = NodeColor::RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = NodeColor::Black;
}


void RedBlackTree::transplant(TreeNode* a, TreeNode* b) {
    if (a->parent == nullptr) {
        root = b;
    }
    else if (a == a->parent->left) {
        a->parent->left = b;
    }
    else {
        a->parent->right = b;
    }
    b->parent = a->parent;
}

void RedBlackTree::deleteNodeHelper(TreeNode* node, int key) {
    TreeNode* x;
    TreeNode* y;
    TreeNode* z = N;

    while (node != N) {
        if (node->key == key) {
            z = node;
        }
        if (node->key > key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    if (z == N) {
        cout << "Key doesn't exist in the tree." << endl;
        return;
    }

    y = z;

    NodeColor y_original_color = y->color;
    if (z->left == N) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == N) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == NodeColor::Black) {
        fixDelete(x);
    }
}

void RedBlackTree::deleteNode(int key) {
    deleteNodeHelper(this->root, key);
}

// to balance tree after deletion operation
void RedBlackTree::fixDelete(TreeNode* x) {

    TreeNode* s;
    while (x != root && x->color == NodeColor::Black) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == NodeColor::RED) {
                s->color = NodeColor::Black;
                x->parent->color = NodeColor::RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == NodeColor::Black && s->right->color == NodeColor::Black) {
                s->color = NodeColor::RED;
                x = x->parent;
            }
            else {
                if (s->right->color == NodeColor::Black) {
                    s->left->color = NodeColor::Black;
                    s->color = NodeColor::RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = NodeColor::Black;
                s->right->color = NodeColor::Black;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            s = x->parent->left;
            if (s->color == NodeColor::RED) {
                s->color = NodeColor::Black;
                x->parent->color = NodeColor::RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == NodeColor::Black && s->right->color == NodeColor::Black) {
                s->color = NodeColor::RED;
                x = x->parent;
            }
            else {
                if (s->left->color == NodeColor::Black) {
                    s->right->color = NodeColor::Black;
                    s->color = NodeColor::RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = NodeColor::Black;
                s->left->color = NodeColor::Black;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = NodeColor::Black;
}

TreeNode* RedBlackTree::minimum(TreeNode* node) {
    while (node->left != N) {
        node = node->left;
    }
    return node;
}


void RedBlackTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;
    if (y->left != N) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(TreeNode* x) {
    TreeNode* y = x->left;
    x->left = y->right;
    if (y->right != N) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}



void RedBlackTree::preOrderHelper(TreeNode* node) {
    if (node != N) {
        cout << node->key << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RedBlackTree::inOrderHelper(TreeNode* node) {
    if (node != N) {
        inOrderHelper(node->left);
        cout << node->key << " ";
        inOrderHelper(node->right);
    }
}

void RedBlackTree::postOrderHelper(TreeNode* node) {
    if (node != N) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->key << " ";
    }
}


void RedBlackTree::preorder() {
    preOrderHelper(this->root);
}

void RedBlackTree::inorder() {
    inOrderHelper(this->root);
}

void RedBlackTree::postorder() {
    postOrderHelper(this->root);
}

