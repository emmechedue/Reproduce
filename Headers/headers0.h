#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<math.h>

using namespace std;

/****************List of errors:
    Error 1 is an error in the function upadateN
    */


void initializeGamma(double **G, double *Gamma,int M, double **Nc, double **Nd, double **x, double p, double s, double K){
    int i=0,j;
    
    j=0; //I have to create the first gamma by hand due to Gamma[0]
    G[0][0]=(1.+p*x[i][0])*Nc[i][0]*(1.-s);
    Gamma[0]=G[0][0];
    j++;
    G[0][1]=Nc[i][0]*(Nd[i][0]+Nc[i][0])/K; 
    Gamma[j]=Gamma[j-1]+G[0][1];
    j++;
    G[0][2]=(1.+p*x[i][0])*Nd[i][0];
    Gamma[j]=Gamma[j-1]+G[0][2];
    j++;
    G[0][3]=Nd[i][0]*(Nd[i][0]+Nc[i][0])/K; 
    Gamma[j]=Gamma[j-1]+G[0][3];
    j++;
    for(i=1; i<M;i++){ //Create the Gammas; the order is G_(0->C), G_(c->0), G_(0->D), G_(D->0) and start back for the new cell
       G[i][0]=(1.+p*x[i][0])*Nc[i][0]*(1.-s);
       Gamma[j]=Gamma[j-1]+G[i][0];
       j++;
       G[i][1]=Nc[i][0]*(Nd[i][0]+Nc[i][0])/K; 
       Gamma[j]=Gamma[j-1]+G[i][1];
       j++;
       G[i][2]=(1.+p*x[i][0])*Nd[i][0];
       Gamma[j]=Gamma[j-1]+G[i][2];
       j++;
       G[i][3]=Nd[i][0]*(Nd[i][0]+Nc[i][0])/K;
       Gamma[j]=Gamma[j-1]+G[i][3];
       j++; 
    }//Here I also computed the overall Gamma
    return;
}


