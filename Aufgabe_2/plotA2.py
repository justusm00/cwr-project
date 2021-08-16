import numpy as np
import matplotlib.pyplot as plt



file = np.loadtxt("resonance.txt", delimiter=",")

omega = []
anal = []
eul = []
rk2 = []
rk4 = []


for row in file:
    omega.append(row[0])
    anal.append(row[1])
    eul.append(row[2])
    rk2.append(row[3])
    rk4.append(row[4])


plt.figure(1)
plt.plot(omega, anal, "r", label="Analytical")
plt.plot(omega, eul, "g", label="Euler")
plt.plot(omega, rk2, "b", label="RK2")
plt.plot(omega, rk4, "c", label="RK4")
plt.legend()
plt.grid()
plt.xlabel(r"$\omega$")
plt.ylabel(r"$x_{max}$")
plt.title(r"Resonance Curve. $\alpha = 0, \beta = 2.0, \gamma = 1.0, \delta = 0.25, \Delta t = 0.01, t_{max} = 1000$")
plt.savefig("Aufgabe2.pdf", dpi=200)
plt.show()



file = np.loadtxt("diff.txt", delimiter=",")

omega = []
eul = []
rk2 = []
rk4 = []


for row in file:
    omega.append(row[0])
    eul.append(row[1])
    rk2.append(row[2])
    rk4.append(row[3])






plt.figure(2)
plt.plot(omega, eul, "g", label="Euler")
plt.plot(omega, rk2, "b", label="RK2")
plt.plot(omega, rk4, "c", label="RK4")
plt.legend()
plt.yscale("log")
plt.grid()
plt.xlabel(r"$\omega$")
plt.ylabel(r"$|x_{max}^{num} - x_{max}^{ana}|$")
plt.title(r"Differences. $\alpha = 0, \beta = 2.0, \gamma = 1.0, \delta = 0.25, \Delta t = 0.01, t_{max} = 1000$")
plt.savefig("Aufgabe2_2.pdf", dpi=200)
plt.show()


