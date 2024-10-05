#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>

typedef struct Node {
    int key, priority;
    struct Node* left, * right;
} Node;

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = rand();
    node->left = node->right = NULL;
    return node;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

void split(Node* root, int k, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }

    if (root->key <= k) {
        *left = root;
        split(root->right, k, &(*left)->right, right);
    }
    else {
        *right = root;
        split(root->left, k, left, &(*right)->left);
    }
}

Node* insert(Node* root, int key) {
    Node* new_node = newNode(key);

    if (!root) return new_node;

    if (new_node->priority > root->priority) {
        split(root, key, &new_node->left, &new_node->right);
        return new_node;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

Node* erase(Node* root, int key) {
    if (!root) return root;

    if (root->key == key) {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }

    if (key < root->key)
        root->left = erase(root->left, key);
    else
        root->right = erase(root->right, key);

    return root;
}

// Обход дерева in-order для проверки
void inorder(Node* root, int* output, int* index) {
    if (!root) return;
    inorder(root->left, output, index);
    output[(*index)++] = root->key;
    inorder(root->right, output, index);
}

bool verifyInorder(Node* root, int* expected, int n) {
    int index = 0;
    int output[100];
    inorder(root, output, &index);
    if (index != n) return false;
    for (int i = 0; i < n; i++) {
        if (output[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

TEST(TreapTest, InsertTest) {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);

    int expected1[] = { 5, 10, 15 };
    EXPECT_TRUE(verifyInorder(root, expected1, 3));

    root = insert(root, 7);
    root = insert(root, 20);

    int expected2[] = { 5, 7, 10, 15, 20 };
    EXPECT_TRUE(verifyInorder(root, expected2, 5));
}

TEST(TreapTest, EraseTest) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 7);
    root = insert(root, 20);

    root = erase(root, 10);
    int expected1[] = { 5, 7, 15, 20 };
    EXPECT_TRUE(verifyInorder(root, expected1, 4));

    root = erase(root, 20);
    int expected2[] = { 5, 7, 15 };
    EXPECT_TRUE(verifyInorder(root, expected2, 3));
}

TEST(TreapTest, MergeTest) {
    Node* left = NULL;
    Node* right = NULL;

    left = insert(left, 5);
    left = insert(left, 10);
    left = insert(left, 15);

    right = insert(right, 20);
    right = insert(right, 25);
    right = insert(right, 30);

    Node* merged = merge(left, right);
    int expected[] = { 5, 10, 15, 20, 25, 30 };
    EXPECT_TRUE(verifyInorder(merged, expected, 6));
}

TEST(TreapTest, SplitTest) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 7);
    root = insert(root, 20);

    Node* left = NULL, * right = NULL;
    split(root, 10, &left, &right);

    int expectedLeft[] = { 5, 7, 10 };
    int expectedRight[] = { 15, 20 };

    EXPECT_TRUE(verifyInorder(left, expectedLeft, 3));
    EXPECT_TRUE(verifyInorder(right, expectedRight, 2));
}
