#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode *left, *right;
};

BSTNode* root = NULL;

struct Queue {
    int front = -1, rear = -1;
    BSTNode* arr[100];
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
    else if (key < root->data)
        insertNode(root->left, key);
}

void printLevelOrderLineByLine(BSTNode* root) {
    if (root == NULL) return;

    enqueue(q, root);
    enqueue(q, NULL);

    while (q.rear != -1) {
        BSTNode* current = dequeue(q);

        if (current != NULL) {
            cout << current->data << " ";

            if (current->left != NULL)
                enqueue(q, current->left);

            if (current->right != NULL)
                enqueue(q, current->right);
        }
        else {
            if (q.rear == -1)
                return;

            cout << "/ ";
            enqueue(q, NULL);
        }
    }
}

int main() {
    int value;

    while (cin >> value && value != -1) {
        insertNode(root, value);
    }

    printLevelOrderLineByLine(root);
    return 0;
}
