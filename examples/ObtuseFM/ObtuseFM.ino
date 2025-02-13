
// This example is meant to run on a Uno with PWM output
// Tested Arduino IDE 1.8.19 with obtuse 0.2.0


/*** Obtuse DSP ***/

#include "synthFMalt.h"


// contexts in obtuse, used to handle internal states
synthFMalt_FMalt_process_type contextv0;

// we will be using the buffered processes for each synth
// to sync with obtuse's vult code
#define BUFFER_SIZE 32

// output buf
int16_t buff[BUFFER_SIZE];
// voices
fix16_t raw_buff[BUFFER_SIZE];

/*** Audio output ***/

// 30khz audio, tradeoff between quality and CPU load
const int sampleRate =  30000;

/*** Misc ***/

// counter for debug
long int tick = 0;

// computing time spent on DSP
unsigned long dsp_tick = 0;
unsigned long dsp_time = 0;
unsigned long dsp_samples = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Let us go");

  /* Audio */

  /* Obtuse DSP */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  synthFMalt_FMalt_default(contextv0);
  //synthFMalt_Voice_setSamplerate(contextv0, float_to_fix(sampleRate / (float)1000));
  // speed-up to get rid of normalization across multiple voices, might saturate signal though
  //synthFM_Voice_setNormalize(contextv0, false);
}

void loop() {
  // buffers hard-coded of size 16 (unless setBuffers() is called), with mono output we need as much as one buffer available
  // Make sure there are at least two samples above that free in the audio circular buffer (of buffers)
  // Note: the returned value of availableForWrite() changed across arduino-pico releases, here consider number of bytes
  //while (audioOut.availableForWrite() > BUFFER_SIZE + 17  ) {
  static int dummy = 0;
  dummy++;
  while (dummy >= BUFFER_SIZE ) {

    dummy -= BUFFER_SIZE;

    // process buffer
    dsp_tick = millis();

    synthFMalt_FMalt_process_bufferTo(contextv0, BUFFER_SIZE, raw_buff);

    // convert obtuse buffer to output buffer
    fix16_t out;
    /*for (size_t i = 0; i < BUFFER_SIZE; i++) {
      out = raw_buff[i];
      // returned float should be between -1 and 1, enforced with saturator
      // shortcut, instead of fixed_to_float * 32767, *almost* the same and vastly improve perf with buffered version
      // Note: use a greater divider than 2 to scale-down values as a crude way to avoid saturation, instead of ad-hoc Saturator
      buff[i] = out / 4 - ( out >> 16);
    }*/

    dsp_time += millis() - dsp_tick;
    dsp_samples += BUFFER_SIZE;

    // do ouput
    /*for (int i = 0; i < BUFFER_SIZE; i++) {
      audioOut.write(buff[i]);
      }*/
  }

  // debug
  int newTick = millis();
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
