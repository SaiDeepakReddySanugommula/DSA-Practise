/* * PROJECT: Binary Search Tree – Bend Detector
 * ------------------------------------------
 * PROBLEM STATEMENT:
 * Construct a BST and count the occurrences of specific directional "bends" 
 * in all paths from the root. A bend is defined by two consecutive movements.
 * * BEND TYPES:
 * 1. LL: Left-Left movement
 * 2. LR: Left-Right movement
 * 3. RR: Right-Right movement
 * 4. RL: Right-Left movement
 *
 * "Life is the school, Love is the lesson." — KR
 */

#include <iostream>

using namespace std;

// Node structure for the Binary Search Tree
struct bstnode {
    int data;
    bstnode *lc, *rc;
};

// Custom Stack to track the path direction (0 for Left, 1 for Right)
struct Stack {
    int top = -1;
    int arr[100]; // Increased size for deeper trees
};

// Global counters for different bend types
int ll = 0, lr = 0, rr = 0, rl = 0;

/**
 * Pushes the direction (0=Left, 1=Right) onto the path stack.
 */
void push(Stack &s, int direction) {
    if (s.top >= 99) return;
    s.arr[++s.top] = direction;
}

/**
 * Removes the last direction from the path stack.
 */
int pop(Stack &s) {
    if (s.top < 0) return -1;
    return s.arr[s.top--];
}

/**
 * Standard BST insertion logic.
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
 * Recursive function to traverse the tree and identify bends.
 * A bend is identified by looking at the last two directions in the stack.
 */
void countBends(bstnode* root, Stack &s) {
    if (root == NULL) return;

    // Check for a "bend" if we have at least two edges in the current path
    if (s.top >= 1) {
        int current_turn = s.arr[s.top];     // The turn that led to this node
        int previous_turn = s.arr[s.top - 1]; // The turn that led to the parent

        if (previous_turn == 0 && current_turn == 0) ll++;
        else if (previous_turn == 0 && current_turn == 1) lr++;
        else if (previous_turn == 1 && current_turn == 1) rr++;
        else if (previous_turn == 1 && current_turn == 0) rl++;
    }

    // Traverse Left: Push 0 to indicate a left turn
    if (root->lc) {
        push(s, 0);
        countBends(root->lc, s);
        pop(s); // Backtrack
    }

    // Traverse Right: Push 1 to indicate a right turn
    if (root->rc) {
        push(s, 1);
        countBends(root->rc, s);
        pop(s); // Backtrack
    }
}

int main() {
    bstnode* root = NULL;
    Stack pathStack;
    int val;

    // Build the tree from input until -1 sentinel
    while (cin >> val && val != -1) {
        create(root, val);
    }

    // Start traversal to count bends
    if (root != NULL) {
        countBends(root, pathStack);
    }

    // Output results in specified order: LL, LR, RR, RL
    cout << ll << " " << lr << " " << rr << " " << rl << endl;

    return 0;
}
