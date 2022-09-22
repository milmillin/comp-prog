#!/usr/bin/env python

import random

print('1')

N = 1000000
M = N - random.randint(1, 10)
A = random.randint(1, N)
B = random.randint(1, N)
while A == B:
    B = random.randint(1, N)

print('{} {} {} {}'.format(N, M, A, B))

maxC = 1000000000

print('0 ' + str(random.randint(0, maxC)))
for i in range(2, N + 1):
    print(str(random.randint(1, i - 1)) + ' ' + str(random.randint(0, maxC)))
