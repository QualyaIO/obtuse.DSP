 #!/usr/bin/env python3

# https://stackoverflow.com/a/67127726


import numpy as np
from scipy.io import wavfile
 
def noise_psd(N, psd = lambda f: 1):
        X_white = np.fft.rfft(np.random.randn(N));
        S = psd(np.fft.rfftfreq(N))
        # Normalize S
        S = S / np.sqrt(np.mean(S**2))
        X_shaped = X_white * S;
        return np.fft.irfft(X_shaped);

def PSDGenerator(f):
    return lambda N: noise_psd(N, f)

@PSDGenerator
def white_noise(f):
    return 1;

@PSDGenerator
def blue_noise(f):
    return np.sqrt(f);

@PSDGenerator
def violet_noise(f):
    return f;

@PSDGenerator
def brownian_noise(f):
    return 1/np.where(f == 0, float('inf'), f)

@PSDGenerator
def pink_noise(f):
    return 1/np.where(f == 0, float('inf'), np.sqrt(f))

def dumb_noise(f):
    return np.random.rand(f) * 2 - 1

# repeatable data
np.random.seed(42)
data = white_noise(4096)
# set to whole int16 range, from -1 .. 1 to -32768..32767
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = (data - np.min(data)) / (np.max(data) - np.min(data))
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = np.round((data) * (65535.0) - 32768)
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
wavfile.write('white_noise.wav', 4096, data.astype(np.int16))

# repeatable data
np.random.seed(42)
data = pink_noise(4096)
# set to whole int16 range, from -1 .. 1 to -32768..32767
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = (data - np.min(data)) / (np.max(data) - np.min(data))
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = np.round((data) * (65535.0) - 32768)
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
wavfile.write('pink_noise.wav', 4096, data.astype(np.int16))
