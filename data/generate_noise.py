 #!/usr/bin/env python3

# generating noise. One optional command line argument: number of samples (default. 4096)

import sys
import numpy as np
from scipy.io import wavfile

# fetch the one argument
if len(sys.argv) > 1 and int(sys.argv[1]) > 0:
    size = int(sys.argv[1])
else:
    size = 4096

print("generating sawtooth of size %d" % size)

# repeatable data
np.random.seed(42)
data = np.random.rand(size)
# set to whole int16 range, from -1 .. 1 to -32768..32767
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = (data - np.min(data)) / (np.max(data) - np.min(data))
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = np.round((data) * (65535.0) - 32768)
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
wavfile.write('noise.wav', size, data.astype(np.int16))
