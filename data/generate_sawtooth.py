 #!/usr/bin/env python3

# generating a not much complicated triangle wave
import numpy as np
from scipy.io import wavfile

size = 4096

data = np.linspace(-1.0, 1.0, size)


# smooth transition between wavetables
data = np.roll(data, int(size/2))

# set to whole int16 range, from -1 .. 1 to -32768..32767
data = np.round((data + 1) * (65535.0 / 2) - 32768)
data16 = data.astype(np.int16)
print("Lenght of wavetable: %f, min vale: %f, max val: %f" % (len(data16), np.min(data16), np.max(data16)))
print(np.min(data))
print(np.max(data))

wavfile.write('sawtooth.wav', 4096, data.astype(np.int16))
