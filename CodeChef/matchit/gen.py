import random
import matplotlib.pyplot as plt
import collections
import numpy as np

def showPlot(x, y, n):
    plt.plot(x, y, 'ro', markersize = 2)
    plt.axis([0, n, 0, n])
    plt.show()


n = np.random.randint(500, 1001)
m = np.random.randint(500, 1001)

pts = []
xs = []
ys = []

tbl = {}

for i in range(2 * m):
    newpt = (np.random.randint(0, n) + 1, np.random.randint(0, n) + 1)
    while (newpt in pts):
        newpt = (np.random.randint(0, n) + 1, np.random.randint(0, n) + 1)
    pts.append(newpt)
    nx, ny = newpt
    xs.append(nx)
    ys.append(ny)

print(n, m)
for (x, y) in pts:
    print(x, y)

for i in range(n):
    for j in range(n):
        print(np.random.randint(-1e9, 1e9 + 1), end=' ')
    print()



