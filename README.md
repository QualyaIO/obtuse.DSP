
_Self-contained generative music with limited resources._

Obtuse is an audio DSP and synthesis engine. It proposes various synths, effects and ways to generate rhythms, melodies or chords. Obtuse leverages on [Vult](https://github.com/vult-dsp/vult) transpiler and by default the code uses fixed floats, for MCU without floating-point unit. The library should be rather efficient, while maintaining hi-fi audio quality. 

While the library is originally meant for the Arduino ecosystem, it can be used outside it, with no external dependencies. One specificity of the is to actually let users explore beforehand its capabilities and prototype the audioscape on desktop, via tools familiar to musicians -- check associated repositories for [audio plugins wrappers](https://github.com/QualyaIO/obtuse.DPF) or [VCV Rack modules](https://github.com/QualyaIO/obtuse.VCV).

Features:

- synths: four voices polyphony, with channel bend and sustain
  - FM, 2 operators with waveforms that can morph between sine, triangle, sawtooth and square
  - sampler, with pre-defined 24 samples to choose from and possibility to set loop points
  - drummer, 5 kits, with 12 percussive sounds in each one
- effects and filters, choice of three different buffer size where applicable (2048, 8192 or 16384 samples)
  - reverb, based on Schroeder's digital reverb
  - delays: comb feedforward, comb feedback, and allpass
  - saturator: using tanh function, with adjustable threshold and coefficient
- utils to generate MIDI-like events to be sent to synths
  - clock: set BPM and a swing that attempts to accommodate odd time signatures
  - trigger: randomize (or not) the triggering of sounds, with options over patterns' evolution and chaos
  - chord: draw three notes from various scales (major, minor or any diatonic, melodic, harmonic, pentatonic and others), defining root note and probabilities to switch to different chords (major, minor, augmented, suspended, diminished, inversions) 
  - arpeggiator: draw notes one by one with control over pattern and randomization
  - gate: define length of incoming notes, handles polyphony 


This version is originally aimed at and tested with RP2040. The library can be used as-is but you are welcomed to transpile again the vult code if you need to tune the output for other platforms or if you want to modify the engine -- add new samples, waveforms, voices, and so on. To do so, start with  `make_vult.sh` to transpile all files. This script is used set some specific optimizations, for example to guard against stack overflows, and to avoid too much code duplication. Note: the script requires bash >= 4.


Tested with vult from commit [8167652f1fbc475f18cb5fecc2f8276e51a70238](https://github.com/vult-dsp/vult/commit/8167652f1fbc475f18cb5fecc2f8276e51a70238). Note that vultin.h from vult was adapted to speed-up computation with fixed float (`fix_mul`).


For other MCUs it might be advisable to tap into progmem. In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*` (or whatever files using progmem)

Look at examples to get used to how the code works. Notably, instead of using objects for each unit we have a struct holding states, passed around the functions performing the computations. WARNING: Be wary where the structs are initialized to avoid problem with stack size, e.g. prefer in the body of the program, especially when large buffer are involved (effectsL or XL).

# Folders

- vult: vult source
- src: transpiled C++ sources to be used within Arduino
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

- at this time Vult transpiles init function in such a way that stack overflow can happen due to unnecessary temp variable and absence of NRVO (Named Return Value Optimization) by the compiler. There is currently a hack in the `make_vult.sh` script to circumvent that, it'd better fixed upstream.
- arrays >= 1000 are not initialized automatically to 0, hence the Buffer wrapper is even more useful for those large buffers
