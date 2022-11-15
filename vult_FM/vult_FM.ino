
// WARNING: need this bit to fix issues with vult template, not retrieving 32bit otherwise -- but only workes with fixed version, for real leplace with pgm_read_float
//#define pgm_read_word(addr) pgm_read_dword(addr)


/*** Vult ***/

#include "engine.h"

// sole context used in vult, used to handle internal states
Engine_process_type context;

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

const int sampleRate =  40000; //16000; // minimum for UDA1334A
const int mclkMultiplier = 256; // typical for many DAC


/*** Misc ***/

// changing clock
#include <pico/stdlib.h>

// counter for debug
int tick = 0;

// computing time spent on DPS
unsigned long dsp_tick;
unsigned long dsp_time;

// playing notes
unsigned long midi_tick;
// starting C
int current_note = 64;

void setup() {

  // set CPU speed for a good ratio with 256*fs, with a sampling rate set as 40000 in mozzi_config for me now
  set_sys_clock_khz(102400, true);

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
  i2s.setBuffers(16, 16);
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
  Serial.println(sgtl.volume(0.2));

  delay(3000);

  /* Vult */
  // Init engine, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  Engine_default(context);
  Engine_setSamplerate(context, float_to_fix(sampleRate / (float)1000));
}

void loop() {
  if (millis() - midi_tick >= 1000) {
    Serial.print("New note: ");
    current_note += 1;
    // playing three octaves
    if (current_note >= 63 + 3 * 12) {
      // back to C
      current_note = 64;
    }
    Serial.println(current_note);
    Engine_noteOn(context, current_note, 0, 0);
    midi_tick = millis();
  }

  //  buffers hard-coded of size 16 in I2S (unless i2s.setBuffers() is called), make sure there are at least two of them free in the audio circular buffer (of buffers)
  while (i2s.availableForWrite() > 32) {
    dsp_tick = micros();
    // returned float should be between -1 and 1 (should we checkit ?)
    int16_t val = fix_to_float(Engine_process(context)) * 32767;
    //Serial.println(val);
    dsp_time += micros() - dsp_tick;
    //Serial.println(val);
    i2s.write(val);
    i2s.write(val);
  }

  // debug
  int newTick = micros();
  if (newTick - tick >= 1000000) {
    unsigned long st = micros();
    Serial.println("Running strong!");
    Serial.print("DSP time (useconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.println("% CPU)");
    dsp_time = 0;
    tick += 1000000;
  }

}
