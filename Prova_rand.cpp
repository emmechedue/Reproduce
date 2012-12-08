#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<iostream>
#include<myrand.h>
#include<headers1.h>
#include<mymath.h>

using namespace std;

int main(){
    double y;
    ofstream file;
    const char nomefile[]="prova.txt";
    int i;
    double Nc[3],Nd[3],x[3];
    
    for(i=0; i<3;i++){
        Nc[i]=0;
        Nd[i]=i+1;
        x[i]=0.27;
    }
    
    
    file.open(nomefile,ios::out|ios::trunc);
    myprint(Nc,Nd,x,0.392,3, file);
    
    return 0;
}
