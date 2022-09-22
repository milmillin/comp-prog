import random
import matplotlib.pyplot as plt
import collections
import numpy as np
import sys

n = 0
m = 0

xs = []
ys = []

def readInput():
    global n, m, xs, ys, val
    inputs = open(sys.argv[1]).read().split()
    ptr = 0
    n = int(inputs[ptr])
    ptr += 1
    m = int(inputs[ptr])
    ptr += 1
    
    for i in range(2 * m):
        xs.append(int(inputs[ptr]) + 0.5)
        ptr += 1
        ys.append(int(inputs[ptr]) + 0.5)
        ptr += 1

    val = np.zeros((n + 1, n + 1), dtype=int)

    for i in range(n):
        for j in range(n):
            val[j + 1][i + 1] = int(inputs[ptr])
            ptr += 1

pthsx = []
pthsy = []

def readOutput():
    global n, m, pthsx, pthsy
    inputs = open(sys.argv[2]).read().split()
    ptr = 0
    for i in range(m):
        sz = int(inputs[ptr])
        ptr += 1
        pthx = []
        pthy = []
        for j in range(sz):
            x = int(inputs[ptr])
            ptr += 1
            y = int(inputs[ptr])
            ptr += 1
            pthx.append(x + 0.5)
            pthy.append(y + 0.5)
        pthsx.append(pthx)
        pthsy.append(pthy)


if len(sys.argv) != 3:
    print("python viz.py inputfile outputfile")
    sys.exit()

readInput()
readOutput()

fig = plt.figure()
ax = fig.add_subplot(111)

ax.axis([1, n + 1, 1, n + 1])
ax.set_aspect(1)

heatmap = ax.pcolor(val, cmap = 'RdYlGn', vmin = -1e9, vmax = 1e9)
fig.colorbar(heatmap, ax = ax)

ax.plot(xs, ys, 'ko', markersize = 4)

for i in range(len(pthsx)):
    ax.plot(pthsx[i], pthsy[i], 'k-', lw = 2)

plt.show()



