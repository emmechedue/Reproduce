#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<gsl/gsl_rng.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(){
	unsigned int seed;
	gsl_rng *r;
	double rand;
	FILE *pfile;
	pfile = fopen ("/dev/urandom", "r");
	fread (&seed, sizeof (seed), 1, pfile);
	cout<<"The seed is: "<<seed<<" ";
	r = gsl_rng_alloc (gsl_rng_taus);
	gsl_rng_set (r, seed);
	rand=gsl_rng_uniform (r);
	cout<<"and the sampled number is: "<<rand<<endl;
	return 0;
}
	
