#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class BST {
private:
    int tree[100];
    int size = 100;

public:
    // Constructor: Read from file and insert into BST
    BST() {
        for (int i = 0; i < size; i++) tree[i] = -1;

        ifstream file("C:\\Users\\Dell\\Documents\\sem 4\\ADS\\input.txt");
        if (!file) {
            cout << "Error: Cannot open input.txt\n";
            exit(1);
        }

        int num;
        cout << "Inserting values from file: ";
        while (file >> num) {
            cout << num << " ";
            insert(0, num);
        }
        cout << endl;

        file.close();
    }

    // Insert into array-based BST
    void insert(int index, int value) {
        if (index >= size) return;

        if (tree[index] == -1) {
            tree[index] = value;
        } else if (value < tree[index]) {
            insert(2 * index + 1, value);
        } else {
            insert(2 * index + 2, value);
        }
    }

    // Non-recursive in-order traversal
    void inorder() {
        stack<int> s;
        int index = 0;

        while (!s.empty() || (index < size && tree[index] != -1)) {
            while (index < size && tree[index] != -1) {
                s.push(index);
                index = 2 * index + 1;  // Move to left child
            }

            if (!s.empty()) {
                index = s.top();
                s.pop();
                cout << tree[index] << " ";
                index = 2 * index + 2;  // Move to right child
            }
        }
    }

    // Recursive search
    bool search(int index, int key) {
        if (index >= size || tree[index] == -1)
            return false;

        if (tree[index] == key)
            return true;
        else if (key < tree[index])
            return search(2 * index + 1, key);
        else
            return search(2 * index + 2, key);
    }
};

// ---------------- DRIVER CODE -------------------

int main() {
    BST bst;

    cout << "\nIn-order traversal (non-recursive): ";
    bst.inorder();
    cout << endl;

    int key;
    cout << "\nEnter element to search: ";
    cin >> key;

    bool found = bst.search(0, key);
    if (found)
        cout << key << " is found in the BST.\n";
    else
        cout << key << " is NOT found in the BST.\n";

    return 0;
}