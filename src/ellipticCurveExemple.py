import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

x = np.linspace(-10, 10, 1000000)
y = np.sqrt(x**3 - 7*x + 10)
yl = -np.sqrt(x**3 - 7*x + 10)
fa = x + 1
fb = x/3 + 3

#Plot das funções
ax.plot(x, y, color='blue', label='y^2 = x^3 - 7x + 10')
ax.plot(x, yl, color='blue')
ax.plot(x, fa, color='orange', label='y = x + 1')
ax.plot(x, fb, color='pink', label='y = x/3 + 3')

#Pontos
ax.scatter(-3, -2, color='red', s=20, zorder=2)
ax.scatter(-3, 2, color='red', s=20, zorder=2)
ax.scatter(1/9, 82/27, color='red', s=20, zorder=2)
ax.scatter(1/9, -82/27, color='red', s=20, zorder=2)

#Zero axis
ax.axhline(0, color='black', linestyle='-.')
ax.axvline(0, color='black', linestyle='-.')

#Proporção
#ax.set_aspect("equal")

ax.set_title("Elliptic curve")
ax.set_xlabel("x")
ax.set_ylabel("f(x)")

ax.legend(loc='upper left')

plt.show()