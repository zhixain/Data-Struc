#include <iostream>
#include <string>
using namespace std;
const int ALPHABET_SIZE = 26;
class Node {
public:
    bool isEndOfWord;
    Node* children[ALPHABET_SIZE];
    char data;
    int cnt;
    int level;
    char tab;
    Node* parent;
    Node(char d) {
        isEndOfWord = false;
        data = d;
        cnt = 0;//the num of child nodes
        parent = NULL;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = NULL;
        }
    }
};
class Trie {
public:
    Node* root;
    Trie() {
        root = new Node(0);
    }
    bool search(string key) {
        Node* current = root;
        for (int i = 0; i < key.length(); i++) {
            if (current->children[0] == NULL) {
                return false;
            }
            int index = -1;
            for (int j = 0; j < 26; j++) {
                if (current->children[j] != NULL && current->children[j]->data == key[i]) {
                    index = j;//找key的開頭在trie的位置
                    break;
                }
            }
            if (index == -1) {
                return false;
            }//not exist in trie
            current = current->children[index];
        }
        return (current != NULL && current->isEndOfWord);
    }
    void insert(string value) {
        Node* current = root;
        Node* parent = NULL;
        int index = 0;
        for (int i = 0; i < value.length(); i++) {
            if (current->children[0] == NULL) {
                current->children[index] = new Node(value[i]);
                current->cnt++;
            }
            else {
                index = -1;
                for (int j = 0; j < 26; j++) {
                    if (current->children[j] != NULL && current->children[j]->data == value[i]) {
                        index = j;
                        break;
                    }
                }
                if (index == -1) {
                    for (index = 0; index < 26; index++) {
                        if (current->children[index] == NULL) {
                            current->children[index] = new Node(value[i]);
                            current->cnt++;
                            break;
                        }
                    }
                }
            }
            parent = current;
            current = current->children[index];
            current->level = i + 1;
            current->parent = parent;
            index = 0;
        }
        current->isEndOfWord = true;
    }
    
    void preorderHelper(Node* current) {
        if (!current) return;
        if (current->data == 0) {
            current->tab = 0;
            cout << "[]" << endl;
        }
        else {
            if ((current->parent->cnt == 1) && (current->parent == this->root)) {
                current->tab = current->parent->tab + 1;
            }
            if (current->parent->cnt >= 2) {
                Node* pre_temp;
                pre_temp = current->parent;
                while (pre_temp->tab < 0) {
                    pre_temp = pre_temp->parent;
                }
                current->tab = pre_temp->tab + 1;
            }
            else if ((current->parent->cnt == 1) && (current->parent->isEndOfWord == true)) {
                Node* pre_temp;
                pre_temp = current->parent;
                while (pre_temp->tab < 1) {
                    pre_temp = pre_temp->parent;
                }
                current->tab = pre_temp->tab + 1;
            }
            for (int i = 0; i < current->tab; i++) {
                cout << "  ";
            }
            cout << current->data;
            if ((current->isEndOfWord == 1) || (current->cnt >= 2)) {
                cout << endl;
            }
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            preorderHelper(current->children[i]);
        }
    }
    void preorder() {
        preorderHelper(root);
    }
};

int main() {
    Trie* trie = new Trie();
    string command, key, value;
    while (1) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie->insert(value);
        }
        else if (command == "search") {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        }
        else if (command == "print") {
            trie->preorder();
        }
        else if (command == "exit") {
            break;
        }
    }
    return 0;
}
