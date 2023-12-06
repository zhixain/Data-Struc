#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

class Tree{
public:
    Tree()
    {
        int j, k;
        for (j = 0; j < 20; j++)
            for (k = 0; k < 4; k++)
                root[j][k] = -1;
    }

    int insert(int node)
    {
      //root[index][0] 紀錄現在的node有沒有被佔用，有：1，沒有：-1
      //root[index][1] 儲存當前node的值
      //root[index][2] 儲存左子樹的index
      //root[index][3] 儲存右子樹的index
      int f = 0, index = 0;
        while (root[index][0] != -1)
            index++;
        if (index >= 20)
            return -1;
        if (index == 0){
            root[0][0] = 1;
            root[0][1] = node;
            return 1;
        }
        else{
            root[index][0] = 1;
            root[index][1] = node;
            while (1){
                if (root[f][1] < node)
                {
                    if (root[f][3] == -1)
                    {
                        root[f][3] = index;
                        return 1;
                    }
                    else
                    {
                        f = root[f][3];
                    }
                }
                else
                {
                    if (root[f][2] == -1)
                    {
                        root[f][2] = index;
                        return 1;
                    }
                    else
                    {
                        f = root[f][2];
                    }
                }
            }
        }
    }

    void inorder(int index)
    //左中右
    {
        if (index != -1)
        {
            inorder(root[index][2]);
            cout << root[index][1] << " ";
            inorder(root[index][3]);
        }
    }

    void preorder(int index)
    {//中左右
        if (index != -1)
        {
            cout << root[index][1] << " ";
            preorder(root[index][2]);
            preorder(root[index][3]);
        }
    }

    void postorder(int index)
    {//左右中
        if (index != -1)
        {
            postorder(root[index][2]);
            postorder(root[index][3]);
            cout << root[index][1] << " ";
        }
    }

    void levelorder()
    {
        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int index = q.front();
            q.pop();//到過就可以刪除

            if (index != -1)
            {
                cout << root[index][1] << " ";
                q.push(root[index][2]);
                q.push(root[index][3]);
            }
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
    int root[20][4];
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

