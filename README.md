
_Self-contained generative music with limited resources._

Audio DSP and synthesis engine using Vult.

Obtuse proposes various synths, effects and ways to generate rhythms, melodies or chords. It leverages on Vult transpiler and by default the code uses fixed floats, for MCU without floating-point unit. The library should be rather efficient, while maintaining hi-fi audio quality. One specificity is to let users explore beforehand its capabilities and prototype the audioscape via tools familiar to musicians -- check associated repositories for audio plugins wrappers or VCV Rack modules.


This version is aimed at and tested with RP2040. The library can be used as-is but you are welcomed to transpile again the vult code if you need to tune the output for other platforms. To do so, start with  `make_vult.sh` to transpile all files. This script is used set some specific optimizations, for example to guard against stack overflow, and to avoid too much code duplication. Note: the script requires bash >= 4.


Tested with vult from commit `8167652f1fbc475f18cb5fecc2f8276e51a70238`. Note that vultin.h from vult was adapted to speed-up computation with fixed float (`fix_mul`).


For other MCUs it might be advisable to tap into progmem. In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*` (or whatever files using progmem)


WARNING: Be wary where the struct are initialized to avoid problem with stack size, e.g. prefer in the body of the program, especially when large buffer are involved (effectsL or XL).

# Folders

- vult: vult source
- src: transpiled C sources to be used within Arduino
- data: orig sound files and scripts used for wavetables and instruments
- examples: Arduino sketch, 4 voices FM, 4 voices sampler, 4 voices drummer, reverb and filter controlled by MIDI

# Changelog

## v0.2.0 (current)

- arp: fix return value, now indeed -1 if no notes
- arp: fix for notes with pitch 0.
- arp: add option to keep step position between sequence change
- FM: fix envelope which caused random noise in "bufferTo"
- voice: add method to set decimation factor for FM
- combFF, combFB, allpass: reduce artifacts when changing delay
- adding FMalt and OSCalt, with on-the-fly wavetables -- CPU over memory
- [BREAKING] drummer: re-order samples to be more consistent
- sampler, drummer: fix out-of-bound of one sample
- [BREAKING] sampler: set loop points for some samples (plus fix clicks)
- [BREAKING] renaming "tonnetz" util to "chord"
- [BREAKING] sampler: rename "clarinets" to "softClarinet"
- arp, chord, trigg: using dedicated random generator, ability to set seed

## v0.1.0 (2023-08-12)

- first proper release

# TODO

Interface

- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- add mixer
- C++ and class wrapper for Arduino?

Fixes

- timeout for voices? (to take into account upon reuse)
- OSC > 4096 can prevent modulation, adjust max phase depending on size to avoid hitting fixed float limit during computations
- SVF: not compute while disabled while avoiding noise upon start
- combFB (and those using): output not guaranteed to be kept within -1..1
- gate: velocity and channel not kept
- combFB, combBB, allpass (hence reverb): eliminate artifacts upon change of delay

Features

- velocity: not only linear? save for monophonic?
- tremolo (e.g. at Voice level)
- also folding for wavetable?
- sampler: option for repeating samples, beyond looping
- sampler, drummer: option to kill on note off?
- clock: a version which handle time signature and different division for swing
- gate: accommodate several noteOn (option to send duplicate noteOn ?)
- synth: in case of monophonic option to retrigger for each note (already change velocity)?
- synth: implement sostenuto pedal?

Vult

- at this time Vult transpile init function in such a way that stack overflow can happen due to unnecessary temp variable and absence of NRVO (Named Return Value Optimization) by the compiler. There is currently a rack in the `make_vult.sh` script to circumvent that, it'd better fixed upstream.
- arrays >= 1000 are not initialized automatically to 0, Buffer wrapper even more useful for large buffers
