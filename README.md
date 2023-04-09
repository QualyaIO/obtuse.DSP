
Audio DSP and synthesis engine using Vult. This version is aimed at and tested with RP2040

Here expects `vultc -ccode voice.vult reverb.vult -real fixed -o engine ` (won't bother fixing progmem issues right now). Note: `-mac` option at times when tables are used.

Tested with vult from comit `8167652f1fbc475f18cb5fecc2f8276e51a70238`. Note that vultin.h from vult was adapted to speed-up computation with fixed float (`fix_mul`).

In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*` (or whatever files using progmem)

For now, use `make_vult.sh` to transpile all files -- and set some specific optimization for RP2040.

WARNING: Be wary where the struct are initialized to avoid problem with stack size, e.g. prefer in the body of the program, especially when large buffer are involved (effectsL or XL).

# Folders

- vult: vult source
- src: transpiled C sources to be used within Arduino
- data: orig sound files and scripts used for wavetables and instruments
- examples: Arduino sketch, 4 voices FM, 4 voices sampler, 4 voices drummer, reverb and filter controlled by MIDI

# TODO


Interface

- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- add mixer

Fixes

- voice: buffer_alt with fixed 4 voices
- better fix pop when a voice is stolen (e.g. take into account separately level and ADSR state?)
- timeout for voices?
- OSC > 4096 can prevent modulation, adjust max phase depending on size to avoid hitting fixed float limit during computations
- SVF: not compute while disabled while avoiding noise upon start
- combFB (and those using): output not guaranteed to be kept within -1..1

Features

- back to toubidou
- velocity: not only linear? save for monophonic?
- tremolo (e.g. at Voice level)
- also folding for wavetable?
