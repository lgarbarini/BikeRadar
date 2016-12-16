import time
import scipy.signal as signal
import numpy as np
from scipy.signal import argrelextrema


t = np.linspace(-10,10,1000); # time support of the signal
y = np.sin(t) + 5*np.sin(t*30*np.pi +np.radians(120)) + np.sin(90*t*np.pi) + np.sin(200*np.pi*t+np.pi/2) + .01*np.random.normal(0, 1, 1000)
z = np.sin(t) + 2*np.sin(t*30.03*np.pi) + np.sin(90*t*np.pi+np.pi) + np.sin(200*np.pi*t) + .01*np.random.normal(0, 1, 1000)


Z    = np.fft.fft(z)
Y    = np.fft.fft(y)


#freq = np.fft.fftfreq(len(y), t[1] - t[0])
start_time = time.time()

maxx = np.argmax(np.abs(Y))
print("--- %s seconds ---" % (time.time() - start_time))
print maxx
print(str(np.abs(Y)[maxx]) + " at angle " + str(np.degrees(np.angle(Y)[maxx]-np.angle(Z)[maxx])))
