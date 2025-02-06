#include<iostream>
using namespace std;

struct Tnode
{
    string word;
    string meaning;
    Tnode* left;
    Tnode* right;
};

class Dictionary
{
public:
    Tnode* head;
    Dictionary() { head = NULL; }

    void insert(string w, string m)
    {
        Tnode* nn = new Tnode();
        nn->word = w;
        nn->meaning = m;
        nn->left = nn->right = NULL;

        if (head == NULL)
        {
            head = nn;
            return;
        }

        Tnode* temp = head;
        while (true)
        {
            if (w < temp->word)
            {
                if (temp->left == NULL)
                {
                    temp->left = nn;
                    return;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = nn;
                    return;
                }
                temp = temp->right;
            }
        }
    }

    void inorder(Tnode* root)
    {
        if (root)
        {
            inorder(root->left);
            cout << endl << root->word << " : " << root->meaning;
            inorder(root->right);
        }
    }

    void preorder(Tnode* root)
    {
        if (root)
        {
            cout << endl << root->word << " : " << root->meaning;
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Tnode* root)
    {
        if (root)
        {
            postorder(root->left);
            postorder(root->right);
            cout << endl << root->word << " : " << root->meaning;
        }
    }

    void search(string w)
    {
        Tnode* temp = head;
        while (temp)
        {
            if (w == temp->word)
            {
                cout << "\nWord found: " << temp->word << " : " << temp->meaning;
                return;
            }
            temp = (w < temp->word) ? temp->left : temp->right;
        }
        cout << "\nWord not found in dictionary..";
    }

    int height(Tnode* root)
    {
        if (!root) return 0;
        int lheight = height(root->left);
        int rheight = height(root->right);
        return max(lheight, rheight) + 1;
    }

    int levelOfNode(Tnode* root, string w, int level)
    {
        if (!root) return -1;
        if (root->word == w) return level;
        
        int leftLevel = levelOfNode(root->left, w, level + 1);
        if (leftLevel != -1) return leftLevel;
        
        return levelOfNode(root->right, w, level + 1);
    }

    int findLevel(string w)
    {
        return levelOfNode(head, w, 0);
    }

    Tnode* minValueNode(Tnode* node)
    {
        Tnode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    Tnode* deleteNode(Tnode* root, string key)
{
    if (!root) return root; // If root is NULL, return NULL

    if (key < root->word) // If key is smaller, traverse the left subtree
        root->left = deleteNode(root->left, key);
    else if (key > root->word) // If key is larger, traverse the right subtree
        root->right = deleteNode(root->right, key);
    else // Node with the key found
    {
        // Case 1: Node has no left child
        if (!root->left)
        {
            Tnode* temp = root->right;
            delete root; // Free memory
            return temp; // Return the right subtree (could be NULL)
        }
        // Case 2: Node has no right child
        else if (!root->right)
        {
            Tnode* temp = root->left;
            delete root; // Free memory
            return temp; // Return the left subtree
        }

        // Case 3: Node has two children
        Tnode* temp = minValueNode(root->right); // Get the inorder successor
        root->word = temp->word; // Copy the inorder successor's content to this node
        root->meaning = temp->meaning;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->word);
    }
    return root; // Return the (possibly new) root
}


    Tnode* cloneTree(Tnode* root)
    {
        if (!root) return NULL;
        Tnode* newNode = new Tnode{ root->word, root->meaning, NULL, NULL };
        newNode->left = cloneTree(root->left);
        newNode->right = cloneTree(root->right);
        return newNode;
    }

    Tnode* mirrorTree(Tnode* root)
    {
        if (!root) return NULL;
        Tnode* mirrored = new Tnode{ root->word, root->meaning, NULL, NULL };
        mirrored->left = mirrorTree(root->right);
        mirrored->right = mirrorTree(root->left);
        return mirrored;
    }
};

int main()
{
    Dictionary d;
    int ch;
    string w, m;
    Tnode* ct=NULL;
    Tnode* mt=NULL;
    do
    {
        cout << "\n1. Insert word";
        cout << "\n2. Inorder traversal";
        cout << "\n3. Preorder traversal";
        cout << "\n4. Postorder traversal";
        cout << "\n5. Search word";
        cout << "\n6. Height of tree";
        cout << "\n7. Delete word";
        cout << "\n8. Clone tree";
        cout << "\n9. Level of a particular node";
        cout << "\n10. Mirror tree";
        cout << "\n11. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1:
                cout << "\nEnter word: ";
                cin >> w;
                cout << "\nEnter meaning: ";
                cin.ignore();
                getline(cin, m);
                d.insert(w, m);
                break;
            case 2:
                d.inorder(d.head);
                break;
            case 3:
                d.preorder(d.head);
                break;
            case 4:
                d.postorder(d.head);
                break;
            case 5:
                cout << "\nEnter word to search: ";
                cin >> w;
                d.search(w);
                break;
            case 6:
                cout << "\nHeight: " << d.height(d.head);
                break;
            case 7:
                cout << "\nEnter word to delete: ";
                cin >> w;
                d.head = d.deleteNode(d.head, w);
                break;
            case 8:
                ct = d.cloneTree(d.head);
                cout << "\nTree cloned successfully.";
                d.inorder(ct);
                delete ct;
                break;
            case 9:
                cout << "\nEnter word to find its level: ";
                cin >> w;
                cout << "\nLevel: " << d.findLevel(w);
                break;
            case 10:
                mt = d.mirrorTree(d.head);
                cout << "\nTree mirrored successfully.";
                d.inorder(mt);
                delete mt;
                break;
            case 11:
                break;
        }
    } while (ch != 11);

    return 0;
}
