#include<iostream>
#include<cstdlib>

using namespace std;

class Node{
public:
    Node()
    {
        data = 0;
        next = NULL;
    }
    int data;
    struct Node *next;
};

class Set
{
public:
    Set(){
      element = NULL;
    }

    int addElement(int e){
      if(contains(e))return 0;
      
      Node *newNode = new Node();
      newNode->data = e;
      if(element == NULL){
        element = newNode;
      }
      else{
        Node *cur = element;
        while(cur->next != NULL){
          cur = cur->next;
        }
        cur->next = newNode;
      }
      return 1;
    }

    Set *unions(Set *b){
      Set *result = new Set();
      Node *cur = element;
      while(cur != NULL){
        result->addElement(cur->data);
        cur = cur->next;
      }
      cur = b->element;
      while (cur != NULL) {
            result->addElement(cur->data);
            cur = cur->next;
        }
      return result;
    }

    Set *intersetcions(Set *b){
      Set *result = new Set();
      Node *cur = element;
      
      while(cur!= NULL){
        if(b->contains(cur->data)){
          result ->addElement(cur-> data);
        }
        cur = cur->next;
      }
      return result;
    }

    bool equivalent(Set *b){
      if(this->size()!= b->size()){
        return false;
      }
      Node *cur = element;
      while(cur!=NULL){
        if(!b->contains(cur->data))return false;
        cur = cur->next;
      }
      return true;
    }
    
    void listAll()
    {
        Node *cur = element;
        while(cur != NULL)
        {
            cout<<cur->data<<" ";
            cur = cur->next;
        }
    }
private:
  Node *element;
  bool contains(int e){
    Node *cur = element;
    while(cur!=NULL){
      if(cur->data == e)return true;
      cur = cur->next;
    }
    return false;
  }
  
  int size(){
    int cnt = 0;
    Node *cur = element;
    while(cur!= NULL){
      cnt++;
      cur = cur->next;
    }
    return cnt;
  }
};

int main()
{
    Set *a = new Set();
    Set *b = new Set();
    Set *c;
    Node *cur;
    
    a->addElement(1);
    a->addElement(2);
    a->addElement(3);
    b->addElement(3);
    b->addElement(4);
    b->addElement(5);
    b->addElement(5);
    
    c = a->unions(b);
    c->listAll();
    
    c = a->intersetcions(b);
    c->listAll();
    
    if(a->equivalent(b) == 0)
        cout<<"Not equivalent.\n";
    else
        cout<<"Equivalent!\n";
}
