 #!/usr/bin/env python3

# generating a super complicated square wave (low 1/4, high 1/2, low 1/4)
import numpy as np
from scipy.io import wavfile

size = 4096
data = np.zeros((size,))

for i in range(size):
    if i < size / 2:
        data[i] = 1.0
    else:
       data[i] = -1.0 

# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('square.wav', 4096, data.astype(np.int16))
