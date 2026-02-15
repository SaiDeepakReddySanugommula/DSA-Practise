#include <iostream>
using namespace std;

struct BSTNode {
    int data;
    BSTNode *left, *right;
};

BSTNode* root = NULL;

struct Queue {
    BSTNode* arr[1000];
    int front = -1, rear = -1;
} q;

void enqueue(Queue &q, BSTNode *node) {
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

int findPartitionIndex(int arr[], int low, int high, int rootValue) {
    for (int i = high; i >= low; i--) {
        if (arr[i] < rootValue)
            return i;
    }
    return low - 1;
}

void buildBSTFromPostorder(BSTNode* &root, int arr[], int low, int high) {
    if (high < low) return;

    root = new BSTNode;
    root->data = arr[high];
    root->left = root->right = NULL;

    int partition = findPartitionIndex(arr, low, high, arr[high]);

    buildBSTFromPostorder(root->left, arr, low, partition);
    buildBSTFromPostorder(root->right, arr, partition + 1, high - 1);
}

void printLevelOrderLineByLine(BSTNode *root) {
    enqueue(q, root);
    enqueue(q, NULL);

    while (q.rear != -1) {
        BSTNode* temp = dequeue(q);

        if (temp != NULL) {
            cout << temp->data << " ";
            if (temp->left) enqueue(q, temp->left);
            if (temp->right) enqueue(q, temp->right);
        } 
        else {
            if (q.rear == -1) {
                cout << endl;
                return;
            }
            cout << endl;
            enqueue(q, NULL);
        }
    }
}

int main() {
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    buildBSTFromPostorder(root, arr, 0, n - 1);
    printLevelOrderLineByLine(root);

    return 0;
}
