
Here expects `vultc -ccode voice.vult reverb.vult -real fixed -o engine ` (won't bother fixing progmem issues right now). Note: `-mac` option at times when tables are used.

MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2). Select TinyUSB as USB stack.

TODO:

- take into account pitchwheel
- filters and reverb: method to ask for auto-resize of delay upon change in samplerate,,
