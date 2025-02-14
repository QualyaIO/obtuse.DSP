
// This example is meant to run on a Uno with PWM output
// Tested with Arduino IDE 1.8.19, AutoAnalogAudio 1.53.0 and obtuse 0.2.0
// NOTE: AutoAnalogAudio hard-code PWM output to pin 9

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

// auto playing notes
bool playing = false;

/*** Audio output ***/

#include <AutoAnalogAudio.h>
AutoAnalog aaAudio;

// 30khz audio, tradeoff between quality and CPU load
const int sampleRate =  1000;

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
  // disable input, enable PWM output (hard-coded pin 9)
  aaAudio.begin(0, 1);
  // fixed samplerate, blocking calls to pace output
  aaAudio.autoAdjust = 0;
  // set samplerate, explicitely mono
  aaAudio.setSampleRate(sampleRate, false);

  /* Obtuse DSP */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  synthFMalt_FMalt_default(contextv0);
  synthFMalt_FMalt_setSamplerate(contextv0, float_to_fix(sampleRate / (float)1000));
}

void loop() {

  // wait for buffer to be free, we use firt pin and limit to common buffer size between DSP and audio output
  aaAudio.feedDAC(0, commonBufferSize);
  // process next buffer
  dsp_tick = millis();
  synthFMalt_FMalt_process_bufferTo(contextv0, commonBufferSize, raw_buff);
  fix16_t out;
  for (size_t i = 0; i < commonBufferSize; i++) {
    // from fixed float -1..1 to byte centered around 127. Can probably be improved
    aaAudio.dacBuffer[i] = raw_buff[i] >> 8 + 127;
  }

  dsp_time += millis() - dsp_tick;
  dsp_samples += BUFFER_SIZE;

  // debug, and autoplay
  unsigned long int newTick = millis();
  if (newTick - tick >= 1000) {
    Serial.print("Running strong! DSP time (miliseconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.print("% CPU)");
    Serial.print(" -- "); Serial.print(dsp_samples); Serial.println(" samples");
    dsp_time = 0;
    dsp_samples = 0;
    tick += 1000;

    if (!playing) {
      synthFMalt_FMalt_noteOn(contextv0, 60, 1, 127);
      Serial.println("Note On");
    }
    else {
      synthFMalt_FMalt_noteOff(contextv0, 60, 1);
      Serial.println("Note Off");
    }
    playing = !playing;
  }

}
