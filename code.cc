#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define Alive true
#define Dead false
#define ToBool(n) (n==1)?Alive:Dead
#define Fr(n,i,v) for(i=v;i<n;i++)
#define upState(i,j,p,n) n.cellByIndex(i,j,p.LivingNeighboursCount(i,j))
#define copyState(i,j,p,n) p.cellByIndex(i,j,-1,n.cellByIndex(i,j))
struct graph{
    int x;
    int y;
};

class Cell{
        bool alive;
    public:
        Cell();
        void changeState(bool state);
        void updateLife(int LivingNeighboursCount);
        bool isAlive();
};
Cell::Cell(){
    alive = Dead;
}
void Cell::changeState(bool state){
    alive = state;
}
void Cell::updateLife(int LivingNeighboursCount){
    if(alive && LivingNeighboursCount>3)
        alive = Dead;
    else if(alive && LivingNeighboursCount<2)
        alive = Dead;
    else if(LivingNeighboursCount ==3)
        alive = Alive;
}
bool Cell::isAlive(){
    return alive;
}

class VectOpr:public Cell{
    public:
        void loadElements(int size,vector<vector<Cell>> &vect);
};

void VectOpr::loadElements(int size,vector<vector<Cell>> &vect){
    vect.resize(size); int i;
    Fr(size,i,0) vect[i].resize(size);
}

class Grid:public VectOpr{
    vector<vector<Cell>> Cells;
    public:
        int size();
        void resizeGrid(int size);
        bool IsInGrid(int maxSize, int x, int y);
        int LivingNeighboursCount(int x, int y);
        bool cellByIndex(int x,int y,int LivingNeighboursCount,int state);
};
bool Grid::cellByIndex(int x,int y,int LivingNeighboursCount=-1,int state=-1){
    if(LivingNeighboursCount!=-1) Cells[x][y].updateLife(LivingNeighboursCount);
    if(state!=-1) Cells[x][y].changeState(ToBool(state));
    return Cells[x][y].isAlive();
}
void Grid::resizeGrid(int size){
    loadElements(size,Cells);
}
bool Grid::IsInGrid(int maxSize, int x, int y){
    return ((x>=0 && x < maxSize) && (y>=0 && y< maxSize ));
}
int Grid::LivingNeighboursCount(int x, int y){
    int count=0,i,j,n=size();
    Fr(x+2,i,x-1) Fr(y+2,j,y-1)
        if(IsInGrid(n,i,j) && !(x==i && y==j))
            count+= cellByIndex(i,j);
    return count;
}
int Grid::size(){
    return Cells.size();
}
class Game:public Grid{
    Grid preGrid,newGrid;
    public:
        void nextTick(int n);
        void Start();
        int readInput(vector<graph> &V);
        void setInitialSeed(vector<graph> &V);
        void showResult();
};
int Game::readInput(vector<graph> &V){
    int n=0,i,j,pos,x,y;
	string In;
	while(getline(cin,In)){
		if(In.empty()) break;
		pos = In.find(",");
        x=stoi(In.substr(0,pos));
        y=stoi(In.substr(pos+1));
		V.push_back({x,y});
		if(x>n)n=x; if(y>n)n=y;
    }
    return ++n;
}
void Game::setInitialSeed(vector<graph> &V){
    int i;
    Fr(V.size(),i,0) preGrid.cellByIndex(V[i].x,V[i].y,-1,1);
}
void Game::nextTick(int T){
    int s,i,j,n=preGrid.size();
    Fr(T,s,0){
        Fr(n,i,0) Fr(n,j,0) copyState(i,j,newGrid,preGrid);
        Fr(n,i,0) Fr(n,j,0) upState(i,j,preGrid,newGrid);
        Fr(n,i,0) Fr(n,j,0) copyState(i,j,preGrid,newGrid);
    }
}
void Game::Start(){
    vector<graph> V;
    int n=readInput(V);
    preGrid.resizeGrid(n);
    newGrid.resizeGrid(n);
    setInitialSeed(V);
}
void Game::showResult(){
    int i,j,n=preGrid.size();
    Fr(n,i,0) Fr(n,j,0) if(preGrid.cellByIndex(i,j)) cout<<i<<","<<j<<"\n";
}

int main(){
    Game myGame;
    myGame.Start();
    myGame.nextTick(1);
    myGame.showResult();
    return 0;
}
