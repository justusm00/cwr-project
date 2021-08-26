import numpy as np
import matplotlib.pyplot as plt


omega = np.loadtxt("res_euler_inc.dat", usecols = 0)
x2 = np.loadtxt("res_rk2_inc.dat", usecols = 1) ##rk2
x4 = np.loadtxt("res_rk4_inc.dat", usecols = 1) ##rk4
xe = np.loadtxt("res_euler_inc.dat", usecols = 1) ##euler





plt.figure(1)
plt.grid()
plt.xlabel("$\omega$")
plt.ylabel("$x_\mathrm{max}$")
plt.title("Resonance curve for increasing $\omega$")
plt.plot(omega,xe, "r",label = "Euler")
plt.plot(omega,x2, "b", label = "RK2")
plt.plot(omega,x4, "c--", label = "RK4")

plt.legend(loc = "upper right")
plt.savefig("rescurve_inc.pdf",dpi = 400)
plt.show()



omega = np.loadtxt("res_euler_dec.dat", usecols = 0)
x2 = np.loadtxt("res_rk2_dec.dat", usecols = 1) ##rk2
x4 = np.loadtxt("res_rk4_dec.dat", usecols = 1) ##rk4
xe = np.loadtxt("res_euler_dec.dat", usecols = 1) ##euler




plt.figure(2)
plt.grid()
plt.xlabel("$\omega$")
plt.ylabel("$x_\mathrm{max}$")
plt.title("Resonance curve for decreasing $\omega$")
plt.plot(omega,xe, "r", label = "Euler")
plt.plot(omega,x2, "b", label = "RK2")
plt.plot(omega,x4, "c--", label = "RK4")

plt.legend(loc = "upper right")
plt.savefig("rescurve_dec.pdf",dpi = 400)
plt.show()

