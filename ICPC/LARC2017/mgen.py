import random as rnd

def genMePlease(N,K):
    print(N)
    for stack in range(N):
        a = ["%d" % K]
        for i in range(K):
            a.append("%d" % 150)
        print(" ".join(a))

genMePlease(632,632)
