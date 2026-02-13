#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

void insertNode(BSTNode*& root, int key) {
    if (root == NULL) {
        root = new BSTNode;
        root->data = key;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if (key < root->data) insertNode(root->left, key);
    else if (key > root->data) insertNode(root->right, key);
}

int findMin(BSTNode* root) {
    while (root->left != NULL) root = root->left;
    return root->data;
}

int findMax(BSTNode* root) {
    while (root->right != NULL) root = root->right;
    return root->data;
}

void inorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

bool searchKey(BSTNode* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true;
    if (key > root->data) return searchKey(root->right, key);
    return searchKey(root->left, key);
}

int main() {
    int key;
    while (cin >> key && key != -1) {
        insertNode(root, key);
    }

    preorderTraversal(root);
    cout << endl;

    inorderTraversal(root);
    cout << endl;

    postorderTraversal(root);
    cout << endl;

    cout << findMax(root) << endl;
    cout << findMin(root) << endl;

    cin >> key;
    cout << searchKey(root, key) << endl;

    cin >> key;
    cout << searchKey(root, key) << endl;

    return 0;
}
