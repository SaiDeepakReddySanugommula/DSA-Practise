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
    BSTNode* res = root;
    while (root != NULL) {
        if (res->data > root->data)
            res = root;
        root = root->left;
    }
    return res;
}

BSTNode* findMax(BSTNode* root) {
    BSTNode* res = root;
    while (root != NULL) {
        if (res->data < root->data)
            res = root;
        root = root->left;
    }
    return res;
}

BSTNode* searchNode(BSTNode* root, int key) {
    if (root == NULL) return NULL;
    if (root->data == key) return root;
    if (key < root->data) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

BSTNode* findViolation(BSTNode* root) {
    if (root == NULL) return NULL;

    if (root->right && !(findMin(root->right)->data > root->data))
        return findMin(root->right);

    if (root->left && !(findMax(root->left)->data < root->data))
        return findMax(root->left);

    BSTNode* leftCheck = findViolation(root->left);
    if (leftCheck != NULL) return leftCheck;

    BSTNode* rightCheck = findViolation(root->right);
    if (rightCheck != NULL) return rightCheck;

    return NULL;
}

void preorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    int value;

    while (cin >> value && value != -1) {
        insertNode(root, value);
    }

    BSTNode* nodeToModify = searchNode(root, 27);
    nodeToModify->data = 16;

    BSTNode* violatedNode = findViolation(root);
    if (violatedNode)
        cout << violatedNode->data << endl;

    preorderTraversal(root);
    return 0;
}
