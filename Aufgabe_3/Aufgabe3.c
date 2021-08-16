#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <our_numerics.h>
#include<tgmath.h>
#define PI 3.14159265358979323846





//constants

const double gamma_ = 1.0;
const double beta = 2.0;
const double delta = 0.25;
const double alpha = 1.0;
const double t_max = 1000.0;
const double delta_t = 0.01;
const int dimension = 2;
static double omega;
static double phi;



//output files
static const char euler_res_name[] = "res_euler.dat";
static const char rk2_res_name[] = "res_rk2.dat";
static const char rk4_res_name[] = "res_rk4.dat";




//declaration of functions
int duffing_ode(double t, const double y[], double f[], void *params);
void ode_step(double t, double y[], int n);
double res(double y[], int n);







// #################################################################
// ########################### MAIN ################################
// #################################################################



int main()
{
	FILE* rescurve[3] = {fopen(euler_res_name, "w") , fopen(rk2_res_name, "w") , fopen(rk4_res_name, "w")};
	double x0 = 2.0;
	double v0 = 0.0;
	
	
	// system arrays
	double y[dimension]; 
	double t;
	y[0] = x0;
	y[1] = v0;
	omega = 0.0;
	phi = 0.0;
	double omega_max = 5.0;
	double delta_omega = 0.01;
	
	
	for(int i = 0; i < 3; i++)
	{
		while(omega < omega_max)
		{	
			t = res(y,i);
			fprintf(rescurve[i], "%lf\t%lf\n", omega, y[0]);
			phi = fmod((omega * t + phi), (2 * PI));
			omega += delta_omega;
			
		}
		y[0] = x0;
		y[1] = v0;
		phi = 0.0;
		omega = 0.0;
		
		
	}
	
	
	for(int i = 0; i < 3; i++)
	{
		fclose(rescurve[i]);
	}
	
	return 0;

}






//########################### FUNCTIONS ############################






//implementation of the Duffing Oscillator's ODE


int duffing_ode(double t, const double y[], double f[], void *params)
{
	f[0] = y[1];
	f[1] = gamma_ * cos(omega * t) - delta * y[1] - beta * y[0] - alpha * y[0] * y[0] * y[0];
	return 0;
}




/* function to do integrations steps
   n determines which algorithm is used: 0 -> Euler, 1 -> RK2, 2 -> RK4
*/

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





//function to return amplitude

double res(double y[], int n)
{
	
	double t0 = 0.0;
	// for the comparison of amplitudes
	double amp1 = 0;
	double amp2 = 0;

	// solving it numerically
	while (t0 < t_max)
	{


		// doing a step with the current algorithm
		ode_step(t0,y,n);

            
            
		// finding max amplitude. Letting the system run for half the time to stabilize
		if (t0 > t_max / 2)
		{
			// the comparison structure is: amp1 - amp2 - x[0]
			if ((y[0] < amp2) && (amp1 < amp2)) break;
		}
            
		// updating amplitudes
		amp1 = amp2;
		amp2 = y[0];

		t0 += delta_t;
        }
        return t0;

}

