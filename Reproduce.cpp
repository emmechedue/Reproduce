#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<iostream>
#include<myrand.h>
#include<headers0.h>

using namespace std;

//**********Initializations**********
const int N0=4; //Initial number of bacteria in each cell
const int Nc0=2;//Initial number of cooperators in each cell
const int T=10000; //Simulations steps
const int M=1; //Number of cells
const double s=0.05; //Selection's strenght
const double p=10.; //Cooperators advantage
const double K=100.; //Carrying capacity

int main(){
    double **Nc, **Nd, **x; //Coop. #, Def. # and fraction of coop. ****In form of N[cell][time]
    double t[T]; //time
    int i,l,m,emme=4*M;
    double Gamma[emme]; //The array with all the partial sums
    double **G; //Matrix with all the gammas for all the cells in form of G[cell][reaction]
    double r;
    double AvN[T],Avx[T]; //Average values
    ofstream file;
    const char filename[]="output.txt";
    
    //*********Let's initialize all**********
    t[0]=0.; 
    Nc=new double* [M];  //Create the MxT matrices
    Nd=new double* [M];
    x=new  double* [M];
    for(i=0; i<M; i++){
        Nc[i]=new double[T];
        Nd[i]=new double[T];
        x[i]=new double[T];
    }
    for(i=0; i<M; i++){ //Initialize the matrices
        Nc[i][0]=Nc0;
        Nd[i][0]=N0-Nc0;
        x[i][0]=Nc[i][0]/(Nc[i][0]+Nd[i][0]);
    }
    G=new double* [M]; //Create the Mx4 gamma matrix
    for(i=0; i<M; i++){
        G[i]=new double[4];
    }
    initializeGamma(G,Gamma,M,Nc,Nd,x,p,s,K);
    //*******end of initialization*********
    
    //*****Start of the evolution***********
    for(i=1;i<T;i++){ 
        //printgamma(Gamma,emme);
        t[i]=t[i-1]+randlog(Gamma[emme-1]); //Samples the time at wich the next thing happens;
        //cout<<"check 1"<<endl;
        r=rand01()*Gamma[emme-1]; //Generates the random number to choose the reaction!
        r=Gamma[emme-1]-r;
        //cout<<"check 2"<<endl;
        l=search(Gamma,emme,r); //Finds the reaction
        //cout<<"check 3"<<endl;
        m=updateN(Nc, Nd,x,l,i,M); //Update the variables at time i and returns the cell where the reaction happened
        //cout<<"check 4"<<endl;
        updateG(G,Gamma,m,Nc,Nd,x,p,s,K,i,M); //Update the G and the Gamma
        //cout<<"check 5"<<endl;
        if((i%10)==0){cout<<"i is "<<i<<endl;} //Just a check
    }
    //**********end of the evolution***********
    
    //Taking the average on M and printing
    file.open(filename,ios::out|ios::trunc);
    file<<"#Results for the simulation reproducing the old results with"<<endl;
    file<<"# M="<<M<<"  T="<<T<<"  K="<<K<<"  s="<<s<<"  p="<<p<<"  N0="<<N0<<"  Nc0="<<Nc0<<endl;
    file<<"#Time  N   x"<<endl;
    
    //cout<<endl<<endl;
    for(l=0;l<T;l++){
        AvN[l]=0;
        Avx[l]=0;
        //cout<<endl<<"time= "<<l<<endl;
        for(i=0;i<M;i++){
            AvN[l]=AvN[l]+Nc[i][l]+Nd[i][l];
            Avx[l]=Avx[l]+x[i][l];
            //cout<<Nc[i][l]+Nd[i][l]<<"  ";
        }
        AvN[l]=AvN[l]/M;
        Avx[l]=Avx[l]/M;
        file<<t[l]<<"   "<<AvN[l]<<"   "<<Avx[l]<<endl;
    }
    file.close(); 
    
    
    return 0;
}
