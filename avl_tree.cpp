#include<iostream>
using namespace std;

struct Node
{
    int player_id;
    float score;
    int height;
    Node* left;
    Node* right;

    Node(int pid, float sc){
    player_id = pid;
    score = sc;
    height = 1;
    left = right = NULL;
    } 
};

class Player
{
public:
    Node* root;
    Player(){
    	root = 	NULL;
    	}

    int getHeight(Node* node)
    {
        if(!node) return 0;
        int lheight = height(node->left);
        int rheight = height(node->right);
        return max(lheight, rheight) + 1;
    }

    int getBalancedFactor(Node* node)
    {
        if (root == NULL) return 0;
        return (getheight(root->left) - getheight(root->right));
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int pid, float sc)
    {
        if (!node)
            return new Node(pid, sc);

        if (sc < node->score)
            node->left = insertNode(node->left, pid, sc);
        else if (sc > node->score)
            node->right = insertNode(node->right, pid, sc);
        else
            return node;  // Duplicate scores are not allowed

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalancedFactor(node);

        if (balance > 1 && sc < node->left->score)
            return rightRotate(node);

        if (balance < -1 && sc > node->right->score)
            return leftRotate(node);

        if (balance > 1 && sc > node->left->score)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && sc < node->right->score)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void display(Node* node)
    {
        if (node)
        {
            display(node->left);
            cout << "\nPlayer id: " << node->player_id << "  Score: " << node->score;
            display(node->right);
        }
    }
};

int main()
{
    Player p;
    int pi, ch;
    float s;
    do
    {
        cout << "\n1. Register player";
        cout << "\n2. Display Player";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nEnter player id: ";
            cin >> pi;
            cout << "\nEnter player score: ";
            cin >> s;
            p.root = p.insertNode(p.root, pi, s);
            break;

        case 2:
            p.display(p.root);
            break;

        case 3:
            break;
        }
    } while (ch != 3);
    return 0;
}

