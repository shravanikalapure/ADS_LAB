#include <iostream>
#include <climits>
#include <string>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data; // directory name or ID (you can use string instead of int)
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data) {
        parent = left = right = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node* root;

    // Left rotate x
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Right rotate x
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    // Fix violations after insertion
    void fixInsert(Node* k) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (k != root && k->color == RED && k->parent->color == RED) {
            parent = k->parent;
            grandparent = parent->parent;

            // Parent is left child of grandparent
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                // Case 1: Uncle is red
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    k = grandparent;
                }
                else {
                    // Case 2: k is right child
                    if (k == parent->right) {
                        leftRotate(parent);
                        k = parent;
                        parent = k->parent;
                    }

                    // Case 3: k is left child
                    rightRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    k = parent;
                }
            }
            else {
                Node* uncle = grandparent->left;

                // Case 1
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    k = grandparent;
                }
                else {
                    // Case 2
                    if (k == parent->left) {
                        rightRotate(parent);
                        k = parent;
                        parent = k->parent;
                    }

                    // Case 3
                    leftRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    k = parent;
                }
            }
        }

        root->color = BLACK;
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            cout << root->data << " (" << (root->color == RED ? "R" : "B") << ") ";
            inorderTraversal(root->right);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* node = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        // Fix Red-Black Tree properties
        fixInsert(node);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};
int main() {
    RedBlackTree R1;
    int choice, value;

    do {
        cout << "\n===== Directory Red-Black Tree Menu =====\n";
        cout << "1. Insert Directory\n";
        cout << "2. Display Inorder\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter directory ID (int): ";
                cin >> value;
                R1.insert(value);
                cout << "Inserted successfully.\n";
                break;

            case 2:
                cout << "Directory Structure (Inorder Traversal):\n";
                R1.display();
                break;

            case 3:
                cout << "Exiting the file system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}