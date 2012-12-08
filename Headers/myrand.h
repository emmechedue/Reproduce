#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<math.h>

using namespace std;



// ===============================================================
// multiple recursive generator MRGk5-93 from 
//  
//  L'Ecuyer, Blouin, Couture: 
//  A search for good multiple recursive random number generators
//  ACM Trans. Modeling and Comp. Sim. Vol.3, No. 2, p 87-98 (1993)
// 
// periode 2^155
// da long long, muss jede multiplikation und Addition < 2^64
// ===============================================================

double rand01( ) {
  unsigned long long a1,a5,m, s1,s5;
  // 1/(m+1)
  double Invmp1=4.656612873077393e-10;

  static unsigned long long x1,x2,x3,x4,x5; 
  static bool first=true;

  // initialize
  if(first) {
    x1=1; x2=2; x3=3; x4=4; x5=5;
    first=false;
  }

  m  = 2147483647;  // m=2^31-1
  a1 = 107374182;
  a5 = 104480;

  // the congruence part I
  s1 = (a1*x1) % m;
  s5 = (a5*x5) % m;

  // shift
  x5=x4; x4=x3; x3=x2; x2=x1;
  
  // the congruence part II
  x1 = (s1 + s5) % m;

  // return uniform in (0,1)
  if(x1 == 0) { 
    return m * Invmp1;
  } else {
    return x1 * Invmp1;
  }
}

double randgauss(){
	static bool nuovo=true;
	static double x1, x2;
	double v,u;

	if(nuovo==false){
		nuovo=true;
		return x2;
	}
	else{
		nuovo=false;
		v=rand01();
		u=rand01();
		double Pi= 3.141592653589793238462643383279502884197169399;

		x1=(sin(2*Pi*v))*sqrt(-2*log(u));
		x2=(cos(2*Pi*v))*sqrt(-2*log(u));

		return x1;
	}
}

int randpoiss(double lambda){
	int i,x;
	double p,s,u;
	bool ver;

	i=0;//Initialize
	ver=true;
	p=exp(-lambda);
	s=p;
	u=rand01();

	while(ver){
		if(u<s){
			x=i;
			ver=false;
		}
		else{
			p=lambda*p/(i+1);
			s=p+s;
			i++;
		}
	}
	return x;
}
