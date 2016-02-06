#!/usr/bin/env python

# This file plots the csv file generated from the bouncing ball example
# Author: Avinash
import numpy as np
import sys
import matplotlib.pyplot as plt


def plot_bb(file):
    """
    This function plots the output from the bouncing ball example
    """
    da = np.genfromtxt(file[0], delimiter=',')
    x = da[:, 0]
    y = da[:, 1]
    z = da[:, 2]
    if len(file) == 1:
        plt.plot(x, y)
        plt.plot(x, z)
    elif len(file) == 3:
        plt.plot(x[int(file[1]):int(file[2])],
                 y[int(file[1]):int(file[2])])
        plt.plot(x[int(file[1]):int(file[2])],
                 z[int(file[1]):int(file[2])])
    else:
        plt.plot(x[0:int(file[1])],
                 y[0:int(file[1])])
        plt.plot(x[0:int(file[1])],
                 z[0:int(file[1])])
    plt.show()


if __name__ == '__main__':
    plot_bb(sys.argv[1:])
