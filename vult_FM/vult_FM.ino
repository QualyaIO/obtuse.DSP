
// WARNING: need this bit to fix issues with vult template, not retrieving 32bit otherwise -- but only workes with fixed version, for real leplace with pgm_read_float
//#define pgm_read_word(addr) pgm_read_dword(addr)


/*** Vult ***/

#include "engine.h"

// context for FM synth used in vult, used to handle internal states
Voice_process_type context;
OSC_process_type context_osc;
FM_process_type context_fm;
// another for the filter
Reverb_process_type context_reverb;

// sync with vult code
#define BUFFER_SIZE 256

int16_t buff[BUFFER_SIZE];
fix16_t raw_buff[BUFFER_SIZE];
fix16_t reverb_buff[BUFFER_SIZE];

/*** MIDI ***/

#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

// play by itself instead of MIDI input
const bool autoplay =  false;
// playing notes
unsigned long midi_tick;
// starting C
int current_note = 0;
// note on/off
bool gate = false;

/*** SGTL ***/

#include <I2S.h>
#include "MCLK.h"
#include "control_sgtl5000.h"

// instanciate SGTL
AudioControlSGTL5000 sgtl;


// Create the I2S port using a PIO state machine
I2S i2s(OUTPUT);
// MCLK clock with PIO as well
MCLK mclk;

// GPIO pin numbers
#define pBCLK 20
#define pWS (pBCLK+1)
#define pDOUT 22
#define pMCLK 18 // pin 24

const int sampleRate =  30000; //16000; // minimum for UDA1334A
const int mclkMultiplier = 256; // typical for many DAC


/*** Misc ***/

// changing clock
#include <pico/stdlib.h>

// counter for debug
int tick = 0;

// computing time spent on DPS
unsigned long dsp_tick;
unsigned long dsp_time;

// same for cycle count
long debug_cycle_tick;
long dsp_cycle_count;
long dsp_cycle_tick;

// for testing we will alternate between both versions of algo
bool buffer_version = true;
unsigned long switch_tick;
// in ms, how often we switch between boht versions. 0 to disable
int buffer_switch_time = 0;

void setup() {

  // set CPU speed for a good ratio with 256*fs, with a sampling rate set as 40000 in mozzi_config for me now
  //set_sys_clock_khz(102400, true);
  set_sys_clock_khz(153600, true); // this one for 30000hz

  /* MIDI */
  // not working?
  usb_midi.setStringDescriptor("Vult_FM");

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call usb_midi's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Attach the handleNoteOn function to the MIDI Library. It will
  // be called whenever the Bluefruit receives MIDI Note On messages.
  MIDI.setHandleNoteOn(handleNoteOn);

  // Do the same for MIDI Note Off messages.
  MIDI.setHandleNoteOff(handleNoteOff);

  // NOTE: for some reason MIDI interface does not init if Serial.begin() is called beforehand -- at least there is too much time between Serial.begin and MIDI.begin, e.g. delay(1000) ??
  Serial.begin(115200);
  delay(1000);
  Serial.println("Let us go");

  /* SGTL */
  // sart MCLK
  mclk.setPin(pMCLK);
  if (!mclk.begin(sampleRate, mclkMultiplier)) {
    while (1) {
      Serial.println("Failed to initialize MCLK!");
      delay(1000);
    }
  }

  // inrcease buffers from default 8 buffers of 16 values
  // here we want enough for our buffer, x2 because two channels, and one more to be not blocking... and one more just in case
  i2s.setBuffers(66, 16);
  i2s.setBCLK(pBCLK);
  i2s.setDATA(pDOUT);
  i2s.setBitsPerSample(16); // instead of 16 to get expected clock for bclk ?
  delay(100);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(sampleRate)) {
    while (1) {
      Serial.println("Failed to initialize I2S!");
      delay(100);
    }
  }
  Serial.println("i2s initialized");
  delay(100);

  // start audio card
  if (!sgtl.enable()) {
    while (1) {
      Serial.println("Failed to initialize SGTL!");
      delay(100);
    }
  }
  Serial.println("sgtl initialized");

  delay(100);
  Serial.println("setup ok");

  Serial.print("volume: ");
  Serial.println(sgtl.volume(0.5));

  delay(1000);

  /* Vult */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  Voice_default(context);
  Voice_setSamplerate(context, float_to_fix(sampleRate / (float)1000));
  OSC_default(context_osc);
  OSC_setSamplerate(context_osc, float_to_fix(sampleRate / (float)1000));
  FM_default(context_fm);
  FM_setSamplerate(context_fm, float_to_fix(sampleRate / (float)1000));
  Reverb_default(context_reverb);
  Reverb_setSamplerate(context_reverb, float_to_fix(sampleRate / (float)1000));
  Reverb_setReverbTime(context_reverb, float_to_fix(10.0));
  Reverb_setDelayms(context_reverb, float_to_fix(50.0));

}

