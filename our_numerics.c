#include<tgmath.h>
#include<stdlib.h>
#include "our_numerics.h"
#include<stdio.h>
#include<time.h>
#include<gsl/gsl_rng.h>
#include <gsl/gsl_histogram.h>

#define PI 3.14159265358979323846




void euler_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params)
{
	double *f = malloc((int)(sizeof(double) * dimension));
	func(t,y,f,params);
	for(int i = 0; i < dimension; i++)
	{
		y[i] += delta_t * (*(f + i));
	}
	free(f);
	


}



void rk2_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params)
{
	
	double *support = malloc((int)(sizeof(double) * dimension));
	double *k1 = malloc((int)(sizeof(double) * dimension));
	double *k2 = malloc((int)(sizeof(double) * dimension));
	func(t,y,k1,params);   //calculate k1
	for(int i = 0; i < dimension; i++)
	{
		k1[i] *= delta_t; //multiply each element by delta_t
	}
	for(int i = 0; i < dimension; i++)
	{
		support[i] = y[i] + 0.5 * k1[i]; //fill support array
	}
	func(t + 0.5 * delta_t,support,k2,params);  //calculate k2 at support and new t
	for(int i = 0; i < dimension; i++)
	{
		k2[i] *= delta_t; //multiply each element by delta_t
	}
	for(int i = 0; i < dimension; i++)
	{
		y[i] += k2[i]; 
	}
	free(support);
	free(k1);
	free(k2);
	



}





void rk4_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params)
{
	double a1 = 0.5;   //parameters
	double a2 = 0.5;
	double a3 = 1.0;
	double w1 = 1.0/6.0;
	double w2 = 1.0/3.0;
	double w3 = 1.0/3.0;
	double w4 = 1.0/6.0;
	double *support = malloc((int)(sizeof(double) * dimension));
	double *k1 = malloc((int)(sizeof(double) * dimension));
	double *k2 = malloc((int)(sizeof(double) * dimension));
	double *k3 = malloc((int)(sizeof(double) * dimension));
	double *k4 = malloc((int)(sizeof(double) * dimension));
	
	//#####################  k1 ###################
	
	func(t,y,k1,params);   //calculate k1
	for(int i = 0; i < dimension; i++)
	{
		k1[i] *= delta_t; //multiply each element by delta_t
	}
	
	
	//#####################  k2 ###################
	for(int i = 0; i < dimension; i++)
	
	{
		support[i] = y[i] + a1 * k1[i]; //fill support array for k2
	}
	func(t + a1 * delta_t,support,k2,params);  //calculate k2 at support and new t
	
	for(int i = 0; i < dimension; i++)
	{
		k2[i] *= delta_t; //multiply each element by delta_t
	}
	
	
	//#####################  k3 ###################
	
	
	for(int i = 0; i < dimension; i++)
	{
		support[i] = y[i] + a2 * k2[i]; //fill support array for k3
	}
	
	func(t + a2 * delta_t,support,k3,params);  //calculate k3 at support and new t
	
	for(int i = 0; i < dimension; i++)
	{
		k3[i] *= delta_t; //multiply each element by delta_t
	}
	
	
	//#####################  k4 ###################
	
	for(int i = 0; i < dimension; i++)
	{
		support[i] = y[i] + a3 * k3[i]; //fill support array for k4
	}
	
	func(t + a3 * delta_t,support,k4,params);  //calculate k4 at support and new t
	
	for(int i = 0; i < dimension; i++)
	{
		k4[i] *= delta_t; //multiply each element by delta_t
	}
	
	for(int i = 0; i < dimension; i++)
	{
		y[i] = y[i] +  w1 * k1[i] +  w2 * k2[i] + w3 * k3[i] + w4 * k4[i]; //calculate new y
	}
	free(support);
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	



}
