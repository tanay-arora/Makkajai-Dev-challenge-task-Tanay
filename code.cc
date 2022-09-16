#include <iostream>
using namespace std;

#define Fr(n,i) for(i=0;i<n;i++)

class graph{
	int i,j;
	public:
		int x();
		int y();
		void setValue(int x,int y);
};
class cell{
	bool Alive = false;
	public:
		void changeState(bool state);
		bool IsAlive();
};
class grid:public cell{
	cell *arr;
	int row_len,col_len;
	public:
		void setGridSize(int x,int y);
		void deleteGrid();
		int rowSize();
		int colSize();
		int getIndex(int x,int y);
		bool IsValid(int x,int y);
		int countNeighbours(graph *CP,int x,int y);
		bool willSurvive(graph *CP,int x,int y);
		void updateCellState(int x,int y,bool state);
		bool getState(int x,int y);
};
class game{
	grid G1,G2;
	public:
		void setGraph(graph arr[]);
		void nextTick(graph *CP);
		void start();
		void drawOutput();
		void end();
};

void grid::setGridSize(int x,int y){
	row_len=x+1;
	col_len=y+1;
	arr = new cell[row_len*col_len];
}
inline void grid::deleteGrid(){
	delete arr;
}
inline int grid::rowSize(){
	return row_len;
}
inline int grid::colSize(){
	return col_len;
}
inline int grid::getIndex(int x,int y){
	return (x*col_len+y);
}
bool grid::IsValid(int x,int y){
	if(x>=0 && x<row_len && y>=0 && y<col_len) return true;
	else return false;
}
int grid::countNeighbours(graph *CP,int x, int y){
	int n=0,i,s,t;
	Fr(8,i){
		s=x+CP[i].x();
		t=y+CP[i].y();
		if(IsValid(s,t)) n+=getState(s,t);
	} 
	return n;
}
bool grid::willSurvive(graph *CP,int x,int y){
	int n=countNeighbours(CP,x,y);
	if(n<2 || n>3) return false;
	if(n>1 && n<4 && getState(x,y) || n==3) return true;
	else return false;
}
inline void grid::updateCellState(int x,int y,bool state){
	arr[getIndex(x,y)].changeState(state);
}
inline bool grid::getState(int x,int y){
	return arr[getIndex(x,y)].IsAlive();
}

inline bool cell::IsAlive(){
	return Alive;
}
inline void cell::changeState(bool state){
	Alive=state;
}

void game::nextTick(graph *CP){
	int row_size=G1.rowSize(), col_size=G1.colSize();
	G2.setGridSize(row_size,col_size);
	int i,j;
	Fr(row_size,i) Fr(col_size,j) 
	if(G1.willSurvive(CP,i,j)) G2.updateCellState(i,j,true);
	else G2.updateCellState(i,j,false);

}
void game::start(){
	int m,n,I,x,y,j,i;
	cout<<"write number of rows in grid: "; cin>>m;
    cout<<"write number of cells in a row: "; cin>>n;
	G1.setGridSize(m,n);
	cout<<"write number of inputs: "; cin>>I;
    cout<<"enter your inputs x y separating with space: \n";
	Fr(I,j){
		cin>>x>>y;
		G1.updateCellState(x,y,true);
	}
}
void game::setGraph(graph arr[]){
    arr[0].setValue(1,0);
    arr[1].setValue(0,1);
    arr[2].setValue(-1,0);
    arr[3].setValue(0,-1);
    arr[4].setValue(1,1);
    arr[5].setValue(-1,-1);
    arr[6].setValue(-1,1);
    arr[7].setValue(1,-1);
}
void game::drawOutput(){
	int i,j,row_size=G1.rowSize(), col_size=G1.colSize();
	cout<<"Output\n";
	Fr(row_size,i) Fr(col_size,j) if(G2.getState(i,j)) cout<<i<<" "<<j<<"\n"; 
	cout<<"Input graph\n";
	Fr(row_size,i){Fr(col_size,j) cout<<G1.getState(i,j)<<" ";cout<<"\n";}
	cout<<"Output graph\n";
	Fr(row_size,i){Fr(col_size,j) cout<<G2.getState(i,j)<<" ";cout<<"\n";}
}
void game::end(){
	G1.deleteGrid();
	G2.deleteGrid();	
}

inline int graph::x(){
    return i;
}
inline int graph::y(){
    return j;
}
void graph::setValue(int x,int y){
	i=x;
	j=y;
}

int main() {
	game myGame;
	graph CP[8];
	myGame.setGraph(CP);
	myGame.start();
	myGame.nextTick(CP);
	myGame.drawOutput();
	myGame.end();
	return 0;
}
