#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode *left, *right;
};

BSTNode* root = NULL;

void insertNode(BSTNode* &root, int key) {
    if (root == NULL) {
        root = new BSTNode;
        root->data = key;
        root->left = root->right = NULL;
        return;
    }

    if (key > root->data)
        insertNode(root->right, key);
    else if (key < root->data)
        insertNode(root->left, key);
}

BSTNode* findMin(BSTNode* root) {
    BSTNode
