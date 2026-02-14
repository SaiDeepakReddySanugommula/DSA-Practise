/* * PROJECT: Binary Search Tree – "End" Node Detector
 * -----------------------------------------------
 * PROBLEM STATEMENT:
 * Create a BST from input. A leaf node is defined as an "end" node 
 * if a new number cannot be inserted as its left or right child 
 * because those values (node->data - 1 and node->data + 1) already 
 * exist as ancestors in the current path.
 *
 * "This is not the end, this is not even the beginning of the end, 
 * this is just perhaps the end of the beginning." — Winston S. Churchill
 */

#include <iostream>
#include <vector>

using namespace std;

// Stack structure to track ancestor nodes in the current path
struct Stack {
    int top = -1;
    int arr[50];
};

struct bstnode {
    int data;
    bstnode *lc, *rc;
};

// Standard stack operations
void push(Stack &s, int k) {
    if (s.top >= 49) return;
    s.arr[++s.top] = k;
}

int pop(Stack &s) {
    return s.arr[s.top--];
}

/**
 * Standard BST Insertion:
 * Smaller values to the left, larger/equal to the right.
 */
void create(bstnode* &root, int k) {
    if (root == NULL) {
        root = new bstnode;
        root->data = k;
        root->lc = NULL;
        root->rc = NULL;
        return;
    }
    if (k < root->data) create(root->lc, k);
    else create(root->rc, k);
}

/**
 * Validates the "End" condition:
 * Checks if (k+1) and (k-1) exist in the stack of ancestors.
 */
bool isEndNode(int k, Stack s) {
    bool foundNext = false;
    bool foundPrev = false;

    while (s.top >= 0) {
        int currentAncestor = pop(s);
        if (currentAncestor == k + 1) foundNext = true;
        if (currentAncestor == k - 1) foundPrev = true;
    }
    return foundNext && foundPrev;
}

/**
 * Traverses the tree and identifies leaf nodes that satisfy 
 * the "End" node criteria.
 */
void findEnds(bstnode* root, Stack pathStack) {
    if (root == NULL) return;

    // Check if the current node is a leaf
    if (root->lc == NULL && root->rc == NULL) {
        if (isEndNode(root->data, pathStack)) {
            cout << root->data << endl;
        }
    }

    // Add current node to path stack and recurse
    push(pathStack, root->data);
    
    if (root->lc) findEnds(root->lc, pathStack);
    if (root->rc) findEnds(root->rc, pathStack);
}

int main() {
    bstnode* root = NULL;
    Stack pathTracker;
    int val;

    // Build tree until -1 is entered
    while (cin >> val && val != -1) {
        create(root, val);
    }

    if (root != NULL) {
        findEnds(root, pathTracker);
    }

    return 0;
}
