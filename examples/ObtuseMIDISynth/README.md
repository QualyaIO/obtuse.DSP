

This example is meant to run on a Pico (rp2040 based), using arduino-pico core, with MIDI input and PWM output.

Tested with arduino-pico 3.3.0 and Arduino IDE 1.8.19 with obtuse 0.2.0

MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2)

Select Adafruit TinyUSB stack, "Fast" optimization advised.

Montage: depending on what the board is connected to, you probably want a resistor in-between the pin and the output to limit current draw (e.g. 330ohm), and a capacitor to ground (in between resistor and output) for low-pass filtering (e.g. 0.1uF).

# TODO

Interface

- take into account pitchwheel
- midi file?

Features

- sequencer?
