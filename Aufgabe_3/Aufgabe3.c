#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <our_numerics.h>
#define PI 3.14159265358979323846


//constants

const double gammma = 1.0;
const double beta = 2.0;
const double delta = 0.25;
const double alpha = 1.0;
const double tmax = 10.0;
const double delta_t = 1e-3;
const int dimension = 2;
static double omega;
static double phi;



//output files
static const char euler_res_name[] = "res_euler.dat";
static const char rk2_res_name[] = "res_rk2.dat";
static const char rk4_res_name[] = "res_rk4.dat";


//physical system


int duffing_ode(double t, const double y[], double f[], void *params)
{
	f[0] = y[1];
	f[1] = gammma * cos(omega * t + phi) - delta * y[1] - beta * y[0] - alpha * pow(y[0],3);
	return 0;
}




// function to decide which algorithm to use

void ode_step(double t, double y[], int n)
{
	switch(n)
	{
		case 0: euler_step(t, delta_t, y, duffing_ode, dimension, NULL); break;
		case 1: rk2_step(t, delta_t, y, duffing_ode, dimension, NULL); break;
		case 2: rk4_step(t, delta_t, y, duffing_ode, dimension, NULL); break;
	}
	return;
}





//function to compute amplitude

double res(double y[], int n)
{
	//transient process
	double t = 0.0;
	while(t < tmax)
	{
		ode_step(t,y,n);
		t += delta_t;
	}



	// find maximum x
	double x_current = y[0];
	double x_next;

	ode_step(t,y,n);
	x_next = y[0];
	t += delta_t;
	
	while(x_current < x_next)
	{
		x_current = x_next;
		ode_step(t,y,n);
		x_next = y[0];
		t += delta_t;
	
	}
	
	return t;

}





// ------------------------ MAIN ---------------------



int main()
{
	FILE* rescurve[3] = {fopen(euler_res_name, "w") , fopen(rk2_res_name, "w") , fopen(rk4_res_name, "w")};
	double x0 = 2.0;
	double v0 = 0.0;
	
	
	// system arrays
	double y[dimension]; 
	y[0] = x0;
	y[1] = v0;
	double t = 0.0;
	omega = 1.0;
	double omega_max = 5.0;
	double delta_omega = 1e-2;
	phi = 0.0;
	
	for(int i = 0; i < 3; i++)
	{
		while(omega < omega_max)
		{	
			t = res(y,i);
			fprintf(rescurve[i], "%lf\t%lf\n", omega, fabsf(y[0]));
			phi = fmod((omega * t + phi), 2 * PI);
			omega += delta_omega;
			t = 0.0;
			
		}
		y[0] = x0;
		y[1] = v0;
		omega = 1.0;
		
		
	}
	
	
	for(int i = 0; i < 3; i++)
	{
		fclose(rescurve[i]);
	}
	
	return 0;

}
