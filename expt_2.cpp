#include<iostream>
using namespace std;

struct Node{
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

class Player{
public:
    Node* root;
    Player(){
    	root = 	NULL;
    	}

    int getHeight(Node* node){
        if(!node) return 0;
        int lheight = getHeight(node->left);
        int rheight = getHeight(node->right);
        return max(lheight, rheight) + 1;
    }

    int getBalancedFactor(Node* node){
        if (root == NULL) return 0;
        return (getHeight(root->left) - getHeight(root->right));
    }

    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int pid, float sc){
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

    void display(Node* node) {
        if (node) {
            display(node->right);
            cout << "\nPlayer ID: " << node->player_id << " | Score: " << node->score;
            display(node->left);
        }
    }
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }
    Node* deleteNode(Node* root, float score) {
        if (!root) return root;
    
        if (score < root->score)
            root->left = deleteNode(root->left, score);
        else if (score > root->score)
            root->right = deleteNode(root->right, score);
        else {
            // Node with one or no child
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp; // Copy contents of the non-empty child
                delete temp;
            } else {
                // Node with two children
                Node* temp = minValueNode(root->right);
                root->score = temp->score;
                root->player_id = temp->player_id;
                root->right = deleteNode(root->right, temp->score);
            }
        }
    
        if (!root) return root;
    
        // Update height
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
        // Check balance
        int balance = getBalancedFactor(root);
    
        // Left Left Case
        if (balance > 1 && getBalancedFactor(root->left) >= 0)
            return rightRotate(root);
    
        // Left Right Case
        if (balance > 1 && getBalancedFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    
        // Right Right Case
        if (balance < -1 && getBalancedFactor(root->right) <= 0)
            return leftRotate(root);
    
        // Right Left Case
        if (balance < -1 && getBalancedFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    
        return root;
    }        
};

int main()
{
    Player p;
    int pi, ch;
    float s, r;
    do
    {
        cout << "\n1. Register player";
        cout << "\n2. Display Player";
        cout << "\n3. Remove Player";
        cout << "\n4. Exit";
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
            cout << "\nEnter score of player which is to be removed";
            cin >> r;
            p.root = p.deleteNode(p.root, r);
            cout<< "\nPlayer removed if score existed";
            break;
        case 4:
            break;
        }
    } while (ch != 4);
    return 0;
}