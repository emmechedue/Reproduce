#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<iostream>

using namespace std;

const int N=100;

int search(double *Gamma, int M, double x);

int main(){
    double M[N];
    int i,l;
    
    for(i=0; i<N;i++){
        M[i]=(double)i/N;
    }
    for(i=0; i<N; i++){
        cout<<"i= "<<i<<"   M[i]= "<<M[i]<<endl;
    }
    cout<<endl<<endl<<endl;
    l=search(M,N,0.2998);
    cout<<endl<<"********* l="<<l<<" *********"<<endl;
    return 0;
}



int search(double *Gamma, int M, double x){ //Binary search
    int a,b,l,result;
    bool check;
    a=0;
    b=M-1;
    do{
        l=(a+b)/2;
        if(x<=Gamma[l]){
            if(x>=Gamma[l-1]){result=l;
            check=true;}
            else{
                b=l;
                check=false;}
            }
        else{
            if(x<=Gamma[l+1]){
                result=l+1;
                check=true;
            }
            else{
                a=l;
                check=false;}
        }
    }while(check==false);
   return result; 
}


    
