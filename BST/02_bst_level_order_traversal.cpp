#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

struct Queue {
    BSTNode* arr[50];
    int front = -1;
    int rear = -1;
} q;

void enqueue(Queue &q, BSTNode* node) {
    if (q.rear == -1) {
        q.front = q.rear = 0;
    } else {
        q.rear++;
    }
    q.arr[q.rear] = node;
}

BSTNode* dequeue(Queue &q) {
    BSTNode* temp = q.arr[q.front];
    if (q.front == q.rear) {
        q.front = q.rear = -1;
    } else {
        q.front++;
    }
    return temp;
}

void insertNode(BSTNode* &root, int key) {
    if (root == NULL) {
        root = new BSTNode;
        root->data = key;
        root->left = root->right = NULL;
        return;
    }
    if (key > root->data)
        insertNode(root->right, key);
    else
        insertNode(root->left, key);
}

void levelOrderTraversal(BSTNode* root) {
    if (root == NULL) return;

    enqueue(q, root);

    while (q.front != -1) {
        BSTNode* current = dequeue(q);
        cout << current->data << " ";

        if (current->left != NULL)
            enqueue(q, current->left);

        if (current->right != NULL)
            enqueue(q, current->right);
    }
}

int main() {
    int value;

    while (cin >> value && value != -1) {
        insertNode(root, value);
    }

    levelOrderTraversal(root);
    return 0;
}
