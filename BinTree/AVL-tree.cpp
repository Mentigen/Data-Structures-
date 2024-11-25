#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        key = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* remove(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

bool search(Node* root, int value) {
    if (root == nullptr) return false;
    if (value == root->key) return true;
    if (value < root->key) return search(root->left, value);
    return search(root->right, value);
}