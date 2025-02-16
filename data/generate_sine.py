 #!/usr/bin/env python3

# generating sine. One optional command line argument: number of samples (default. 4096)

import sys
import numpy as np
from scipy.io import wavfile

# fetch the one argument
if len(sys.argv) > 1 and int(sys.argv[1]) > 0:
    size = int(sys.argv[1])
else:
    size = 4096

# one extra for modulo,
t = np.linspace(0, 2 * np.pi, size+1)
data = np.sin(t)
# back to correct size
data = data[0:size]
data 
# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('sine.wav', size, data.astype(np.int16))
