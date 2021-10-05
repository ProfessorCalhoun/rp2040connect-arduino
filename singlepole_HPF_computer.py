# Packages and adjustments to the figures
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np
import math

samplingFreq = 20000; # sampled at ...
poleFreq = 5000;
#tlims = [0,1]        # in seconds
#t = np.linspace(tlims[0],tlims[1],(tlims[1]-tlims[0])*samplingFreq)
#fcycles = np.fft.fftfreq(len(t),d=1.0/samplingFreq); # the frequencies in cycles/s

# High-pass filter
w0 = 2*np.pi*poleFreq; # pole frequency (rad/s)
num = [1,0]        # transfer function numerator coefficients
den = [1,w0]    # transfer function denominator coefficients
highPass = signal.TransferFunction(num,den) # Transfer function

# Compute the discrete low pass with delta_t = 1/samplingFrequency
dt = 1.0/samplingFreq;
discreteHighPass = highPass.to_discrete(dt,method='gbt',alpha=0.5)
print(discreteHighPass)

# The coefficients from the discrete form of the filter transfer function (but with a negative sign)
b = discreteHighPass.num;
a = -discreteHighPass.den;
print("Filter coefficients b_i: " + str(b))
print("Filter coefficients a_i: " + str(a[1:]))