#! /usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from numpy import array, arange, sqrt, floor, abs
from sys import argv

def round_near(arg):
    return floor(arg + 0.5)

def get_ideal():
    return round_near(sqrt(arange(0x8000) / 256.0) * 256.0)

def get_from_file(fname):
    with open(fname) as f:
        return array([float(line) for line in f])

if __name__ == "__main__":
    x     = arange(0x8000)
    ideal = get_ideal()

    ideal_den = ideal.copy()
    ideal_den[ideal_den == 0] = 1   # avoid divide by zero

    for fname in argv[1:]:
        error   = get_from_file(fname) - ideal
        abserr  = abs(error)
        maxerr  = abserr.max()
        toterr  = sum(abserr)
        perr    = 100 * error / ideal_den
        maxperr = abs(perr).max()
        print("{0} -- max = {1}, max % = {2}, total = {3}".format(fname, maxerr, maxperr, toterr))
        plt.plot(x, perr, label=fname)

    plt.legend()
    plt.show()
