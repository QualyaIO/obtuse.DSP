
This example is meant to run on a Pico (rp2040 based), using arduino-pico core, with MIDI input and PWM audio output.

There is a 4 voices FM synth (all MIDI channels but 2 and 3), a sampler (channel 2), drums (channel 3), SVF filter, reverb and saturator. Some MIDI CC can be used to enable SVF, change its parameters or FM wavetables -- obviously more controls can be added.

The MCU is slightly overclocked (153.6MHz) and samplerate set to 30kHz. Input latency is determined by the hard-coded buffer size, although it is possible to switch to buffer-less versions of the processing.

An `autoplay` switch let the system plays some notes by itself, for testing purposes without MIDI input.

`BufferedSerial` is used output to Serial MIDI messages while minimizing crashes due to cross-talk and interrupt shenanigans. 

Tested with arduino-pico 3.3.0 and Arduino IDE 1.8.19 with obtuse 0.2.0

MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2)

Select Adafruit TinyUSB stack, "Fast" optimization advised.

Montage: depending on what the board is connected to, you probably want a resistor in-between the pin and the output to limit current draw (e.g. 330ohm), and a capacitor to ground (in between resistor and output) for low-pass filtering (e.g. 0.1uF).

# TODO

Interface

- take into account pitchwheel
