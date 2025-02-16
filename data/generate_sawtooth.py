 #!/usr/bin/env python3

# generating a not much complicated triangle wave. One optional command line argument: number of samples (default. 4096)

import numpy as np
from scipy.io import wavfile
import sys

# fetch the one argument
if len(sys.argv) > 1 and int(sys.argv[1]) > 0:
    size = int(sys.argv[1])
else:
    size = 4096

print("generating sawtooth of size %d" % size)

data = np.linspace(-1.0, 1.0, size)

# smooth transition between wavetables
data = np.roll(data, int(size/2))

# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('sawtooth.wav', size, data.astype(np.int16))