int search(double *Gamma, int M, double x){ //Binary search
    int a,b,l,result;
    bool check;
    a=0;
    b=M-1;
    //cout<<endl<<"Random number is "<<x<<endl;
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

void updaterest(double **Nc, double **Nd,double **x, int l,int t, int M){//Copies all the others M-1 N's to step t!
    int i;
    if((l!=0)&&(l!=M-10)){
        for(i=0;i<l;i++){//I do in this way instad of doing M "if" that are always going to be true except that in one case!
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
        } 
        for(i=l+1;i<M;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
        } 
    }
    else{
        if(l==0){
            for(i=1;i<M;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            } 
        }
        else{
            for(i=0;i<M-1;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            } 
        }
    }
    return;
}

int updateN(double **Nc, double **Nd,double **x, int l,int t,int M){  //Updates the N; l is the chosen reation from G (the one given by search), t is the time step (the new one, is just the index of the for!)
    int m,k; //m is the cell where the change occurred, l is the occured reation and is returned by the function
    
    m=l/4;
    k=l%4;
    switch(k){ //Update the appropriate number
        case 0:
            Nc[m][t]=Nc[m][t-1]+1;
            Nd[m][t]=Nd[m][t-1];
            break;
        case 1:
            Nc[m][t]=Nc[m][t-1]-1;
            Nd[m][t]=Nd[m][t-1];
            break;
        case 2:
            Nd[m][t]=Nd[m][t-1]+1;
            Nc[m][t]=Nc[m][t-1];
            break;
        case 3:
            Nd[m][t]=Nd[m][t-1]-1;
            Nc[m][t]=Nc[m][t-1];
            break;
        default:
            cout<<"Error in updateN for the "<<t<<"-th step"<<endl;
            exit(1);
            break;
    }
    x[m][t]=Nc[m][t]/(Nc[m][t]+Nd[m][t]); //Update the x array
    updaterest(Nc,Nd,x,m,t,M);
    return m;
}

//***************PROVA!!!!********
/*int updateN(double **Nc, double **Nd,double **x, int l,int t,int M){  //Updates the N; l is the chosen reation from G (the one given by search), t is the time step (the new one, is just the index of the for!)
    int m,k; //m is the cell where the change occurred, l is the occured reation and is returned by the function
    
    m=l/4;
    k=l%4;
    cout<<"k is "<<k<<endl;
    cout<<"Nc is "<<Nc[m][t-1]<<"  Nd is "<<Nd[m][t-1]<<"  x is "<<x[m][t-1]<<endl<<"Then:"<<endl;
    switch(k){ //Update the appropriate number
        case 0:
            Nc[m][t]=Nc[m][t-1]+1;
            Nd[m][t]=Nd[m][t-1];
            break;
        case 1:
            Nc[m][t]=Nc[m][t-1]-1;
            Nd[m][t]=Nd[m][t-1];
            break;
        case 2:
            Nd[m][t]=Nd[m][t-1]+1;
            Nc[m][t]=Nc[m][t-1];
            break;
        case 3:
            Nd[m][t]=Nd[m][t-1]-1;
            Nc[m][t]=Nc[m][t-1];
            break;
        default:
            cout<<"Error in updateN for the "<<t<<"-th step"<<endl;
            exit(1);
            break;
    }
    x[m][t]=Nc[m][t]/(Nc[m][t]+Nd[m][t]); //Update the x array
    updaterest(Nc,Nd,x,m,t,M);
    cout<<"Nc is "<<Nc[m][t]<<"  Nd is "<<Nd[m][t]<<"  x is "<<x[m][t]<<endl<<endl;
    return m;
}

void updaterest(double **Nc, double **Nd,double **x, int l,int t, int M){//Copies all the others M-1 N's to step t!
    int i;
    cout<<endl<<"********rest*****"<<endl;
    if((l!=0)&&(l!=M-10)){
        for(i=0;i<l;i++){//I do in this way instad of doing M "if" that are always going to be true except that in one case!
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            cout<<"Nc is "<<Nc[i][t]<<"  Nd is "<<Nd[i][t]<<"  x is "<<x[i][t]<<endl<<endl;
        } 
        for(i=l+1;i<M;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            cout<<"Nc is "<<Nc[i][t]<<"  Nd is "<<Nd[i][t]<<"  x is "<<x[i][t]<<endl<<endl;
        } 
    }
    else{
        if(l==0){
            for(i=1;i<M;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            cout<<"Nc is "<<Nc[i][t]<<"  Nd is "<<Nd[i][t]<<"  x is "<<x[i][t]<<endl<<endl;
            } 
        }
        else{
            for(i=0;i<M-1;i++){
            Nc[i][t]=Nc[i][t-1];
            Nd[i][t]=Nd[i][t-1];
            x[i][t]=Nc[i][t]/(Nc[i][t]+Nd[i][t]);
            cout<<"Nc is "<<Nc[i][t]<<"  Nd is "<<Nd[i][t]<<"  x is "<<x[i][t]<<endl<<endl;
            } 
        }
    }
    cout<<"*******endrest"<<endl;
    return;
}*/
//****************************************


void updateG(double **G,double *Gamma, int m, double **Nc, double **Nd, double **x, double p, double s, double K,int t,int M){ //Update the array G[m][] with Nc, Nd and x at time t and the array Gamma
    double old[4];
    double sum;//Sum saves the difference of the old G[m][] with the new one;
    int i,a;
    
    for( i=0; i<4;i++){ //Save the changes of G[][]
        old[i]=G[m][i];
    }
    G[m][0]=(1.+p*x[m][t])*Nc[m][t]*(1.-s); //Updates the G[][]
    G[m][1]=Nc[m][t]*(Nd[m][t]+Nc[m][t])/K; 
    G[m][2]=(1.+p*x[m][t])*Nd[m][t];
    G[m][3]=Nd[m][t]*(Nd[m][t]+Nc[m][t])/K;
    sum=0;
    for(i=0;i<4;i++){ //Compute the change
        sum=sum+G[m][i]-old[i];
    }
    a=4*m;
    if(m==0){ //Update Gamma[4*m]; I need to do in this way due to m=0
        Gamma[0]=G[0][0];
    }
    else{
        Gamma[a]=Gamma[a-1]+G[m][0];
    }
    for(i=1;i<4;i++) //Update the part of the Gamma[i] due to m
    {
        Gamma[i+a]=Gamma[i+a-1]+G[m][i];
    }
    for(i=a+4;i<4*M;i++){ //I think this way is better because I have to make less calls (instead of Nd, Nc, x I just call sum)
        Gamma[i]=Gamma[i]+sum;
    }
    return;
}

double randlog(double Gamma){ //Generate the random number according to the distribution -ln(random[0,1]/Gamma)
    double x,r;
    
    r=rand01();
    x=-log(r)/Gamma;
    return x;
}

void printgamma(double *Gamma, int emme){
    int i;
    cout<<endl;
    for(i=0;i<emme;i++){
        cout<<Gamma[i]<<"  ";
    }
    cout<<endl;
    return;
}