void loop() {

  // generating notes if option set
  if (autoplay) {
    // note on
    if (!gate and millis() - midi_tick >= 50) {
      Serial.print("New note: ");
      current_note += 1;
      // playing three octaves
      if (current_note >= 128) {
        // back to C
        current_note = 0;
      }
      Serial.println(current_note);
      Voice_noteOn(context, current_note, 0, 0);
      //OSC_setFrequency(context_osc, Util_noteToFrequency(current_note));
      midi_tick = millis();
      gate = true;
    }
    if (gate and millis() - midi_tick >= 50) {
      Serial.println("note off");
      Voice_noteOff(context, current_note, 0);
      midi_tick = millis();
      gate = false;
    }
  }

  if (!buffer_version) {
    // buffers hard-coded of size 16 in I2S (unless i2s.setBuffers() is called), make sure there are at least two samples above that free in the audio circular buffer (of buffers)
    while (i2s.availableForWrite() > 17) {
      dsp_tick = micros();
      dsp_cycle_tick = rp2040.getCycleCount();

      // returned float should be between -1 and 1 (should we checkit ?)
      //fix16_t raw = FM_process(context_fm);
      //fix16_t raw = OSC_process(context_osc);

      fix16_t raw = Voice_process(context);
      fix16_t val = Reverb_process(context_reverb, raw);
      // wet / dry
      fix16_t out = 0.5 * raw + 0.5 * val;
      // shortcut, instead of fixed_to_float * 32767, *almost* the same
      int16_t out16 =  out / 2 - (out >> 16);

      dsp_cycle_count += rp2040.getCycleCount() - dsp_cycle_tick;
      dsp_time += micros() - dsp_tick;
      i2s.write16(out16, out16);

    }
  } else {
    //  buffers hard-coded of size 16 in I2S (unless i2s.setBuffers() is called), make sure there are at least two samples above that free in the audio circular buffer (of buffers)
    while (i2s.availableForWrite() > (BUFFER_SIZE) * 2 + 17  ) {
      // process buffer
      dsp_tick = micros();
      dsp_cycle_tick = rp2040.getCycleCount();

      //OSC_process_bufferTo_simplest(context_osc, BUFFER_SIZE, raw_buff);
      // FIXME: buffer not supported for voice at the moment
      //FM_process_bufferTo(context_fm, BUFFER_SIZE, raw_buff);
      Voice_process_bufferTo_alt(context, BUFFER_SIZE, raw_buff);
      Reverb_process_bufferTo(context_reverb, BUFFER_SIZE, raw_buff, reverb_buff);
      // two times to better compare with classical situation
      fix16_t out;
      for (size_t i = 0; i < BUFFER_SIZE; i++) {
        // wet / dry
        out = 0.5 * raw_buff[i] + 0.5 * reverb_buff[i];
        // returned float should be between -1 and 1 (should we checkit ?)
        // shortcut, instead of fixed_to_float * 32767, *almost* the same and vastly improve perf with buffered version (???)
        buff[i] = out / 2 - ( out >> 16);
      }

      dsp_cycle_count += rp2040.getCycleCount() - dsp_cycle_tick;
      dsp_time += micros() - dsp_tick;

      for (int i = 0; i < BUFFER_SIZE; i++) {
        i2s.write16(buff[i], buff[i]);
      }
    }
  }

  // read any new MIDI messages
  MIDI.read();

  // debug
  int newTick = micros();
  if (newTick - tick >= 1000000) {
    unsigned long cycle_count = rp2040.getCycleCount() -  debug_cycle_tick;
    float dsp_cycle_ratio = (float) dsp_cycle_count / cycle_count;
    Serial.print("Running strong! Buffer: ");
    Serial.print(buffer_version);
    Serial.print(". DSP time (useconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.println("% CPU)");
    Serial.print("CPU cycles ratio: "); Serial.print(dsp_cycle_ratio); Serial.print(" (count: "); Serial.print(dsp_cycle_count); Serial.println(")");

    dsp_time = 0;
    tick += 1000000;
    dsp_cycle_count = 0;
    debug_cycle_tick = rp2040.getCycleCount();
  }

  if (buffer_switch_time > 0 and millis() - switch_tick >= buffer_switch_time) {
    buffer_version = !buffer_version;
    Serial.print("Switch to buffer: ");
    Serial.println(buffer_version);
    switch_tick = millis();
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
  //OSC_setFrequency(context_osc, Util_noteToFrequency(pitch));
  //FM_noteOn(context_fm, pitch, 0, 0);
  Voice_noteOn(context, pitch, 0, 0);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Log when a note is released.
  Serial.print("Note off: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
  //OSC_setFrequency(context_osc, Util_noteToFrequency(1));
  //FM_noteOff(context_fm, pitch, 0);
  Voice_noteOff(context, pitch, 0);
}
