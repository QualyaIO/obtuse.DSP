
// WARNING: need this bit to fix issues with vult template, not retrieving 32bit otherwise -- but only workes with fixed version, for real leplace with pgm_read_float
#define pgm_read_word(addr) pgm_read_dword(addr)


/*** Vult ***/

#include "engine.h"

// sole context used in vult, used to handle internal states
Processor_process_type context;

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

  delay(1000);
}

int nb_updates = 0;


long loop_n = 0;
// i2s and then buffer have elements
long loop_i2s_a = 0;
long loop_buf_a = 0;
// buffer full
long loop_buf_f = 0;
// audio transmitted in this loop
long loop_audio = 0;

void loop() {
  loop_n++;

  if (i2s.availableForWrite() > 32) {
    loop_i2s_a++;
    loop_audio++;

  }

  //  buffers hard-coded of size 16 in I2S (unless i2s.setBuffers() is called), make sure there are at least two of them free in the audio circular buffer (of buffers)
  while (i2s.availableForWrite() > 32) {
    // as long as float is really between -1 and 1, int part of fixed will be on -65536/65535 range (should we checkit ?)
    // not forgetting to convert passed parameters to fixed (of course...)
    fix16_t val_fix = Processor_process(context, float_to_fix(sampleRate));
    int16_t val = (int16_t)(val_fix / 2);
    //Serial.println(val);
    i2s.write(val);
    i2s.write(val);
  }

  // debug
  int newTick = millis();
  if (newTick - tick >= 1000) {
    unsigned long st = micros();
    Serial.println("Running strong!");
    Serial.print("loops with i2s available");
    Serial.println( loop_i2s_a / (float) loop_n);
    Serial.print("loops with buffer available");
    Serial.println( loop_buf_a / (float) loop_n);
    Serial.print("loops with buffer full");
    Serial.println( loop_buf_f / (float) loop_n);
    Serial.print("number of loops: ");
    Serial.println(loop_n);

    Serial.print("loops with audio transmitted");
    Serial.println( loop_audio / (float) loop_n);

    Serial.print("i2s available: ");
    Serial.println(i2s.availableForWrite());
    loop_n = 0;
    loop_i2s_a = 0;
    loop_buf_a = 0;
    loop_buf_f = 0;
    loop_audio = 0;
    nb_updates = 0;

    tick += 1000;

    // testing buffer to create pops
    //delayMicroseconds(random(0, 2000));
    loop_buf_f = 0;
    unsigned long en = micros();
    Serial.print("Time for debug (microseconds): ");
    Serial.println(en - st);
  }

}
