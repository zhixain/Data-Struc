//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

template<class T>
class Node
{
public:
 Node()
 {
  data = new T;
 }
 Node(T d)
 {
  data = new T;
  (*data) = d;
 }
 Node& operator=(T d)
 {
  (*data) = d;
  return *this;
 }
 friend std::ostream& operator<<(std::ostream& out, Node n)
 {
  out << *(n.data);
  return out;
 }
 friend std::ostream& operator<<(std::ostream& out, Node* n)
 {
  out << *(n->data);
  return out;
 }
 void setData(T d)
 {
  *data = d;
 }
 T& getData() const
 {
  return *data;
 }
protected:
 T* data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
 BinaryTreeNode() : Node<T>()
 {
  left = NULL;
  right = NULL;
 }
 BinaryTreeNode(T d) : Node<T>(d)
 {
  left = NULL;
  right = NULL;
  height = 1;
 }
 BinaryTreeNode(BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) : Node<T>()
 {
  left = l;
  right = r;
 }
 BinaryTreeNode(T d, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) : Node<T>(d)
 {
  left = l;
  right = r;
 }
 void setLeft(BinaryTreeNode<T>* l)
 {
  left = l;
 }
 void setRight(BinaryTreeNode<T>* r)
 {
  right = r;
 }
 BinaryTreeNode<T>*& getLeft()
 {
  return left;
 }
 BinaryTreeNode<T>*& getRight()
 {
  return right;
 }
 bool operator>(BinaryTreeNode<T> n)
 {
  if (*(this->data) > *(n.data))
   return true;
  return false;
 }
 bool operator==(BinaryTreeNode<T> n)
 {
  if (*(this->data) == *(n.data))
   return true;
  return false;
 }
 int height;
private:
 BinaryTreeNode<T>* left, * right;
};

template<class T>
class AVLTree
{
private:
 BinaryTreeNode<T>* root;
 void inorder(BinaryTreeNode<T>* cur, int n)
 {
  if (cur == NULL)
   return;
  inorder(cur->getRight(), n + 1);
//  inorder(cur->getLeft(), n + 1);
  int j;
  for (j = 0; j < n; j++)
   cout << "  ";
  cout << cur << endl;
  inorder(cur->getLeft(), n + 1);

//  inorder(cur->getRight(), n + 1);
 }
 /* +++ */
 // A utility function to get the height of the tree
 int height(BinaryTreeNode<T>* N)
 {
  if (N == NULL)
   return 0;
  return N->height;
 }

 // A utility function to get maximum of two integers
 int max(int a, int b)
 {
  return (a > b) ? a : b;
 }

 void show(BinaryTreeNode<T>* node)
 {
  if(node == NULL)
   return;
  show(node->getLeft());
  cout << node->getData();
  cout << "  ";
  show(node->getRight());
 }
 BinaryTreeNode<T>* rightRotate(BinaryTreeNode<T>* y)
 {
  BinaryTreeNode<T>* x = y->getLeft();
  BinaryTreeNode<T>* T2 = x->getRight();

  // Perform rotation
  x->setRight(y);
  y->setLeft(T2);

  // Update heights
  y->height = max(height(y->getLeft()),
   height(y->getRight())) + 1;
  x->height = max(height(x->getLeft()),
   height(x->getRight())) + 1;

  // Return new root
  return x;
 }
 BinaryTreeNode<T>* leftRotate(BinaryTreeNode<T>* x)
 {
  BinaryTreeNode<T>* y = x->getRight();
  BinaryTreeNode<T>* T2 = y->getLeft();

  // Perform rotation
  y->setLeft(x);
  x->setRight(T2);

  // Update heights
  x->height = max(height(x->getLeft()),
   height(x->getRight())) + 1;
  y->height = max(height(y->getLeft()),
   height(y->getRight())) + 1;

  // Return new root
  return y;
 }
 // Get Balance factor of node N
 int getBalance(BinaryTreeNode<T>* N)
 {
  if (N == NULL)
   return 0;
  return height(N->getLeft()) - height(N->getRight());
 }
 BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, T d)
 {
  if ((node) == NULL)
  {
   //new Node<T>();
   //new Node<T>(d);
   //new BinaryTreeNode<T>();
   //cout << "1. test" << endl;
   node = new BinaryTreeNode<T>(d);
  }
  if (d < (node)->getData()) {
   (node)->setLeft(insert(node->getLeft(), d));
  }
  else if (d > (node)->getData()) {
   //cout << "2. test" << endl;
//   (node)->setRight(new BinaryTreeNode<T>(d));
   (node)->setRight(insert(node->getRight(), d));
  }
  else {
   // Equal keys are not allowed in BST
   return node;
  }

  /* 2. Update height of this ancestor node */
  node->height = 1 + max(height(node->getLeft()),
   height(node->getRight()));
  //printf("node_data: %d, height: %d\n", node->getData(), node->height);

  /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
  int balance = getBalance(node);
  //printf("balance: %d\n", balance);

  // If this node becomes unbalanced, then there are 4 cases
  // Left Left Case
  if (balance > 1 && d < node->getLeft()->getData())
   return rightRotate(node);

  // Right Right Case
  if (balance < -1 && d > node->getRight()->getData())
   return leftRotate(node);

  // Left Right Case
  if (balance > 1 && d > node->getLeft()->getData())
  {
   node->setLeft(leftRotate(node->getLeft()));
   return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && d < node->getRight()->getData())
  {
   node->setRight(rightRotate(node->getRight()));
   return leftRotate(node);
  }

  return (node);
 }
 /* --- */
public:
  AVLTree()
  {
   /* ToDo */
   root = NULL;
  }
  void insert(T d)
  {
   /* ToDo */
   root = insert(root, d);
  }
 void inorder()
 {
  inorder(root, 0);
 }
  void show()
  {
   show(root);
   cout << endl;
  }
};

// https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// https://hub.packtpub.com/binary-search-tree-tutorial/

int main()
{
 AVLTree<int> *tree = new AVLTree<int>();
 srand(0);
 int j, k, i;
 for(j = 0;j < 20;j ++)
 {
  tree->insert(rand() % 100);
//  tree->inorder();
//  cout<<endl;
 }
 tree->inorder();
}
