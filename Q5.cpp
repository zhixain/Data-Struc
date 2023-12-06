#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
    Node()
    {
        next = NULL;
        pre = NULL;
    }
    Node(int n)
    {
        data = n;
        next = NULL;
        pre = NULL;
    }
    int getData() { return data; }
    Node *getNext() { return next; }
    Node *getPre() { return pre; }
    void setData(int d) { data = d; }
    void setNext(Node *n) { next = n; }
    void setPre(Node *p) { pre = p; }
private:
    int data;
    Node *next, *pre;
};

class List
{
public:
    List() { list = NULL; }
    List(int n) { generate(n); }
    
    void generate(int n)
    {
        int j;
        list = NULL;
        for(j = 0;j < n;j ++)
            generate();
    }
    
    void generate()
    {
        Node *buf = new Node(rand());
        buf->setNext(list);
        if(list != NULL)
            list->setPre(buf);
        list = buf;
    }
  void bubbleSort(){
    if(list == NULL)return;
    bool swap;
    Node *end = NULL;
    
    do{
      swap = false;
      Node *current = list;
      Node *prev = NULL;
      
      while(current -> getNext() != NULL){
        if(current->getData() > current -> getNext() -> getData()){
          int temp = current->getData();
          current ->setData(current->getNext()->getData());
          current ->getNext()->setData(temp);
          swap = true;
        }
        prev = current;
        current = current ->getNext();
      }
      end = current;
      
    }while(swap);
  }
    
    void selectionSort(){
      if(list == NULL)return;
      Node *current;
      Node *minNode;
      for(current = list ; current != NULL ; current = current->getNext()){
        Node *search;
        minNode = current;
        for(search = current ->getNext(); search!=NULL; search = search->getNext()){
          if(search->getData() < minNode->getData()){
            minNode = search;
          }
        }
        int temp = current->getData();
        current->setData(minNode->getData());
        minNode->setData(temp);
      }
    }

void insertionSort(){
  if(list == NULL)return ;
  Node *current = list;
  
  while(current!=NULL){
    Node *prev = current->getPre();
    while(prev!=NULL && prev->getData() > current->getData()){
      current->setData(prev->getData());
      current = prev;
      prev = current->getPre();
    }
    current = current->getNext();
  }
}

    
    void print()
    {
        Node *cur = list;
        while(cur != NULL)
        {
            cout<<cur->getData()<<" ";
            cur = cur->getNext();
        }
        cout<<endl;
    }
private:
    Node *list;
};

int main()
{
    srand(time(NULL));
    List *l = new List(10);
    l->print();
    l->bubbleSort();
    l->print();
    
    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();
    
    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
}
