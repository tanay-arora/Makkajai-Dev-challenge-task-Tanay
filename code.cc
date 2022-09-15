#include <iostream>
#include <vector>
using namespace std;

#define Fr(n,i) for(i=0;i<n;i++)

class LifeGame{
    int MR,MC,MI, *cords,*opr;
    public:
    int gi(int r,int c){
        return (r*MC+c);
    }
    LifeGame(){
        cout<<"write number of rows in grid: "; cin>>MR;
        cout<<"write number of cells in a row: "; cin>>MC;
        int x,y,i,j;
        MR++;MC++;
        cords=new int[MR*MC];
        opr=new int[MR*MC];
        Fr(MR,i) Fr(MC,j){cords[gi(i,j)]=0;opr[gi(i,j)]=0;}
        cout<<"write number of inputs: "; cin>>MI;
        cout<<"enter your inputs x y separating with space: \n";
        Fr(MI,i){cout<<i<<": ";cin>>x>>y;cords[gi(x,y)]=1;}
    }
    int LiveN(int r,int c){
        int count=0;
        bool A=((r+1)<MR),B=((c+1)<MC),C=((r-1)>-1),D=((c-1)>-1);
        if(A) count+=cords[gi(r+1,c)];
        if(B) count+=cords[gi(r,c+1)];
        if(C) count+=cords[gi(r-1,c)];
        if(D) count+=cords[gi(r,c-1)];
        if(A && B) count+=cords[gi(r+1,c+1)];
        if(C && D) count+=cords[gi(r-1,c-1)];
        if(B && C) count+=cords[gi(r-1,c+1)];
        if(A && D) count+=cords[gi(r+1,c-1)];
        return count;
    }
    int LifeC(int r,int c){
        int count = LiveN(r,c);
        if(count<2 || count>3) return 0;
        if(count>1 && count<=3 && cords[gi(r,c)] == 1 || count == 3) return 1;
        else return 0;
    }
    void drawMatrix(){
        int i,j;
        cout<<"before:"; Fr(MR,i){ cout<<"\n"; Fr(MC,j) cout<<cords[gi(i,j)]<<"  ";} cout<<"\n";
        cout<<"after:"; Fr(MR,i){ cout<<"\n"; Fr(MC,j) cout<<opr[gi(i,j)]<<"  ";}
    }
    void nextTick(){
        int i,j;
        cout<<"output: \n";
        Fr(MR,i) Fr(MC,j){ opr[gi(i,j)]=LifeC(i,j);if(opr[gi(i,j)]==1) cout<<i<<" "<<j<<"\n";}
        drawMatrix();
        cords=opr;
    }
    ~LifeGame(){
        delete opr;
    }
};

int main(){
    LifeGame I;
    I.nextTick();
}
