import numpy as np
import matplotlib.pyplot as plt


omega = np.loadtxt("res_euler_inc.dat", usecols = 0)
x2 = np.loadtxt("res_rk2_inc.dat", usecols = 1) ##rk2
x4 = np.loadtxt("res_rk4_inc.dat", usecols = 1) ##rk4
xe = np.loadtxt("res_euler_inc.dat", usecols = 1) ##euler






plt.figure(dpi=400)
plt.grid()
plt.xlabel("driving frequency $\omega$ in Hz")
plt.ylabel("Amplitude $A/\gamma$")
plt.title("resonance curve for increasing $\omega$")
plt.plot(omega,xe, lw = 0.5,label = "Euler")
plt.plot(omega,x2, lw = 0.5,label = "RK2")
plt.plot(omega,x4, lw = 0.5,label = "RK4")

plt.legend(loc = "upper right")
plt.savefig("rescurve_inc.pdf")
plt.show()




