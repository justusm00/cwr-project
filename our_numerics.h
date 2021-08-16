#ifndef OURNUMERICS_H
#define OURNUMERICS_H


/*pointer to function*/
typedef
int ode_func(double, const double[], double[], void * );



//------------INTEGRATION ALGORTIHMS---------------------





//euler algorithm to solve ode systems
void euler_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params);


//rk2 algorithm to solve ode systems
void rk2_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params);

//rk4 algorithm to solve ode systems
void rk4_step(double t, double delta_t, double y[], ode_func func, int dimension, void* params);


#endif
