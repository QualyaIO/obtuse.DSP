
// This example is meant to run on a Pico (rp2040 based), using arduino-pico core, with MIDI input and PWM output
// Tested with arduino-pico 3.3.0 and Arduino IDE 1.8.19 with obtuse 0.2.0
// MIDI input: using https://github.com/FortySevenEffects/arduino_midi_library (tested 5.0.2)
// select Adafruit TinyUSB stack, "Fast" optimization advised

/*** Obtuse DSP ***/

#include "effects.h"
#include "synthFM.h"
#include "synthSampler.h"
#include "synthDrummer.h"

// contexts in obtuse, used to handle internal states
synthFM_Voice_process_type contextv0;
synthSampler_Voice_process_type contextv1;
synthDrummer_Voice_process_type contextboom;
// another round for the filters
effects_Reverb_process_type context_reverb;
effects_SVF_process_type context_svf;

// we will be using the buffered processes for each synth
// to sync with obtuse's vult code
#define BUFFER_SIZE 128

// output buf
int16_t buff[BUFFER_SIZE];
// voices
fix16_t raw0_buff[BUFFER_SIZE];
fix16_t raw1_buff[BUFFER_SIZE];
fix16_t raw2_buff[BUFFER_SIZE];
// mixer
fix16_t raw_buff[BUFFER_SIZE];
// efect
fix16_t filter_buff[BUFFER_SIZE];
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

// counters to pull from time to time (but not to often, to minimize crash) from MIDI messages
long midi_msg_tick = 0;
float midi_msg_freq = 4;

/*** Audio output ***/

// Note: you might switch to I2S with little change in the code for optimum quality

#include <PWMAudio.h>

// instanciate audio output, in mono
#define PWMOUT 18
PWMAudio audioOut(PWMOUT, false);

// 30khz audio, tradeoff between quality and CPU load
const int sampleRate =  30000;

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

