#include<stdio.h>
#include<stdlib.h>
#include "../our_numerics.h"
#include<tgmath.h>
#include<math.h>
#include<string.h>


// declaration of functions
int duff_ode(double t, const double y[], double f[], void *params);
double x_max_analytical(double omega);
double x_max_numerical(char *s, double omega, double alpha, double delta_t, double t_max);





// ############### CONSTANTS ##############
const double gamma_ = 1.0;   //amplitude of force
const double beta = 2.0;    // undamped frequency squared
const double delta = 0.25;  //friction coeff.
const int dimension = 2; // dimension of the system



// #################################################################
// ########################### MAIN ################################
// #################################################################

int main(){

    // file for saving data
    FILE *reson = fopen("resonance.txt", "w");
    FILE *differ = fopen("diff.txt", "w");

    // specific values used in calculations
    double alpha = 0.0;
    // lenght of step
    double delta_t = 0.01;
    // maximal time. This has to be high for the low frequency calculations
    double t_max = 1000;


    // strings for different types of solver
    char eul[] = "Euler";
    char rk2[] = "RK2";
    char rk4[] = "RK4";

    // filling file. 
    for (double omega = 0.01; omega < 3; omega+=0.01){
        // resonance curve. structure: omega, analytical, euler, rk2, rk4
        fprintf(reson, "%f,%f,%f,%f,%f\n", omega, x_max_analytical(omega), x_max_numerical(eul, omega, alpha, delta_t, t_max), x_max_numerical(rk2, omega, alpha, delta_t, t_max), x_max_numerical(rk4, omega, alpha, delta_t, t_max));

        // difference between analytical and numerical curves.
        fprintf(differ, "%f,%f,%f,%f\n", omega, fabs(x_max_numerical(eul, omega, alpha, delta_t, t_max) -  x_max_analytical(omega)), 
        fabs(x_max_numerical(rk2, omega, alpha, delta_t, t_max) -  x_max_analytical(omega)), fabs(x_max_numerical(rk4, omega, alpha, delta_t, t_max) -  x_max_analytical(omega)));
    }

    // closing file
    fclose(reson);
    fclose(differ);
    return 0;
}



//########################### FUNCTIONS ############################

/**
 * @brief System function of the Duffing Oscillator
 * 
 * @param t time
 * @param y array of the current parameters, i.e. position and velocity
 * @param f array for the system function
 * @param params parameters. here the pointer points on alpha and omega (in that order)
 */
int duff_ode(double t, const double y[], double f[], void *params){
    // setting alpha. casting it from void to double

    double alpha = *((double*)params);

    // setting omega

    double omega = *((double*)params + 1);

    // first entry to system function is velocity
    f[0] = y[1];

    // system function for acceleration
    f[1] = gamma_ * cos(omega * t) - delta * y[1] - beta * y[0] - alpha * y[0] * y[0] * y[0]; 

    return 0;
}


/**
 * @brief Analytical solution of the resonance curve of a harmonic oscillator 
 * 
 * @param omega frequency of external force
 * @return double max amplitude
 */
double x_max_analytical(double omega){
    // intermediate calculation
    double betom = (beta - omega * omega);
    // return
    return gamma_ / sqrt(betom * betom + delta * delta * omega * omega);
}


/**
 * @brief Function that calculates the maximum amplitude by solving the system and checking for local maximum
 * 
 * @param s         String with what methode is to be used. Choices are "Euler", "RK2" and "RK4"
 * @param omega     Frequency of external force
 * @param alpha     parameter for the non-linear part
 * @param delta_t   time step
 * @param t_max     max time
 * @return double   max amplitude
 */
double x_max_numerical(char *s, double omega, double alpha, double delta_t, double t_max){
    //array for parameters
    double param[2] = {alpha, omega};

    // pointer for function and RK
    void *parameters = param;

    // max amplitude
    double ampl_max = 0;


    // for euler method
    if (strcmp(s, "Euler") == 0){
        // array for position and velocity
        double *x = (double*)malloc(sizeof(double) * 2);

        // initial conditions
        x[0] = 2;
        x[1] = 0;

        // time
        double t0 = 0;

        // for the comparison of amplitudes
        double amp1 = 0;
        double amp2 = 0;

        // solving it numerically
        while (t0 < t_max){


            // doing a step with euler
            euler_step(t0, delta_t, x, duff_ode, dimension, parameters);

            
            
            // finding max amplitude. Letting the system run for half the time to stabilize
            if (t0 > t_max / 2){
                // the comparison structure is: amp1 - amp2 - x[0]. Here amp2 has to be larger than x[0], but also larger than amp1, so that it sits on the peak
                if ((x[0] < amp2) && (amp1 < amp2)) {
                    ampl_max = amp2;
                    break;
                }
                
            }
            
            // updating amplitudes
            amp1 = amp2;
            amp2 = x[0];

            t0 += delta_t;
        }
        


        free(x);
        return ampl_max;

    }


    //##########################################################################################
    //################################### FOR RK2 ##############################################
    //##########################################################################################
    else if (strcmp(s, "RK2") == 0){
        // array for position and velocity
        double *x = (double*)malloc(sizeof(double) * 2);

        // initial conditions
        x[0] = 2;
        x[1] = 0;

        // time
        double t0 = 0;

        // for the comparison of amplitudes
        double amp1 = 0;
        double amp2 = 0;

        // solving it numerically
        while (t0 < t_max){


            // doing a step with euler
            rk2_step(t0, delta_t, x, duff_ode, dimension, parameters);

            
            
            // finding max amplitude. Letting the system run for half the time to stabilize
            if (t0 > t_max / 2){
                // the comparison structure is: amp1 - amp2 - x[0]
                if ((x[0] < amp2) && (amp1 < amp2)) {
                    ampl_max = amp2;
                    break;
                }
                
            }
            
            // updating amplitudes
            amp1 = amp2;
            amp2 = x[0];

            t0 += delta_t;
        }
        


        free(x);
        return ampl_max;

    }


    //##########################################################################################
    //################################### FOR RK4 ##############################################
    //##########################################################################################
    else if (strcmp(s, "RK4") == 0){
        // array for position and velocity
        double *x = (double*)malloc(sizeof(double) * 2);

        // initial conditions
        x[0] = 2;
        x[1] = 0;

        // time
        double t0 = 0;

        // for the comparison of amplitudes
        double amp1 = 0;
        double amp2 = 0;

        // solving it numerically
        while (t0 < t_max){


            // doing a step with euler
            rk4_step(t0, delta_t, x, duff_ode, dimension, parameters);

            
            
            // finding max amplitude. Letting the system run for half the time to stabilize
            if (t0 > t_max / 2){
                // the comparison structure is: amp1 - amp2 - x[0]
                if ((x[0] < amp2) && (amp1 < amp2)) {
                    ampl_max = amp2;
                    break;
                }
                
            }
            
            // updating amplitudes
            amp1 = amp2;
            amp2 = x[0];

            t0 += delta_t;
        }
        


        free(x);
        return ampl_max;

    }
    return 0;
}



