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

void traverse(BSTNode *root, int mode) {
    if (mode == 0) {
        traverse(root->left, 1);
        cout << " /" << endl << root->data << " /" << endl;
        traverse(root->right, 2);
        cout << " /";
    }
    else if (mode == 1) {   // left subtree ascending
        if (root == NULL) return;
        traverse(root->left, 1);
        cout << root->data << " ";
        traverse(root->right, 1);
    }
    else {   // right subtree descending
        if (root == NULL) return;
        traverse(root->right, 2);
        cout << root->data << " ";
        traverse(root->left, 2);
    }
}

int main() {
    int value;

    while (cin >> value && value != -1) {
        insertNode(root, value);
    }

    traverse(root, 0);
    return 0;
}
