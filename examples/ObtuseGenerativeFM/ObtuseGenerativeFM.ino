
// Generative music with an arpeggiator on changing chords, a four-voices FM synth and a delay filter

// This example is meant to run on a Uno with PWM or DAC output depending on boards
// Tested with Arduino IDE 1.8.19, AutoAnalogAudio 1.53.0 and obtuse 0.2.0
// NOTE: AutoAnalogAudio hard-codes pins; PWM output on pin 9 on AVR (e.g. Uno), or first DAC for boards with a real one.

/*** Obtuse DSP ***/

#include "Obtuse.h"

// contexts in obtuse, used to handle internal states
// utils
utils_Clock_process_type context_clock;
utils_Chord_process_type context_chord;
utils_Trigg_process_type context_trigg;
utils_Arp_process_type context_arp;
utils_Gate_process_type context_gate;
// FM synth, wavetable in memory, more CPU effecient but memory hungry, and should not morph while running
synthFM_Voice_process_type context_fm;
// delay filter, comb feedback
effectsL_CombFB_process_type context_comb;

// we will be using the buffered processes for each synth
// to sync with obtuse's vult code
#define BUFFER_SIZE 128

// buffer for processing synth and filter
fix16_t raw_buff[BUFFER_SIZE];
fix16_t filter_buff[BUFFER_SIZE];

// B2 root note chord
const int rootNote = 47;
// main paramaters to manipulate, general pace of the notes
const float clock_bpm = 240.0;
// how long notes will be held, in seconds
const float gate_duration = 0.250;

/*** Audio output ***/

#include <AutoAnalogAudio.h>
AutoAnalog aaAudio;

// tradeoff between quality and CPU load
// On Due 22050hz will incur around between 36% and 41% CPU load in this sketch
const int sampleRate = 22050;

// the library has its own buffer size, we will need to fil
const int commonBufferSize = min(MAX_BUFFER_SIZE, BUFFER_SIZE);

//Link the DAC ISR/IRQ to the library. Called by the MCU when DAC is ready for data
void DACC_Handler(void) {
  aaAudio.dacHandler();
}


/*** Misc ***/

// counter for debug
unsigned long int tick = 0;

// computing time spent on DSP
unsigned long dsp_tick = 0;
unsigned long dsp_time = 0;
unsigned long dsp_samples = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Let us go");

  /* Audio */
  // disable input, enable output (either PWM on hard-coded pin 9 or first DAC pin on boards with those)
  aaAudio.begin(0, 1);
  // fixed samplerate, blocking calls to pace output
  aaAudio.autoAdjust = 0;
  // 12 is the highest bitrate for this library (out of Obtuse's 16bit)
  aaAudio.dacBitsPerSample = 12;
  // set samplerate, explicitely mono
  aaAudio.setSampleRate(sampleRate, false);

  /* Obtuse DSP */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  synthFM_Voice_default(context_fm);
  synthFM_Voice_setSamplerate(context_fm, float_to_fix(sampleRate / (float)1000));
  // shaping the envelope for a more pleasing sound
  synthFM_Voice_synthSetModulatorADSR(context_fm, float_to_fix(0.1), float_to_fix(0.01), float_to_fix(0.60), float_to_fix(0.29));
  synthFM_Voice_synthSetCarrierADSR(context_fm, float_to_fix(0.1), float_to_fix(0.01), float_to_fix(0.75), float_to_fix(0.3));
  // init filter, a delay with larger buffer
  effectsL_CombFB_process_init(context_comb);
  effectsL_CombFB_setSamplerate(context_comb, float_to_fix(sampleRate / (float)1000));
  effectsL_CombFB_setDecay(context_comb, float_to_fix(0.5));
  effectsL_CombFB_setDelayms(context_comb, float_to_fix(250.0));
  // init and configure utils
  utils_Clock_process_init(context_clock);
  utils_Clock_setBPM(context_clock, float_to_fix(clock_bpm));
  // clock a sequence of 4 pulses, ABAB, tiny swing to it
  utils_Clock_setGroupSize(context_clock, 4);
  utils_Clock_setGroupRatio(context_clock, float_to_fix(0.5));
  utils_Clock_setSwing(context_clock, float_to_fix(0.6));
  // gate for arp
  utils_Gate_process_init(context_gate);
  utils_Gate_setDuration(context_gate, float_to_fix(gate_duration));
  // default triggers for evolving arp timings, almost all the time
  utils_Trigg_process_init(context_trigg);
  utils_Trigg_setDensity(context_trigg, float_to_fix(0.9));
  // also default chord and arp sequences
  utils_Chord_process_init(context_chord);
  utils_Arp_process_init(context_arp);
}

