 #!/usr/bin/env python3

# generating a not much complicated triangle wave
import numpy as np
from scipy.io import wavfile

size = 4096
data = np.zeros((size,))

data1 = np.linspace(-1.0, 1.0, int(size/2))
data2 = np.linspace(1.0, -1.0, int(size/2))

data[0:int(size/2)] = data1[0:int(size/2)]
data[int(size/2):size] = data2[0:int(size/2)]

# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('triangle.wav', 4096, data.astype(np.int16))
