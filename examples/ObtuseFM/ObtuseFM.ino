
// One of the simplest example, playing one octave note by note on a FM synth.

// This example is meant to run on a Uno with PWM or DAC output depending on boards
// Tested with Arduino IDE 1.8.19, AutoAnalogAudio 1.53.0 and obtuse 0.2.0
// NOTE: AutoAnalogAudio hard-codes pins; PWM output on pin 9 on AVR (e.g. Uno), or first DAC for boards with a real one.

/*** Obtuse DSP ***/

#include "Obtuse.h"

// contexts in obtuse, used to handle internal states
// FM with a version less heavy on memory but more heavy on CPU (each sample is fetched from wavetables instead of computing wavetable once per "morph").
synthFMalt_FMalt_process_type context_fm;

// we will be using the buffered processes for each synth
// to sync with obtuse's vult code
#define BUFFER_SIZE 128

// voices
fix16_t raw_buff[BUFFER_SIZE];

// auto playing notes
bool playing = false;

// starting note and current note for the octave
const int rootNote = 40;
int curNote = rootNote;

/*** Audio output ***/

#include <AutoAnalogAudio.h>
AutoAnalog aaAudio;

// tradeoff between quality and CPU load
// On Uno (AVR) this example can barely run at 1500hz, unusable
// On Due (SAM) 16050 will incur around 24% CPU load with FM mono
const int sampleRate = 16050;

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
  // set samplerate, explicitely mono
  aaAudio.setSampleRate(sampleRate, false);

  /* Obtuse DSP */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  synthFMalt_FMalt_default(context_fm);
  synthFMalt_FMalt_setSamplerate(context_fm, float_to_fix(sampleRate / (float)1000));
  // shaping the envelope for a more pleasing sound
  synthFMalt_FMalt_setModulatorADSR(context_fm, float_to_fix(0.1), float_to_fix(0.01), float_to_fix(0.60), float_to_fix(0.29));
  synthFMalt_FMalt_setCarrierADSR(context_fm, float_to_fix(0.1), float_to_fix(0.01), float_to_fix(0.75), float_to_fix(0.3));
}

void loop() {

  // wait for buffer to be free, we use firt pin and limit to common buffer size between DSP and audio output
  aaAudio.feedDAC(0, commonBufferSize);
  // process next buffer
  dsp_tick = millis();
  synthFMalt_FMalt_process_bufferTo(context_fm, commonBufferSize, raw_buff);
  for (size_t i = 0; i < commonBufferSize; i++) {
    // from fixed float -1..1 to byte centered around 128. Can probably be improved
    aaAudio.dacBuffer[i] = (raw_buff[i] >> 8) + 128;
  }

  dsp_time += millis() - dsp_tick;
  dsp_samples += commonBufferSize;

  // debug, and autoplay
  unsigned long int newTick = millis();
  if (newTick - tick >= 1000) {
    Serial.print("Running strong! DSP time (miliseconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.println("% CPU)");
    Serial.print(" -- "); Serial.print(dsp_samples); Serial.println(" samples");
    dsp_time = 0;
    dsp_samples = 0;
    tick += 1000;
    if (!playing) {
      synthFMalt_FMalt_noteOn(context_fm, curNote, 127, 1);
      Serial.print("Note On: "); Serial.println(curNote);
    }
    else {
      synthFMalt_FMalt_noteOff(context_fm, curNote, 1);
      Serial.print("Note Off: "); Serial.println(curNote);
      // note going up for one octave
      curNote++;
      if (curNote >= rootNote + 12) {
        curNote = rootNote;
      }
    }
    playing = !playing;
  }
}
