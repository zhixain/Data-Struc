#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid{
    public:
    Grid(){
        Grid(0);
    }
    Grid(int s){
        state = s;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
        
        wasHere = false;/**/
    }
    Grid *getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid *g) { dir[d] = g; }
    void setState(int s) { state = s;}
    
    void setWasHere(int s) { wasHere = s;}/* +++ */
    bool getWasHere() { return wasHere; }/* --- */
    
    private:
    Grid *dir[4];
    int state;
    bool wasHere;/* --- */
};

struct List{
    public:
    List(){
        top = 0;
    }
    void addElement(Grid *g){
        data[top++] = g;
    }
    Grid *removeElement(){
        top--;
        return data[top];
    }
 void printPath()
 {
  int j;
  for(j = 1;j < top;j ++)
  {
   if(data[j] == data[j - 1]->getDir(UP))
   {
    cout<<"UP\n";
   }
   else if(data[j] == data[j - 1]->getDir(DOWN))
   {
    cout<<"DOWN\n";
   }
   else if(data[j] == data[j - 1]->getDir(LEFT))
   {
    cout<<"LEFT\n";
   }
   else if(data[j] == data[j - 1]->getDir(RIGHT))
   {
    cout<<"RIGHT\n";
   }
  }
 }
private:
 Grid *data[SIZE * SIZE];
 int top;
};

class Maze
{
public:
 Maze()
 {
  initMaze(SIZE);
 }
 void initMaze(int s){
  int j, k;
  Grid* grids[SIZE][SIZE];

  for (j = 0; j < SIZE; j++){
   for (k = 0; k < SIZE; k++){
    grids[j][k] = new Grid(0);
   }
  }
  srand(time(0));
  for (j = 0; j < SIZE; j++){
   for (k = 0; k < SIZE; k++){
    int val;
    if(rand()%10>=2)val= 0;
    else val = 1;
    grids[j][k]->setState(val);
    if (k != 0){
        grids[j][k]->setDir(LEFT, grids[j][k - 1]);
    }
    
    if (k != SIZE-1){
        grids[j][k]->setDir(RIGHT, grids[j][k + 1]);
    }
    if (j != 0){
        grids[j][k]->setDir(UP, grids[j-1][k]);
    }
    if (j != SIZE - 1){
        grids[j][k]->setDir(DOWN, grids[j+1][k]);
    }
    if (j == 0 && k == 0 && grids[j][k]->getState() ==1)
     grids[j][k]->setState(0);
    if (j == SIZE - 1 && k == SIZE - 1 && grids[j][k]->getState() == 1)
     grids[j][k]->setState(0);
   }
  }
  maze = grids[0][0];
 }
 bool recursiveSolve(Grid *grid, List *list){
  if (grid->getDir(RIGHT) == NULL && grid->getDir(DOWN) == NULL && grid->getState() == 0)
   return true; //到達終點
  
  // 撞牆或已走過
  if (grid->getState() == 1 || grid->getWasHere() == true)
        return false;

  grid->setWasHere(true);

  if (grid->getDir(LEFT) == NULL && grid->getDir(UP) == NULL && grid->getState() == 0){
      list->addElement(grid);
  }

 // 檢查是否到最左
  if (grid->getDir(LEFT) != NULL) {
      list->addElement(grid->getDir(LEFT));
      if (recursiveSolve(grid->getDir(LEFT), list))return true;
      list->removeElement();
  }
  
  // 檢查是否到最右
  if (grid->getDir(RIGHT) != NULL){
      list->addElement(grid->getDir(RIGHT));
      if (recursiveSolve(grid->getDir(RIGHT), list))return true;
      list->removeElement();
  }
  
  //檢查是否到最頂
  if (grid->getDir(UP) != NULL){
      list->addElement(grid->getDir(UP));
      if (recursiveSolve(grid->getDir(UP), list))return true;
      list->removeElement();
  }
  
  //檢查是否到最底
  if (grid->getDir(DOWN) != NULL){
      list->addElement(grid->getDir(DOWN));
      if (recursiveSolve(grid->getDir(DOWN), list))return true;
      list->removeElement();
  }
  return false;
 }
 List *getPath(){
  List* list = new List;
  recursiveSolve(maze, list);
  return list;
 }
 void printMaze(){
  Grid *j = maze, *k;
  while(j != NULL){
   k = j;
   while(k != NULL){
    cout<< k->getState();
    k = k->getDir(RIGHT);
   }
   cout<<endl;
   j = j->getDir(DOWN);
  }
  //一行一行列出，如果一行列完，呼叫down ，繼續印下一行
 }
private:
 Grid *maze;
};

int main(){
 Maze *maze = new Maze();
 maze->printMaze();
 maze->getPath()->printPath();
}
