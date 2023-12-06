#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
};

class Tree
{
public:
    Tree()
    {
        root = NULL;
    }
    void insert(Node *n){
        insert(&root, n);
    }
    void inorder(){
        inorder(root);
        cout << endl;
    }
    void preorder(){
        preorder(root);
        cout << endl;
    }
    void postorder(){
        postorder(root);
        cout << endl;
    }
    void levelorder(){
        levelorder(root);
        cout << endl;
    }

private:
    Node *root;

    void insert(struct Node **r, struct Node *n){
      //r : root
      //把新的節點(n)放入tree
      //以root為分界，左邊的會小於等於中間的值，右邊會大於中間的值
        if (*r == NULL)
            *r = n;
        else if (n->data > (*r)->data)
            insert(&((*r)->right), n);
      //(*r)->right:值
      //(&((*r)->right):地址
        else
            insert(&((*r)->left), n);
    }

    void inorder(Node *root){
        if (root){
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    void preorder(Node *root){
      if (root){
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
      }
    }

    void postorder(Node *root){
      if (root){
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
      }
    }

    void levelorder(Node *root){
      if (!root)return;

      queue<Node *> q;
      q.push(root);
      
      while (!q.empty()){
        Node *current = q.front();
        cout << current->data << " ";
        q.pop();
        
        if (current->left)
          q.push(current->left);
        
        if (current->right)
          q.push(current->right);
      }
    }
};

int main()
{
    Tree *tree = new Tree();
    Node *node;
    int j;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
    {
        node = new Node();
        node->data = rand()%10;
        node->left = NULL;
        node->right = NULL;
        tree->insert(node);
    }
    cout <<"inorder:";
    tree->inorder();
    cout <<"preorder:";
    tree->preorder();
    cout <<"postorder:";
    tree->postorder();
    cout <<"levelorder:";
    tree->levelorder();

    delete tree;
    return 0;
}
