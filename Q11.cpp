#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

class Tree{
public:
    Tree(){
        int j;
        for (j = 0; j < 2000; j++)
            root[j] = -1;
    }

    void insert(int node){
        int index = 0;
        while (index < 2000 && root[index] != -1){
            if (root[index] < node)
                index = index * 2 + 2;//右
            else
                index = index * 2 + 1;//左
        }
        root[index] = node;
    }

    void inorder(int index)
    {//左中右
        if (index >= 2000 || root[index] == -1)
            return;
        inorder(index * 2 + 1);
        cout << root[index] << " ";
        inorder(index * 2 + 2);
    }

    void preorder(int index)
    {//中左右
        if (index >= 2000 || root[index] == -1)
            return;
        cout << root[index] << " ";
        preorder(index * 2 + 1);
        preorder(index * 2 + 2);
    }

    void postorder(int index)
    {//左右中
        if (index >= 2000 || root[index] == -1)
            return;
        postorder(index * 2 + 1);
        postorder(index * 2 + 2);
        cout << root[index] << " ";
    }

    void levelorder()
    {
        int index = 0;
        queue<int> q;
        q.push(index);

        while (!q.empty())
        {
            index = q.front();
            q.pop();
            if (index >= 2000 || root[index] == -1)
                continue;

            cout << root[index] << " ";
            q.push(index * 2 + 1);
            q.push(index * 2 + 2);
        }
    }

    void inorder()
    {
        inorder(0);
        cout << endl;
    }

    void preorder()
    {
        preorder(0);
        cout << endl;
    }

    void postorder()
    {
        postorder(0);
        cout << endl;
    }

private:
    int root[2000];
};

int main()
{
    Tree *tree = new Tree();
    int j, node;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
    {
        node = rand();
        tree->insert(node);
    }
    tree->inorder();
    printf("\n");
    tree->preorder();
    printf("\n");
    tree->postorder();
    printf("\n");
    tree->levelorder();
    printf("\n");
    return 0;
}


