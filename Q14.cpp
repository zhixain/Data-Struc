#include <iostream>
#include <stack>
#include <cctype>
using namespace std;
class ExpressionTree {
public:
  ExpressionTree(string exp) {
    string postfix = infixToPostfix(exp);
    stack<Node*> st;
    for (string::size_type i = 0; i < postfix.size(); ++i) {
      if (isdigit(postfix[i]) || postfix[i] == '.') {
        string operand;
        while (i < postfix.size() && (isdigit(postfix[i]) || postfix[i] == '.')) {
          operand += postfix[i];
          i++;
        }
        i--; // Move back to the last digit or dot
        Node* node = new Node(stod(operand)); // string to double
        st.push(node);
      }
      else if (isOperator(postfix[i])) {
        Node* right = st.top();
        st.pop();
        Node* left = st.top();
        st.pop();
        Node* node = new Node(postfix[i], left, right);
        st.push(node);
      }
    }
    root = st.top();
  }

  void inorder() {
    inorder(root);
    cout << endl;
  }

  void postorder() {
    postorder(root);
    cout << endl;
  }

  void preorder() {
    preorder(root);
    cout << endl;
  }

  double evaluate() {
    return evaluate(root);
  }

private:
  struct Node {
    char op;
    double val;
    Node* left;
    Node* right;
    Node(double v) : op(0), val(v), left(nullptr), right(nullptr) {}
    Node(char c, Node* l, Node* r) : op(c), val(0), left(l), right(r) {}
  };
  Node* root;

  void inorder(Node* node) {
    if (node == nullptr) {
      return;
    }
    inorder(node->left);
    if (node->op) {
      cout << node->op << " ";
    } else {
      cout << node->val << " ";
    }
    inorder(node->right);
  }

  void postorder(Node* node) {
    if (node == nullptr) {
      return;
    }
    postorder(node->left);
    postorder(node->right);
    if (node->op) {
      cout << node->op << " ";
    }
    else {
      cout << node->val << " ";
    }
  }

  void preorder(Node* node) {
    if (node == nullptr) {
      return;
    }
    if (node->op) {
      cout << node->op << " ";
    }
    else {
      cout << node->val << " ";
    }
    preorder(node->left);
    preorder(node->right);
  }

  double evaluate(Node* node) {
    if (node->op) {
      double left = evaluate(node->left);
      double right = evaluate(node->right);
      switch (node->op) {
        case '+':
          return left + right;
        case '-':
          return left - right;
        case '*':
          return left * right;
        case '/':
          return left / right;
      }
    } else {
      return node->val;
    }
      return 0;
  }
    int priority(char op) {
     switch(op) {
      case '+': case '-': return 1;
      case '*': case '/': return 2;
      default:            return 0;
     }
    }

  string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";
    for (string::size_type i = 0; i < infix.size(); ++i) {
      if (isdigit(infix[i]) || infix[i] == '.') {
        string operand;
        while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
          operand += infix[i];
          i++;
        }
        i--; // Move back to the last digit or dot
        postfix += operand + " ";
      }
      else if (infix[i] == '(') {
        st.push(infix[i]);
      }
      else if (infix[i] == ')') {
        while (!st.empty() && st.top() != '(') {
          postfix += st.top();
          postfix += " ";
          st.pop();
        }
        st.pop(); // Pop the opening parenthesis
      }
      else if (isOperator(infix[i])) {
          while (!st.empty() && st.top() != '(' && priority(st.top()) >= priority(infix[i])) {
            postfix += st.top();
            postfix += " ";
            st.pop();
          }
        st.push(infix[i]);
      }
    }

    while (!st.empty()) {
      postfix += st.top();
      postfix += " ";
      st.pop();
    }
      return postfix;
  }

  bool isOperator(char c) {
      return (c == '+' || c == '-' || c == '*' || c == '/');
  }
};

int main() {
    ExpressionTree expTree("2+(3*1)-9");
    cout << "Inorder traversal: ";
    expTree.inorder();
    
    cout << "Postorder expression: ";
    expTree.postorder();  
    
    cout << "Preorder traversal: ";
    expTree.preorder();
    
    cout << "Evaluation result: " << expTree.evaluate()<< endl;
    return 0;
}
