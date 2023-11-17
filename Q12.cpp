#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
/*++++++++++++++++*/
#include<queue>
#include<vector>
#include<map>
//*<map> is use for operator and size() */
using namespace std;
/*++++++++++++++++*/
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
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out<<*(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out<<*(n->data);
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }
protected:
    T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
    ListNode() : Node<T>()
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d)
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(ListNode *p, ListNode *n) : Node<T>()
    {
        prev = p;
        next = n;
    }
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
    {
        prev = p;
        next = n;
    }
    ListNode *getNext() const
    {
        return next;
    }
    ListNode *getPrev() const
    {
        return prev;
    }
    void setNext(ListNode *n)
    {
        next = n;
    }
    void setPrev(ListNode *p)
    {
        prev = p;
    }
    ListNode &operator=(T d)
    {
        this->setData(d);
        return *this;
    }
private:
    ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
    LinkList()
    {
        head = NULL;
        tail = NULL;
    }
    void addFromHead(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if(tail == NULL)
            tail = node;
    }
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if(head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d)
    {
        if(!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if(at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if(node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        if(head != NULL)
        {
            head = head->getNext();
            if(head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    ListNode<T> *removeFromTail()
    {
        ListNode<T> *n = tail;
        if(tail != NULL)
        {
            tail = tail->getPrev();
            if(tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if(!exist(n))
            return NULL;
        if(n == head)
            return removeFromHead();
        if(n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for(k = 0;k < i && j != NULL;k ++)
            j = j->getNext();
        if(j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while(j != NULL)
        {
            std::cout<<(*j)<<" ";
            j = j->getNext();
        }
        std::cout<<std::endl;
    }
protected:
    ListNode<T> *head, *tail;
};

/*
    Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
    A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template<class T>
class TreeNode : public Node<T>
{
public:
    TreeNode() : Node<T>(){
        child = new LinkList<TreeNode<T> *>();
    }
    TreeNode(T d) : Node<T>(d){
        child = new LinkList<TreeNode<T> *>();
    }
    /*
        Add a child to this node.
    */
    void addChild(TreeNode *n){
        child->addFromTail(n);
    }
    /*
        Add a child to this node.
    */
    void addChild(T d){
        child->addFromTail(new TreeNode<T>(d));
    }
    /*
        Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n){
        return(*child)[n].getData();
    }
    //(*child)[n] is from the function I set(operator overloading) and it is a ptr.use getData() to get the value
    
    
private:
    LinkList<TreeNode<T> *> *child;
};

/*
    Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.
    
*/
template<class T>
class Tree
{
public:
    Tree(){
      root = NULL;
    }
    /*
        return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n){
      if(root == NULL)return NULL;
      queue<TreeNode<T>*>q;
      q.push(root);
      TreeNode<T>*cur = q.front();
      q.pop();
      for(int i = 0 ; i < n ; i++){
        int j = 0 ;
        while(true){
          try{
            TreeNode<T> *t = (*cur)[j];
            //現在的節點的第幾個子節點
            q.push(t);
          }
          catch(invalid_argument e){
            break;
            //no element in (*cur)[j]
          }
          j++;
        }
        cur = q.front();
        q.pop();
      }
      return cur;
    }
    /*
        return the number of nodes on this tree.
    */
    int count(){
      if(root == NULL)return 0;
      queue<TreeNode<T>*>q;
      q.push(root);
      int cnt = 0 ;
      
      while(!q.empty()){
        int size = q.size();
        cnt+= size;
        for(int i = 0 ; i < size ; i++){
          TreeNode<T> *cur = q.front();
          q.pop();
          int j = 0 ;
          while(true){
            try{
              TreeNode<T>*t = (*cur)[j];
              q.push(t);
            }
            catch(invalid_argument e){
              break;
            }
            j++;
          }
        }
      }
      return cnt;
    }
    /*
        print all the node on this tree with level order.
    */
    void levelOrder(){
      if(root == NULL)return;
      
      queue<TreeNode<T>*>q;
      q.push(root);
      
      while(!q.empty()){
        int size = q.size();
        for(int i = 0 ; i < size ; i++){
          TreeNode<T> *cur = q.front();
          q.pop();
          cout<<cur<<" ";
          
          int j = 0;
          while(true){
            try{
              TreeNode<T> *t = (*cur)[j];
              q.push(t);
            }
            catch(invalid_argument e){
              break;
            }
            j++;
          }
        }
      }
      //cout<<endl;
    }
    /*
        print all the node on this tree with preorder.
    */
  //root -> left ->right
    void preorder(){
      _preorder(root);
    }
    /*
        print all the node on this tree with postorder.
    */
  // left->right->root
    void postorder(){
      _postorder(root);
    }
    /*
        set the root of this tree.
    */
    void setRoot(T d){
      root = new TreeNode<T>(d);
    }
      
      TreeNode<T> *getRoot(){
      return root;
    }
  
private:
    TreeNode<T> *root;
      void _preorder(TreeNode<T> *r){
      if(r == NULL)return;
      cout << r << " ";
      int j = 0 ;
      while(1){
        try{
          _preorder((*r)[j]);
        }
        catch(invalid_argument e){
          break;
        }
        j++;
      }
    }
      void _postorder(TreeNode<T> *r){
      if(r == NULL)return;
      int j = 0 ;
      while(true){
        try{
          _postorder((*r)[j]);
        }
        catch(invalid_argument e){
          break;
        }
        j++;
      }
      cout<<r<<" ";
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    srand(0);
    int j, k, i;
    for(j = 0;j < 20;j ++)
    {
        if(tree->count() == 0)
            tree->setRoot(rand() % 100);
        else
        {
            k = rand() % tree->count();
            (*tree)[k]->addChild(rand() % 100);
        }
    }
    cout<<"count: ";
    cout<<tree->count()<<endl;
    
    cout<<"LevelOrder: ";
    tree->levelOrder();
    cout<<endl;
    
    cout<<"PreOrder: ";
    tree->preorder();
    cout<<endl;
    
    cout <<"PostOrder: ";
    tree->postorder();
    cout <<endl;
    return 0;
}
