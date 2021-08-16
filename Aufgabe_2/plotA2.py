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


plt.plot(omega, anal, "r", label="analytical")
plt.plot(omega, eul, "g", label="euler")
plt.plot(omega, rk2, "b", label="rk2")
plt.plot(omega, rk4, "c", label="rk4")
plt.legend()
plt.grid()
plt.xlabel(r"$\omega$")
plt.ylabel(r"$x_{max}$")
plt.show()