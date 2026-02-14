/* * PROJECT: Binary Search Tree - Node Range Analyzer
 * ------------------------------------------------
 * PROBLEM STATEMENT:
 * Create a BST and calculate the theoretical minimum and maximum 
 * values possible at each node based on its position in the tree.
 * * INITIAL CONSTRAINTS:
 * - The global minimum boundary starts at 0.
 * - The global maximum boundary starts at 99999.
 * * LOGIC RULES:
 * 1. When moving Left:  The max possible value for that child is (Parent->data - 1).
 * 2. When moving Right: The min possible value for that child is (Parent->data + 1).
 * * INPUT FORMAT: A sequence of integers ending with -1.
 * OUTPUT FORMAT: (node_data  calculated_min  calculated_max)
 */

#include <iostream>
using namespace std;

// Structure for a standard Binary Search Tree node
struct bstnode {
    int data;
    bstnode *lc, *rc;
};

// Global root pointer for the tree structure
bstnode* root = NULL;

/**
 * Standard BST Insertion:
 * Values smaller than the root go to the left subtree; 
 * values larger/equal go to the right subtree.
 */
void create(bstnode* &root, int k) {
    if (root == NULL) {
        root = new bstnode;
        root->data = k;
        root->lc = NULL;
        root->rc = NULL;
        return;
    }
    if (root->data > k) {
        create(root->lc, k);
    } else {
        create(root->rc, k);
    }
}

/**
 * Helper: Finds the maximum value in a subtree (rightmost leaf).
 */
int findMax(bstnode* root) {
    while (root && root->rc) root = root->rc;
    return root->data;
}

/**
 * Helper: Finds the minimum value in a subtree (leftmost leaf).
 */
int findMin(bstnode* root) {
    while (root && root->lc) root = root->lc;
    return root->data;
}

/**
 * CORE LOGIC:
 * Calculates and prints the valid range for each node.
 * It combines inherited bounds from the parent with the actual 
 * constraints discovered from the node's own children.
 */
void func(bstnode* root, int minn, int maxx) {
    if (root == NULL) return;

    // Recursive step for Left Child: Max bound is updated
    if (root->lc) {
        func(root->lc, minn, root->data - 1);  
    }

    // Recursive step for Right Child: Min bound is updated
    if (root->rc) {
        func(root->rc, root->data + 1, maxx);
    }

    // Local variables to refine the bounds for current node display
    int mn = minn;
    int mx = maxx;

    // Tighten the bounds based on the actual max/min of the subtrees
    if (root->lc) mn = findMax(root->lc) + 1;
    if (root->rc) mx = findMin(root->rc) - 1;

    // Result output
    cout << root->data << " " << mn << " " << mx << endl;
}

int main() {
    int input_val;
    
    // Continuous input until -1 sentinel is entered
    while (cin >> input_val && input_val != -1) {
        create(root, input_val);
    }

    // Setting the initial problem boundaries
    int initial_min = 0;
    int initial_max = 99999;

    // Begin the recursive range analysis
    func(root, initial_min, initial_max);

    return 0;
}
