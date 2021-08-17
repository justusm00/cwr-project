#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <our_numerics.h>
#include<tgmath.h>
#define PI 3.14159265358979323846





//Constants
//ODE parameters
const double gamma_ = 1.0;
const double beta = 2.0;
const double delta = 0.25;
const double alpha = 1.0;


const double t_max = 1000.0; //maximum time
const double delta_t = 0.01; //time step
const int dimension = 2; //dimension of the ODE system
static double omega; //driving frequence, declared as static so it doesn't have to be passed on to functions
static double phi; //to avoid phase shift after omega changes



//Output files
//Need two files for each algorithm, one for increasing and one for decreasing omega
static const char euler_res_inc[] = "res_euler_inc.dat";
static const char rk2_res_inc[] = "res_rk2_inc.dat";
static const char rk4_res_inc[] = "res_rk4_inc.dat";
static const char euler_res_dec[] = "res_euler_dec.dat";
static const char rk2_res_dec[] = "res_rk2_dec.dat";
static const char rk4_res_dec[] = "res_rk4_dec.dat";




//declaration of functions
int duffing_ode(double t, const double y[], double f[], void *params);
void ode_step(double t, double y[], int n);
double res(double y[], int n);







// #################################################################
// ########################### MAIN ################################
// #################################################################



int main()
{
	FILE* rescurve_inc[3] = {fopen(euler_res_inc, "w") , fopen(rk2_res_inc, "w") , fopen(rk4_res_inc, "w")}; //put files into pointer array so we can iterate through them
	FILE* rescurve_dec[3] = {fopen(euler_res_dec, "w") , fopen(rk2_res_dec, "w") , fopen(rk4_res_dec, "w")};
	
	
	// initial conditions (only for the first run)
	double x0 = 2.0;
	double v0 = 0.0;
	
	
	
	double y[dimension]; // system array
	double t; //time 
	
	//intialize y, omega and phi
	y[0] = x0;
	y[1] = v0;
	
	phi = 0.0;
	double omega_max = 5.0;
	double omega_min = 0.0;
	omega = omega_min;
	double delta_omega = 0.01;
	
	
	
	//Loops to compute resonance curves for each algorithm
	//First we consider increasing omega from 0 to 5
	for(int i = 0; i < 3; i++) //i determines if Euler (0), RK2 (1) or RK4 (2) is used
	{
		while(omega < omega_max) //increasing omega
		{	
			t = res(y,i); //After this step, y[0] contains the amplitude. Need t to compute the new phi
			fprintf(rescurve_inc[i], "%lf\t%lf\n", omega, y[0]); //Print resonance curve
			phi = fmod((omega * t + phi), (2 * PI)); //Compute new phi
			omega += delta_omega; //Increase omega
			
		}
		//Re-initialize before repeating with next algorithm
		y[0] = x0;
		y[1] = v0;
		phi = 0.0;
		omega = omega_min;
		
		
	}
	
	
	
	//Now we repeat the process but with omega decreasing from 5 to 0
	omega = omega_max;
	for(int i = 0; i < 3; i++) //i determines if Euler (0), RK2 (1) or RK4 (2) is used
	{
		while(omega > omega_min) //Increasing omega
		{	
			t = res(y,i); //After this step, y[0] contains the amplitude. Need t to compute the new phi
			fprintf(rescurve_dec[i], "%lf\t%lf\n", omega, y[0]); //Print resonance curve
			phi = fmod((omega * t + phi), (2 * PI)); //Compute new phi
			omega -= delta_omega; //Decrease omega
			
		}
		//Re-initialize before repeating with next algorithm
		y[0] = x0;
		y[1] = v0;
		phi = 0.0;
		omega = omega_max;
		
		
	}
	
	//Close files
	for(int i = 0; i < 3; i++)
	{
		fclose(rescurve_inc[i]);
		fclose(rescurve_dec[i]);
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

