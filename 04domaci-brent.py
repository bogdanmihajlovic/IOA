import math
import random

import numpy as np
import matplotlib.pyplot as plt

N = 6
BETA = 20*math.pi
DOTS = 100
MINIMUM_BREAK = 1e-8


def F(n, beta, theta, d, delta):
    phi = delta + beta*d*math.cos(theta)
    j = complex("0+1j")
    suma = 0
    for k in range(0, n):
        suma += pow(math.e, -j*k*phi)
    return suma


def randomIndex(rangeDots):
    i1 = int(random.random() * rangeDots)
    i2 = int(random.random() * rangeDots)
    i3 = int(random.random() * rangeDots)

    while i2 == i3:
        i2 = int(random.random() * DOTS)

    while i3 == i1 or i3 == i2:
        i3 = int(random.random() * DOTS)

    return i1, i2, i3


def showGraph(x, y, xlabel, ylabel):
    fig = plt.figure()
    plt.plot(x, y)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.show()


def findMaximum(y):
    fMaximum = max(y)

    deltas = np.arange(4, 5.5, (5.5 - 4)/1000)
    index1, index2, index3 = randomIndex(1000)

    delta1 = deltas[index1]
    delta2 = deltas[index2]
    delta3 = deltas[index3]

    while True:
        f1 = abs(F(N, BETA, math.pi / 3, 1.0 / 20, delta1))
        f2 = abs(F(N, BETA, math.pi / 3, 1.0 / 20, delta2))
        f3 = abs(F(N, BETA, math.pi / 3, 1.0 / 20, delta3))

        matrix = np.linalg.inv(np.array([[delta1*delta1, delta1, 1], [delta2*delta2, delta2, 1], [delta3*delta3, delta3, 1]]))
        fs = [[f1], [f2], [f3]]
        consts = np.dot(matrix, np.array(fs))

        a = consts[0][0]
        b = consts[1][0]

        deltaMaximum = -b / (2*a)
        fLocalMaximum = abs(F(N, BETA, math.pi / 3, 1.0 / 20, deltaMaximum))

        if abs(fMaximum - fLocalMaximum) < MINIMUM_BREAK:
            break

        fMin = min(f1, f2, f3, fLocalMaximum)
        if f1 == fMin:
            delta1 = deltaMaximum
        elif f2 == fMin:
            delta2 = deltaMaximum
        elif f3 == fMin:
            delta3 = deltaMaximum

    return fMaximum, fLocalMaximum, deltaMaximum


def main():

    deltas = np.arange(0, 2 * math.pi, 2 * math.pi / DOTS)
    f = [abs(F(N, BETA, math.pi/3, 1.0/20, delta)) for delta in deltas]

    showGraph(deltas, f, "delta", "|F|")
    actualMax, myMax, deltaMax = findMaximum(f)

    print(f'Actual maximum {actualMax}\nMaximum I found {myMax}\nDelta {deltaMax}')

if __name__ == "__main__":
    main()
