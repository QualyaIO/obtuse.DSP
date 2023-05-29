 #!/usr/bin/env python3

import numpy as np
from scipy.io import wavfile

# repeatable data
np.random.seed(42)
data = np.random.rand(4096)
# set to whole int16 range, from -1 .. 1 to -32768..32767
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = (data - np.min(data)) / (np.max(data) - np.min(data))
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
data = np.round((data) * (65535.0) - 32768)
print("Lenght of wavetable: %f, min val: %f, max val: %f" % (len(data), np.min(data), np.max(data)))
wavfile.write('noise.wav', 4096, data.astype(np.int16))
