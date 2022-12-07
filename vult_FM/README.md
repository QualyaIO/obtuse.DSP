
Here expects `vultc -ccode voice.vult reverb.vult -real fixed -o engine ` (won't bother fixing progmem issues right now). Note: `-mac` option at times when tables are used.

In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*`
MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2). Select TinyUSB as USB stack.

For now, use `make_vult.sh` to transpile all files -- and set some specific optimization for rp2040.

WARNING: Drummer for some reason does not work on Os optim (default). Tested fine with Ofast.

# TODO


Interface

- take into account pitchwheel
- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- add mixer
- midi file?

Fixes

- voice: buffer_alt with fixed 4 voices
- better fix pop when a voice is stolen
- timeout for voices?
- make drummer work no matter the optimisation ??

Features

- back to toubidou
- sequencer?
- velocity: not only linear? save for monophonic?
- tremolo (e.g. at Voice level)
- interpolate between wavetables (for morph or even to retrieve samples)