// pace notes generation
void control() {
  // update time
  int timeS = millis() / 1000;
  float timeFract = (micros() % 1000000) / 1000000.0;
  utils_Gate_setTime(context_gate, timeS, float_to_fix(timeFract));
  // advance controls for each beat
  utils_Clock_setTime(context_clock, timeS, float_to_fix(timeFract));
  // Note: there could be sereval peding beats if we dont read often enough
  int beat = utils_Clock_process(context_clock);
  // chord change on first beat of a group
  if (beat == 1) {
    // new chord upon each clock, generate 3 notes
    utils_Chord_process(context_chord);
    int n0 = utils_Chord_process_ret_0(context_chord);
    int n1 = utils_Chord_process_ret_1(context_chord);
    int n2 = utils_Chord_process_ret_2(context_chord);
    // connect to arp (array of up to 16 notes)
    int arpNotes[] = {n0, n1, n2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    utils_Arp_setNotes(context_arp, arpNotes);
    Serial.print("Chord change"); Serial.print(n0); Serial.print(" "); Serial.print(n1); Serial.print(" "); Serial.println(n2);
  }
  // arp could trigger on any beat
  if (beat > 0) {
    if (utils_Trigg_process(context_trigg)) {
      int arpNote = utils_Arp_process(context_arp);
      // new note for gate -- velocity and channel are ignored
      utils_Gate_noteOn(context_gate, arpNote, 0, 0);
      Serial.print("Gate On "); Serial.println(arpNote);
    }
  }
  // run gate to FM, first we need note off, then note onn
  utils_Gate_process(context_gate);
  int note = utils_Gate_getNoteOff(context_gate);
  while (note >= 0) {
    synthFM_Voice_noteOff(context_fm, note, 0);
    Serial.print("Note Off "); Serial.println(note);
    note = utils_Gate_getNoteOff(context_gate);
  }
  note = utils_Gate_getNoteOn(context_gate);
  while (note >= 0) {
    synthFM_Voice_noteOn(context_fm, note, 127, 0);
    Serial.print("Note On "); Serial.println(note);
    note = utils_Gate_getNoteOn(context_gate);
  }
}

void loop() {

  // wait for buffer to be free, we use firt pin and limit to common buffer size between DSP and audio output
  aaAudio.feedDAC(0, commonBufferSize);

  // update sequence
  control();

  // process next buffer
  dsp_tick = millis();
  // generate sounds and apply filter
  synthFM_Voice_process_bufferTo(context_fm, commonBufferSize, raw_buff);
  effectsL_CombFB_process_bufferTo(context_comb, BUFFER_SIZE, raw_buff, filter_buff);
  // copy to output
  for (size_t i = 0; i < commonBufferSize; i++) {
    // from fixed float in 16.16 format -1..1 to byte centered around mid-point. Set for 12 bit output. Can probably be improved.
    // Note: signal can saturate, to correct that manually the divider was increased (from 4 to 5 >> shift, hence 11 to 10 for << shift) for more headroom. Alternatively one can use the Saturator right before the output
    aaAudio.dacBuffer16[i] = (filter_buff[i] >> 5) + (2 << 10);
  }

  dsp_time += millis() - dsp_tick;
  dsp_samples += commonBufferSize;

  // debug
  unsigned long int newTick = millis();
  if (newTick - tick >= 1000) {
    Serial.print("Running strong! DSP time (miliseconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.print("% CPU)");
    Serial.print(" -- "); Serial.print(dsp_samples); Serial.println(" samples");
    dsp_time = 0;
    dsp_samples = 0;
    tick += 1000;
  }
}
