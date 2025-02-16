# -*- coding: utf-8 -*-

# from https://gist.github.com/endolith/407991
# adding expricit fs

"""
Bandlimited versions of scipy.signal.waveforms.

Intent is mathematical perfection over performance;
these use additive synthesis, so they are slow, but exact.

Less ideal methods using BLIT:
Sawtooth can be made by integrating BLIT minus a DC value to prevent integrator wandering off
Square can be made by integrating bipolar BLIT
Triangle can be made by integrating square
But I'm trying to avoid leaky integration, etc.
"""

from __future__ import division
from numpy import asarray, zeros, pi, sin, cos, amax, diff, arange, outer
from scipy.io import wavfile

# TODO: De-duplicate all this code into one generator function and then make these into wrapper functions

def bl_sawtooth(t, fs): # , width=1
    """
    Return a periodic band-limited sawtooth wave with
    period 2*pi which is falling from 0 to 2*pi and rising at
    2*pi (opposite phase relative to a sin)

    Produces the same phase and amplitude as scipy.signal.sawtooth.

    Examples
    --------
    >>> t = linspace(0, 1, num = 1000, endpoint = False)
    >>> f = 5 # Hz
    >>> plot(bl_sawtooth(2 * pi * f * t))
    """
    t = asarray(t)

    if abs((t[-1]-t[-2]) - (t[1]-t[0])) > .0000001:
        raise ValueError("Sampling frequency must be constant")

    if t.dtype.char in ['fFdD']:
        ytype = t.dtype.char
    else:
        ytype = 'd'
    y = zeros(t.shape, ytype)

    # Get sampling frequency from timebase
    #fs =  1 / (t[1] - t[0])
    #    fs =  1 / amax(diff(t))

    # Sum all multiple sine waves up to the Nyquist frequency

    # TODO: Maybe choose between these based on number of harmonics?

    # Slower, uses less memory
    for h in range(1, int(fs)+1):
        y += 2 / pi * -sin(h * t) / h

    # Faster, but runs out of memory and dies
#    h = arange(1, int(fs * pi) + 1)
#    phase = outer(t, h)
#    y = 2 / pi * -sin(phase) / h
#    y = sum(y, axis=1)

    return y


def bl_triangle(t, fs):
    """
    Return a periodic band-limited triangle wave with
    period 2*pi which is falling from 0 to pi and rising from
    pi to 2*pi (same phase as a cos)

    Produces the same phase and amplitude as scipy.signal.sawtooth(width=0.5).

    Examples
    --------
    >>> t = linspace(0, 1, num = 1000, endpoint = False)
    >>> f = 5 # Hz
    >>> plot(bl_triangle(2 * pi * f * t))
    """
    t = asarray(t)

    if abs((t[-1]-t[-2]) - (t[1]-t[0])) > .0000001:
        raise ValueError("Sampling frequency must be constant")

    if t.dtype.char in ['fFdD']:
        ytype = t.dtype.char
    else:
        ytype = 'd'
    y = zeros(t.shape, ytype)

    # Get sampling frequency from timebase
    #fs =  1 / (t[1] - t[0])

    # Sum all odd multiple sine waves up to the Nyquist frequency

    # Slower, uses less memory
    for h in range(1, int(fs) + 1, 2):
        y += 8 / pi**2 * -cos(h * t) / h**2

    # Faster, but runs out of memory and dies
#    h = arange(1, int(fs * pi) + 1, 2)
#    phase = outer(t, h)
#    y = 8 / pi**2 * -cos(phase) / h**2
#    y = sum(y, axis=1)

    return y


def bl_square(t, fs, duty=0.5):
    """
    Return a periodic band-limited square wave with
    period 2*pi which is +1 from 0 to pi and -1 from
    pi to 2*pi (same phase as a sin)

    Produces the same phase and amplitude as scipy.signal.square.

    Similarly, duty cycle can be set, or varied over time.

    Examples
    --------
    >>> t = linspace(0, 1, num = 10000, endpoint = False)
    >>> f = 5 # Hz
    >>> plot(bl_square(2 * pi * f * t))

    >>> sig = np.sin(2 * np.pi * t)
    >>> pwm = bl_square(2 * np.pi * 30 * t, duty=(sig + 1)/2)
    >>> plt.subplot(2, 1, 1)
    >>> plt.plot(t, sig)
    >>> plt.subplot(2, 1, 2)
    >>> plt.plot(t, pwm)
    >>> plt.ylim(-1.5, 1.5)
    """
    return bl_sawtooth(t - duty*2*pi, fs) - bl_sawtooth(t, fs) + 2*duty-1


if __name__ == "__main__":
    import sys
    from numpy import linspace
    import numpy as np
    # fetch the one argument, duration of wavefile
    if len(sys.argv) > 1 and int(sys.argv[1]) > 0:
        length = int(sys.argv[1])
    else:
        length = 4096

    # target sampling rate
    sr = 30000
    # band limit with A4...
    f = 440 # Hz
    # how many periods we should have
    per = 1
    t = linspace(0, 1, num = length, endpoint = False)

    # cutoff freq (or really, number of harmonics?)
    fs = sr / f / 2

    print("Generate square")
    data = bl_square(2 * pi * per * t, fs)
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = (data - np.min(data)) / (np.max(data) - np.min(data))
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = np.round((data) * (65535.0) - 32768)
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    wavfile.write('square_bl.wav', length, data.astype(np.int16))

    print("Generate sawtooth")
    data = bl_sawtooth(2 * pi * per * t, fs)
    # same phase as current wavetables
    data = np.roll(data, int(length/2))
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = (data - np.min(data)) / (np.max(data) - np.min(data))
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = np.round((data) * (65535.0) - 32768)
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    wavfile.write('sawtooth_bl.wav', length, data.astype(np.int16))

    print("Generate triangle")
    data = bl_triangle(2 * pi * per * t, fs)
    # same phase as current wavetables
    data = np.roll(data, -int(length/4))
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = (data - np.min(data)) / (np.max(data) - np.min(data))
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    data = np.round((data) * (65535.0) - 32768)
    print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
    wavfile.write('triangle_bl.wav', length, data.astype(np.int16))