void setup() {

  // overclkock for audio DSP, also set CPU speed for a good ratio with 256*fs in case we switch to I2S with MCLK
  set_sys_clock_khz(153600, true); // this one for 30000hz

  /* MIDI */
  // setting device name not working? Come back with later aurduino-pico core.
  usb_midi.setStringDescriptor("ObtuseMIDISynth");

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call usb_midi's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Attach the handleNoteOn function to the MIDI Library. It will
  // be called whenever the Bluefruit receives MIDI Note On messages.
  MIDI.setHandleNoteOn(handleNoteOn);

  // Do the same for MIDI Note Off messages.
  MIDI.setHandleNoteOff(handleNoteOff);

  // And finally, for control change
  MIDI.setHandleControlChange(handleCC);

  // NOTE: for some reason MIDI interface does not init if Serial.begin() is called beforehand -- at least there is too much time between Serial.begin and MIDI.begin, e.g. delay(1000) ??
  Serial.begin(115200);
  delay(1000);
  Serial.println("Let us go");

  /* Audio */

  // configure sample rate
  audioOut.setFrequency(sampleRate);
  // increase buffers from default 8 buffers of 16 values
  // here we want enough for our buffer, x2 because two channels, and one more to be not blocking... and one more just in case
  audioOut.setBuffers(66, 16);
  audioOut.begin();

  delay(100);
  Serial.println("setup ok");

  /* Obtuse DSP */
  // Init FM, then pass sample rate, not forgetting to convert passed parameters to fixed (of course...)
  synthFM_Voice_default(contextv0);
  synthFM_Voice_setSamplerate(contextv0, float_to_fix(sampleRate / (float)1000));
  synthFM_Voice_setNormalize(contextv0, false);
  // Init sampler ocarina
  synthSampler_Voice_default(contextv1);
  synthSampler_Voice_setSamplerate(contextv1, float_to_fix(sampleRate / (float)1000));
  synthSampler_Voice_synthSetLoop(contextv1, true);
  synthSampler_Voice_synthSetLoopStart(contextv1, 5073);
  synthSampler_Voice_synthSetLoopEnd(contextv1, 5992);
  synthSampler_Voice_setNormalize(contextv1, false);
  // Init drummer
  synthDrummer_Voice_default(contextboom);
  synthDrummer_Voice_setSamplerate(contextboom, float_to_fix(sampleRate / (float)1000));
  synthDrummer_Voice_setNormalize(contextboom, false);
  // Effect
  effects_Reverb_default(context_reverb);
  effects_Reverb_setSamplerate(context_reverb, float_to_fix(sampleRate / (float)1000));
  effects_Reverb_setReverbTime(context_reverb, float_to_fix(10.0));
  effects_Reverb_setDelayms(context_reverb, float_to_fix(50.0));
  effects_SVF_default(context_svf);
  effects_SVF_setSamplerate(context_svf, float_to_fix(sampleRate / (float)1000));
  // by default, disable
  effects_SVF_setFreq(context_svf, float_to_fix(sampleRate / (float)2000));
  effects_SVF_setQ(context_svf, float_to_fix(0.0));
  effects_SVF_setType(context_svf, 0);
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
      synthFM_Voice_noteOn(contextv0, current_note, 0, 0);
      synthSampler_Voice_noteOn(contextv1, 127 - current_note, 0, 1);

      midi_tick = millis();
      gate = true;
    }
    if (gate and millis() - midi_tick >= 50) {
      Serial.println("note off");
      synthFM_Voice_noteOff(contextv0, current_note, 0);
      synthSampler_Voice_noteOff(contextv1, 127 - current_note, 0);

      midi_tick = millis();
      gate = false;
    }
  }

  // buffers hard-coded of size 16 (unless setBuffers() is called), with mono output we need as much as one buffer available
  // Make sure there are at least two samples above that free in the audio circular buffer (of buffers)
  // Note: the returned value of availableForWrite() changed across arduino-pico releases, here consider number of bytes
  while (audioOut.availableForWrite() > BUFFER_SIZE + 17  ) {
    // process buffer
    dsp_tick = micros();
    dsp_cycle_tick = rp2040.getCycleCount();

    synthFM_Voice_process_bufferTo(contextv0, BUFFER_SIZE, raw0_buff);
    synthSampler_Voice_process_bufferTo(contextv1, BUFFER_SIZE, raw1_buff);
    synthDrummer_Voice_process_bufferTo(contextboom, BUFFER_SIZE, raw2_buff);
    // mix -- scaling will occur on all voices at once
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
      raw_buff[i] = (raw0_buff[i] + raw1_buff[i] + raw2_buff[i]);
    }
    // apply SVF and then reverb
    effects_SVF_process_bufferTo(context_svf, BUFFER_SIZE, raw_buff, filter_buff);
    effects_Reverb_process_bufferTo(context_reverb, BUFFER_SIZE, filter_buff, reverb_buff);
    // two times to better compare with classical situation
    fix16_t out;
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
      // wet / dry
      //out = 0.5 * raw_buff[i] + 0.5 * reverb_buff[i];
      out = filter_buff[i] + reverb_buff[i];
      // returned float should be between -1 and 1 (should we checkit ?)
      // shortcut, instead of fixed_to_float * 32767, *almost* the same and vastly improve perf with buffered version (???)
      //buff[i] = out / 2 - ( out >> 16);
      // now scale-down at the very end
      buff[i] = out / 10 - ( out >> 16);
    }

    dsp_cycle_count += rp2040.getCycleCount() - dsp_cycle_tick;
    dsp_time += micros() - dsp_tick;

    for (int i = 0; i < BUFFER_SIZE; i++) {
      audioOut.write(buff[i]);
    }
  }

  // Process all incoming MIDI messages
  MidiFlush();
  // fetch message from MIDI to Serial in a second time to minimize crash due to racing condition
  // FIXME: sill not perfect, might disable all logs and/or set watchdog
  if (midi_msg_freq > 0 && millis() - midi_msg_tick > 1. / midi_msg_freq) {
    Sfetch();
    midi_msg_tick = millis();
  }

  // debug
  int newTick = micros();
  if (newTick - tick >= 1000000) {
    unsigned long cycle_count = rp2040.getCycleCount() -  debug_cycle_tick;
    float dsp_cycle_ratio = (float) dsp_cycle_count / cycle_count;
    Serial.print("Running strong! DSP time (useconds): ");
    Serial.print(dsp_time);
    Serial.print(" ("); Serial.print((float)dsp_time / (newTick - tick)); Serial.println("% CPU)");
    Serial.print("CPU cycles ratio: "); Serial.print(dsp_cycle_ratio); Serial.print(" (count: "); Serial.print(dsp_cycle_count); Serial.println(")");

    dsp_time = 0;
    tick += 1000000;
    dsp_cycle_count = 0;
    debug_cycle_tick = rp2040.getCycleCount();
  }

}

