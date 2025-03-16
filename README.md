
_Self-contained generative music with limited resources._

Obtuse is an audio DSP and synthesis engine. It proposes various synths, effects and ways to generate rhythms, melodies or chords. Obtuse leverages on [Vult](https://github.com/vult-dsp/vult) transpiler and by default the code uses fixed floats, for MCU without floating-point unit. The library should be rather efficient, while maintaining hi-fi audio quality (16 bit precision).

While the library is originally meant for the Arduino ecosystem, it can be used outside it, with no external dependencies. One specificity of the project is to let users explore beforehand its capabilities and prototype the audioscape on desktop, via tools familiar to musicians -- check associated repositories for [audio plugins wrappers](https://github.com/QualyaIO/obtuse.DPF) or [VCV Rack modules](https://github.com/QualyaIO/obtuse.VCV).

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


Beside uses on computers, this library is originally aimed at and tested with 32-bit MCU (e.g. RP2040 or SAM architecture). The library can be used as-is but you are welcomed to transpile again the vult code if you need to tune the output for other platforms or if you want to modify the engine -- add new samples, waveforms, voices, and so on. To do so, start with  `make_vult.sh` to transpile all files. This script is used set some specific optimizations, for example to guard against stack overflows, and to avoid too much code duplication. Note: the script requires bash >= 4.

Tested with vult v0.4.15. Note that vultin.h from vult was adapted to speed-up computation with fixed float (`fix_mul`).

While it is feasible to use the library on 8-bit MCUs, e.g. AVR, the performance will be so low and the memory constraints so high that the synths will barely run (e.g. 1500hz sampling rate for a monophonic FM synth on Arduino UNO, without much RAM left). If you still want to go down this road, you might need to only keep the most lightweight files, i.e. FM "alt" synth and utils. Indeed, Arduino will compile the whole library when you first compile for a new board, and the structs used in some parts (e.g. samplers or effects) will raise an error due to their size. To reduce memory footprint you can use smaller buffers and wavetables (include `buffer_small` and `wavetable_small` while transpiling), and switch to PROGMEM to store wavetables. For the latter the "arduino" template can be used with vult (`-template arduino` option), although there will be two issues. First, the wrong function is employed to read back arrays with 32bit variables (`pgm_read_word` instead of `pgm_read_dword`), in which case a command such as `sed -i 's/pgm_read_word/pgm_read_dword/g' src/*` can fix it. Second, the template wrongly puts `pgm_read_word` for accessing *all* arrays, even those that are not constant and not put in PROGMEM. Fortunately, this can be mitigated in some instances, e.g. for FM synth only the .h files should be generated with the arduino template, and the cpp should be generated without template. The bottom line of this paragraph: for AVR or similar architecture you might be better off using a library best suited for 8-bit processors.

Some tuning can be performed depending on the target architecture. For example for RP2040 the code will speed-up if frequent memory accesses are made from RAM rather than flash (especially on some boards, depending on the flash chip used). In this specific case FMalt could benefit from a decorator `sed -i 's/static const fix16_t/static const fix16_t __not_in_flash("vult")/g' src/synthFMalt.tables.h`.

Check the included examples to get used to how the code works. Notably, instead of using objects for each unit we have a struct holding states, passed around the functions performing the computations. This is an artifact of the vult transpilation, kept as-is because wrappers would incur supplementary function calls. WARNING: Be wary where the structs are initialized to avoid problem with stack size, e.g. prefer in the body of the program, especially when large buffer are involved (effectsL or XL).

More examples of how to use the library (generative music, play back MIDI files, ...) can be found in a separate repository: https://github.com/QualyaIO/obtuse.audioscene

# Folders

- vult: vult source
- src: transpiled C++ sources to be used within Arduino
- data: original sound files and scripts used for wavetables and instruments
- examples: Arduino sketch, 4 voices FM, 4 voices sampler, 4 voices drummer, reverb and filter controlled by MIDI

# Changelog

## v0.2.1 (current)

- gate: adding `getVel()` to retrieve velocity

## v0.2.0 (2025-02-17)

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
- adding wrapper "Obtuse.h" for all headers at once

## v0.1.0 (2023-08-12)

- first proper release

# TODO

The API will probably be ironed out in the future depending on uses-cases, e.g. to enable transpilation to other languages.

Interface

- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- add mixer
- optional C++ class wrappers?
- more consistent usage of functions across synths (e.g. `process`, `process_bufferTo`)

Fixes

- timeout for voices? (to take into account upon reuse)
- OSC > 4096 can prevent modulation, adjust max phase depending on size to avoid hitting fixed float limit during computations
- SVF: not compute while disabled while avoiding noise upon start
- combFB (and those using): output not guaranteed to be kept within -1..1
- gate: channel not kept
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
- test code with real floats

# Licence

This code is released under the [GNU/AGPL3 Licence](https://www.gnu.org/licenses/agpl-3.0.html). 
