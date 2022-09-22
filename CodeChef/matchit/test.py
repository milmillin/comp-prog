import random
import matplotlib.pyplot as plt
import collections
import numpy as np
import sys

n = 5

val = np.zeros((n, n))

for i in range(n):
    for j in range(n):
        val[i][j] = i;

fig = plt.figure()
ax = fig.add_subplot(111)

ax.axis([0, n, 0, n])
ax.set_aspect(1)

heatmap = ax.pcolor(val, cmap = 'RdYlGn')
fig.colorbar(heatmap, ax = ax)

plt.show()



