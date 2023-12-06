#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node{
public:
    Node(){
        Node(0, 0);
    }
    Node(int r, int c){
        row = r;
        col = c;
    }
    
    int getRow() { return row; }
    int getCol() { return col; }
    
    void setRow(int r){
        if(r >= 0 && r < SIZE)
            row = r;
    }
    void setCol(int c){
        if(c >= 0 && c < SIZE)
            col = c;
    }
private:
    int col, row;
};

class List{
public:
    List(){
        top = 0;
    }
    void addElement(int r, int c){
        data[top].setRow(r);
        data[top].setCol(c);
        top++;
    }
    Node *removeElement(){
        top--;
        return &data[top];
    }
    
    void printList(){
        int j;
        for(j = 0;j < top;j ++){
            cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
        }
    }
private:
    Node data[SIZE * SIZE];
    int top;
};

class Maze{
public:
    Maze(){
        initMaze(SIZE);
    }
    void initMaze(int s){//s : size
        int j, k;
        maze = (int **)malloc(s*sizeof(int *)); //配置空間，maze裡面存的是地址，會指向整數的地址
        for (j = 0; j < SIZE; j++){
            maze[j] = (int *)malloc(s * sizeof(int));//配置空間，儲存整數
        }
        srand(time(0));
        for (j = 0; j < SIZE; j++){
            for (k = 0; k < SIZE; k++){
                if (j == 0 && k == 0 && maze[j][k] == 1)
                    maze[j][k] = 0;
                else if (j == SIZE-1 && k == SIZE-1 && maze[j][k] == 1)
                    maze[j][k] = 0;
                else{
                    //建立20%的牆壁
                    int val;
                    if(rand() %10 <= 2)val = 1;
                    else val = 0;
                    maze[j][k] = val;
                    
                }
            }
        }
    }
    bool check(int x, int y, List *list){
        if (x == SIZE-1 && y == SIZE-1) return true; // 如果到了終點，回傳「真」值出去。
        if (maze[x][y] == 1 || wasHere[x][y]) return false;// 如果撞到牆或已經來過這一點，回傳「假」值出去。
        wasHere[x][y] = true;
        if (x==0 && y==0 && maze[x][y]==0)
            list->addElement(x, y);
        if (x != 0)//檢查是不是最頂
        {
            list->addElement(x - 1, y);
            if (check(x - 1, y, list)) {
                correctPath[x][y] = true;
                return true;
            }
            list->removeElement();
        }
        if (x != SIZE - 1)//檢查是不是最底
        {
            list->addElement(x + 1, y);
            if (check(x + 1, y, list)) {
                correctPath[x][y] = true;
                return true;
            }
            list->removeElement();
        }
        if (y != 0)//檢查是不是最左
        {
            list->addElement(x, y - 1);
            if (check(x, y - 1, list)) {
                correctPath[x][y] = true;
                return true;}
            list->removeElement();
        }
        if (y != SIZE - 1)//檢查是不是最右
        {
            list->addElement(x, y + 1);
            if (check(x, y + 1, list)) {
                correctPath[x][y] = true;
                return true;
            }
            list->removeElement();
        }
        return false;
    }
    List *getPath(){
        List *list = new List;
        //初始化wasHere和correctpath
        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++) {
                wasHere[row][col] = false;
                correctPath[row][col] = false;
            }
        }
        check(0, 0, list);
        return list;
    }
    void printMaze(){
        int j, k;
        for(j = 0;j < SIZE;j ++){
            for(k = 0;k < SIZE;k ++){
                if(maze[j][k] == 0)
                    cout<<" ";
                else if(maze[j][k] == 1)
                    cout<<"*";
            }
            cout<<"\n";
        }
    }
private:
    int **maze;
    bool wasHere[SIZE][SIZE];
    bool correctPath[SIZE][SIZE];
};

int main(){
    Maze *maze = new Maze();
    maze->printMaze();
    maze->getPath()->printList();
    return 0;
}
