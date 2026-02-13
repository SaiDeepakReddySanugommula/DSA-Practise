#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode *left, *right;
};

BSTNode* root = NULL;

struct Stack {
    int top = -1;
    int arr[100];
} st;

struct Queue {
    BSTNode* arr[100];
    int front = -1, rear = -1;
} q;

void insertNode(BSTNode* &root, int key) {
    if (root == NULL) {
        root = new BSTNode;
        root->data = key;
        root->left = root->right = NULL;
        return;
    }

    if (key < root->data)
        insertNode(root->left, key);
    else
        insertNode(root->right, key);
}

void push(Stack &st, int value) {
    if (st.top >= 99) return;
    st.arr[++st.top] = value;
}

int pop(Stack &st) {
    return st.arr[st.top--];
}

void enqueue(Queue &q, BSTNode* node) {
    if (q.rear == -1)
        q.front = q.rear = 0;
    else
        q.rear++;

    q.arr[q.rear] = node;
}

BSTNode* dequeue(Queue &q) {
    BSTNode* temp = q.arr[q.front];
    if (q.front == q.rear)
        q.front = q.rear = -1;
    else
        q.front++;
    return temp;
}

int main() {
    int value;

    while (cin >> value && value != -1) {
        insertNode(root, value);
    }

    enqueue(q, root);

    while (q.front != -1) {
        BSTNode* current = dequeue(q);
        push(st, current->data);

        if (current->left) enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }

    while (st.top != -1) {
        cout << pop(st) << " ";
    }

    return 0;
}
