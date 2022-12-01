
Here expects `vultc -ccode voice.vult reverb.vult -real fixed -o engine ` (won't bother fixing progmem issues right now). Note: `-mac` option at times when tables are used.

In case arduino template is used: `sed -i 's/pgm_read_word/pgm_read_dword/g' engine.*`
MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2). Select TinyUSB as USB stack.

For now, use `make_vult.sh` to transpile all files.

TODO:

- take into account pitchwheel
- filters and reverb: method to ask for auto-resize of delay upon change in samplerate
- voice: buffer_alt with fixed 4 voices
- fix pop when a voice is stolen
- add effect to modulate?
- add mixer
- back to toubidou
- add velocity
- midi file?
- sequencer?
