 #!/usr/bin/env python3

import numpy as np
from scipy.io import wavfile

# one extra for modulo,
t = np.linspace(0, 2 * np.pi, 4097)
data = np.sin(t)
# back to correct size
data = data[0:4096]
data 
# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('sine.wav', 4096, data.astype(np.int16))
