
Audio DSP and synthesis engine using Vult. This version is aimed at and tested with RP2040

Here expects `vultc -ccode voice.vult reverb.vult -real fixed -o engine ` (won't bother fixing progmem issues right now). Note: `-mac` option at times when tables are used.

Tested with vult from comit `8167652f1fbc475f18cb5fecc2f8276e51a70238`

In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*`

For now, use `make_vult.sh` to transpile all files -- and set some specific optimization for RP2040.

WARNING: Drummer for some reason does not work on Os optim (default). Tested fine with Ofast.

# Folders

- vult: vult source
- data: orig sound files and scripts used for wavetables and instruments
- examples: Arduino sketch, 4 voices FM, 4 voices sampler, 4 voices drummer, reverb and filter controlled by MIDI

# TODO


Interface

- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- add mixer

Fixes

- voice: buffer_alt with fixed 4 voices
- better fix pop when a voice is stolen
- timeout for voices?
- make drummer work no matter the optimisation??

Features

- back to toubidou
- velocity: not only linear? save for monophonic?
- tremolo (e.g. at Voice level)
- interpolate between wavetables (for morph or even to retrieve samples)
- also folding for wavetable?
- option to adjust relative phase for morphing
- negative ratio: fixed frequency
- option to modulate not phase but volume (cheap and limited tremolo)
