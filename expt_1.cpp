#include<iostream>
#include<queue>
using namespace std;

struct Node
{
    string key;
    string value;
    Node* left;
    Node* right;
};

class DictionaryBST
{
public:
    Node* root;
    DictionaryBST() { root = NULL; }

    void insert(string k, string v)
    {
        Node* newNode = new Node();
        newNode->key = k;
        newNode->value = v;
        newNode->left = newNode->right = NULL;

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true)
        {
            if (k < current->key)
            {
                if (current->left == NULL)
                {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            }
            else
            {
                if (current->right == NULL)
                {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }

    void inorder(Node* node)
    {
        if (node)
        {
            inorder(node->left);
            cout << endl << node->key << " : " << node->value;
            inorder(node->right);
        }
    }

    void preorder(Node* node)
    {
        if (node)
        {
            cout << endl << node->key << " : " << node->value;
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node)
    {
        if (node)
        {
            postorder(node->left);
            postorder(node->right);
            cout << endl << node->key << " : " << node->value;
        }
    }

    void levelOrder(Node* root)
    {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();
            cout << endl << temp->key << " : " << temp->value;
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }

    void search(string k)
    {
        Node* current = root;
        while (current)
        {
            if (k == current->key)
            {
                cout << "\nFound: " << current->key << " : " << current->value;
                return;
            }
            current = (k < current->key) ? current->left : current->right;
        }
        cout << "\nNot found.";
    }

    int height(Node* node)
    {
        if (!node) return 0;
        int lheight = height(node->left);
        int rheight = height(node->right);
        return max(lheight, rheight) + 1;
    }

    Node* minNode(Node* node)
    {
        Node* temp = node;
        while (temp && temp->left)
            temp = temp->left;
        return temp;
    }

    Node* remove(Node* node, string k)
    {
        if (!node) return node;

        if (k < node->key)
            node->left = remove(node->left, k);
        else if (k > node->key)
            node->right = remove(node->right, k);
        else
        {
            if (!node->left)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    Node* cloneTree(Node* node)
    {
        if (!node) return NULL;
        Node* newNode = new Node{ node->key, node->value, NULL, NULL };
        newNode->left = cloneTree(node->left);
        newNode->right = cloneTree(node->right);
        return newNode;
    }

    Node* mirrorTree(Node* node)
    {
        if (!node) return NULL;
        Node* mirrored = new Node{ node->key, node->value, NULL, NULL };
        mirrored->left = mirrorTree(node->right);
        mirrored->right = mirrorTree(node->left);
        return mirrored;
    }
};

int main()
{
    DictionaryBST dict;
    int choice;
    string key, value;
    Node* clonedTree = NULL;
    Node* mirroredTree = NULL;
    
    do
    {
        cout << "\n1. Insert";
        cout << "\n2. Inorder";
        cout << "\n3. Preorder";
        cout << "\n4. Postorder";
        cout << "\n5. Search";
        cout << "\n6. Height";
        cout << "\n7. Delete";
        cout << "\n8. Clone";
        cout << "\n9. Mirror";
        cout << "\n10. Level Order";
        cout << "\n11. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "\nEnter word: ";
                cin >> key;
                cout << "\nEnter meaning: ";
                cin.ignore();
                getline(cin, value);
                dict.insert(key, value);
                break;
            case 2:
                dict.inorder(dict.root);
                break;
            case 3:
                dict.preorder(dict.root);
                break;
            case 4:
                dict.postorder(dict.root);
                break;
            case 5:
                cout << "\nEnter word to search: ";
                cin >> key;
                dict.search(key);
                break;
            case 6:
                cout << "\nHeight: " << dict.height(dict.root);
                break;
            case 7:
                cout << "\nEnter word to delete: ";
                cin >> key;
                dict.root = dict.remove(dict.root, key);
                break;
            case 8:
                clonedTree = dict.cloneTree(dict.root);
                cout << "\nCloned tree inorder:";
                dict.inorder(clonedTree);
                break;
            case 9:
                mirroredTree = dict.mirrorTree(dict.root);
                cout << "\nMirrored tree inorder:";
                dict.inorder(mirroredTree);
                break;
            case 10:
                cout << "\nLevel Order Traversal:";
                dict.levelOrder(dict.root);
                break;
            case 11:
                break;
        }
    } while (choice != 11);

    return 0;
}