// channel: 1..16
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Log when a note is pressed.
  Sprint("Note on: channel = ");
  Sprint(channel);

  Sprint(" pitch = ");
  Sprint(pitch);

  Sprint(" velocity = ");
  Sprintln(velocity);

  // FM by default, sampler on channel 2, drums on channel 3
  if (channel == 3) {
    synthDrummer_Voice_noteOn(contextboom, pitch, velocity, channel);
  }
  else if (channel == 2) {
    synthSampler_Voice_noteOn(contextv1, pitch, velocity, channel);
  } else {
    synthFM_Voice_noteOn(contextv0, pitch, velocity, channel);
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Log when a note is released.
  Sprint("Note off: channel = ");
  Sprint(channel);

  Sprint(" pitch = ");
  Sprint(pitch);

  Sprint(" velocity = ");
  Sprintln(velocity);
  if (channel == 3) {
    synthDrummer_Voice_noteOff(contextboom, pitch, channel);
  }
  else if (channel == 2) {
    synthSampler_Voice_noteOff(contextv1, pitch, channel);
  } else {
    synthFM_Voice_noteOff(contextv0, pitch, channel);
  }
}

void handleCC(byte channel, byte cc, byte value) {
  Sprint("CC on: channel = ");
  Sprint(channel);
  Sprint(" control = ");
  Sprint(cc);
  Sprint(" value = ");
  Sprintln(value);

  if (value > 127) {
    value = 127;
  }
  float ratio = value / 127.0;
  switch (cc) {
    // SVF freq, from 0 to nyquist (in kHz)
    case 62:
      {
        float freq = ratio * (sampleRate / 2000.0);
        Sprint("Setting SVF freq to: ");
        Sprintln(freq);
        effects_SVF_setFreq(context_svf, float_to_fix(freq));
      }
      break;

    // SVF: Q from 0 to ... 5?
    case 63:
      {
        float q = ratio * 3.0;
        Sprint("Setting SVF Q to: ");
        Sprintln(q);
        effects_SVF_setQ(context_svf, float_to_fix(q));
      }
      break;

    // SVF type
    case 75:
      {
        int type = round(ratio * 4);
        Sprint("Setting SVF type to: ");
        Sprint(type);
        switch (type) {
          case 0:
            Sprintln(" (disabled)");
            break;
          case 1:
            Sprintln(" (low pass)");
            break;
          case 2:
            Sprintln(" (high pass)");
            break;
          case 3:
            Sprintln(" (band pass)");
            break;
          case 4:
            Sprintln(" (notch)");
            break;
          default:
            Sprintln(" (unknown)");
            break;
        }
        effects_SVF_setType(context_svf, type);
      }
      break;

    // FM carrier wavetable
    case 78:
      {
        float wavetable = ratio * synthFM_Voice_synthGetNbWavetables(contextv0);
        float wavetable_ratio = fmod(wavetable, 1.0);
        Sprint("Carrier wavetable: ");
        Sprint(int((1 - wavetable_ratio) * 100));
        if (wavetable < 1) {
          Sprint("% sine ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% and triangle.");
        }
        else if (wavetable < 2) {
          Sprint("%  triangle and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% saw.");
        }
        else if (wavetable < 3) {
          Sprint("%  saw and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% square.");
        }
        else if (wavetable < 4) {
          Sprint("%  square and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% sine.");
        }
        else {
          Sprintln(wavetable);
        }
        synthFM_Voice_synthSetCarrierWavetable(contextv0, float_to_fix(wavetable));
      }
      break;

    // FM Modulator wavetable
    case 83:
      {
        float wavetable = ratio * synthFM_Voice_synthGetNbWavetables(contextv0);
        float wavetable_ratio = fmod(wavetable, 1.0);
        Sprint("Modulator wavetable: ");
        Sprint(int((1 - wavetable_ratio) * 100));
        if (wavetable < 1) {
          Sprint("% sine ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% and triangle.");
        }
        else if (wavetable < 2) {
          Sprint("%  triangle and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% saw.");
        }
        else if (wavetable < 3) {
          Sprint("%  saw and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% square.");
        }
        else if (wavetable < 4) {
          Sprint("%  square and ");
          Sprint(int(wavetable_ratio * 100));
          Sprintln("% sine.");
        }
        else {
          Sprintln(wavetable);
        }
        synthFM_Voice_synthSetModulatorWavetable(contextv0, float_to_fix(wavetable));
      }
      break;
  }
}

// pull all pending MIDI messages
void MidiFlush() {
  while (tud_midi_available() > 0) {
    MIDI.read();
  }
}

// automatically called from TinyUSB, disable to avoid changing things during audio processing
/*void tud_midi_rx_cb(uint8_t itf)
  {
  MidiFlush();
  }*/
