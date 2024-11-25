#include <iostream>

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (key < root->val) {
        root->left = insert(root->left, key);
    } else if (key > root->val) {
        root->right = insert(root->right, key);
    }
    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

Node* remove(Node* root, int key) {
    if (root == nullptr) return root;
    if (key < root->val) {
        root->left = remove(root->left, key);
    } else if (key > root->val) {
        root->right = remove(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->val = temp->val;
        root->right = remove(root->right, temp->val);
    }
    return root;
}

bool search(Node* root, int key) {
    if (root == nullptr) return false;
    if (key == root->val) return true;
    if (key < root->val) return search(root->left, key);
    return search(root->right, key);
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->val << " ";
        inOrderTraversal(root->right);
    }
}
