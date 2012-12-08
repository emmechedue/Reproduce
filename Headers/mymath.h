#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cmath>

using namespace std;

int powint(int x, int a){
	int i=0;
	int geppo=1;
	for(i=0;i<a;i++){
		geppo=geppo*x;
	}
	return geppo;
}

double divint(int a, int b){
    double da,db,res;
    da=(double) a;
    db=(double) b;
    res=da/db;
    return res;
}
