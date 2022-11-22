
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_H
#define ENGINE_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine.tables.h"

typedef struct Notes__ctx_type_0 {
   uint8_t poly;
   int notes[128];
   int nb_notes;
   int last_notes[128];
} Notes__ctx_type_0;

typedef Notes__ctx_type_0 Notes_setPoly_type;

void Notes__ctx_type_0_init(Notes__ctx_type_0 &_output_);

static_inline void Notes_setPoly_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void Notes_setPoly(Notes__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.poly = flag;
};

typedef Notes__ctx_type_0 Notes_default_type;

static_inline void Notes_default_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void Notes_default(Notes__ctx_type_0 &_ctx){
   Notes_setPoly(_ctx,false);
};

typedef Notes__ctx_type_0 Notes_nbNotes_type;

static_inline void Notes_nbNotes_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline int Notes_nbNotes(Notes__ctx_type_0 &_ctx){
   return _ctx.nb_notes;
};

typedef Notes__ctx_type_0 Notes_firstNote_type;

static_inline void Notes_firstNote_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

int Notes_firstNote(Notes__ctx_type_0 &_ctx);

typedef Notes__ctx_type_0 Notes_lastNote_type;

static_inline void Notes_lastNote_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

int Notes_lastNote(Notes__ctx_type_0 &_ctx);

typedef Notes__ctx_type_0 Notes_noteOn_type;

static_inline void Notes_noteOn_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t Notes_noteOn(Notes__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef Notes__ctx_type_0 Notes_noteOff_type;

static_inline void Notes_noteOff_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t Notes_noteOff(Notes__ctx_type_0 &_ctx, int note, int channel);

static_inline fix16_t Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

typedef struct Util__ctx_type_1 {
   uint8_t pre;
} Util__ctx_type_1;

typedef Util__ctx_type_1 Util_edge_type;

static_inline void Util__ctx_type_1_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1 _ctx;
   _ctx.pre = false;
   _output_ = _ctx;
   return ;
}

static_inline void Util_edge_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t Util_edge(Util__ctx_type_1 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline void Util_buffer(fix16_t (&_output_)[256]){
   fix16_t buff[256];
   fix_copy_array(256,_output_,buff);
   return ;
}

static_inline void Util_buffer_large(fix16_t (&_output_)[8192]){
   fix16_t buff[8192];
   fix_copy_array(8192,_output_,buff);
   return ;
}

static_inline int OSC_sin_wave_samples(){
   return 2048;
};

static_inline fix16_t OSC_sin_wave(int channel, int index){
   if(channel == 0){
      return fix_wrap_array(OSC_sin_wave_chan_0)[(index % 2048)];
   }
   return 0x0 /* 0.000000 */;
}

typedef struct OSC__ctx_type_2 {
   int wavetable;
   fix16_t stepRatio;
   fix16_t step;
   fix16_t rsize;
   fix16_t phase_base;
   fix16_t phase;
   fix16_t fs;
   fix16_t freq;
   fix16_t buffer[256];
} OSC__ctx_type_2;

typedef OSC__ctx_type_2 OSC_getSample_type;

void OSC__ctx_type_2_init(OSC__ctx_type_2 &_output_);

static_inline void OSC_getSample_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

fix16_t OSC_getSample(OSC__ctx_type_2 &_ctx, int index);

typedef OSC__ctx_type_2 OSC_process_type;

static_inline void OSC_process_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t OSC_process(OSC__ctx_type_2 &_ctx){
   _ctx.phase = (_ctx.phase + _ctx.step);
   while(_ctx.phase > _ctx.rsize){
      _ctx.phase = (_ctx.phase + (- _ctx.rsize));
   }
   return OSC_getSample(_ctx,fix_to_int((_ctx.phase + _ctx.phase_base)));
}

typedef OSC__ctx_type_2 OSC_process_buffer_type;

static_inline void OSC_process_buffer_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_process_buffer(OSC__ctx_type_2 &_ctx, int nb, fix16_t (&env)[256], fix16_t (&phase_shift)[256], fix16_t phase_shift_level);

typedef OSC__ctx_type_2 OSC_process_buffer_simple_type;

static_inline void OSC_process_buffer_simple_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_process_buffer_simple(OSC__ctx_type_2 &_ctx, int nb, fix16_t (&env)[256]);

typedef OSC__ctx_type_2 OSC_process_buffer_simplest_type;

static_inline void OSC_process_buffer_simplest_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_process_buffer_simplest(OSC__ctx_type_2 &_ctx, int nb);

typedef OSC__ctx_type_2 OSC_updateStep_type;

static_inline void OSC_updateStep_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_updateStep(OSC__ctx_type_2 &_ctx){
   _ctx.step = fix_mul(_ctx.freq,_ctx.stepRatio);
};

typedef OSC__ctx_type_2 OSC_getBuffer_type;

static_inline void OSC_getBuffer_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_getBuffer(OSC__ctx_type_2 &_ctx, fix16_t (&_output_)[256]){
   fix_copy_array(256,_output_,_ctx.buffer);
   return ;
}

typedef OSC__ctx_type_2 OSC_setSamplerate_type;

static_inline void OSC_setSamplerate_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_setSamplerate(OSC__ctx_type_2 &_ctx, fix16_t newFs);

typedef OSC__ctx_type_2 OSC_setFrequency_type;

static_inline void OSC_setFrequency_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_setFrequency(OSC__ctx_type_2 &_ctx, fix16_t newFreq){
   _ctx.freq = newFreq;
   OSC_updateStep(_ctx);
}

typedef OSC__ctx_type_2 OSC_setPhase_type;

static_inline void OSC_setPhase_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_setPhase(OSC__ctx_type_2 &_ctx, fix16_t newPhase){
   _ctx.phase_base = newPhase;
};

typedef OSC__ctx_type_2 OSC_resetPhase_type;

static_inline void OSC_resetPhase_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_resetPhase(OSC__ctx_type_2 &_ctx){
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.phase_base = 0x0 /* 0.000000 */;
}

typedef OSC__ctx_type_2 OSC_setWavetable_type;

static_inline void OSC_setWavetable_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_setWavetable(OSC__ctx_type_2 &_ctx, int index){
   if(_ctx.wavetable == 0){
      _ctx.rsize = int_to_fix(OSC_sin_wave_samples());
   }
   else
   {
      OSC_setWavetable(_ctx,0);
   }
};

typedef OSC__ctx_type_2 OSC_getSize_type;

static_inline void OSC_getSize_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline int OSC_getSize(OSC__ctx_type_2 &_ctx){
   return fix_to_int(_ctx.rsize);
};

typedef OSC__ctx_type_2 OSC_copyTo_type;

static_inline void OSC_copyTo_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_copyTo(OSC__ctx_type_2 &_ctx, fix16_t (&oBuffer)[256], int nb);

typedef OSC__ctx_type_2 OSC_default_type;

static_inline void OSC_default_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_default(OSC__ctx_type_2 &_ctx);

typedef struct ADSR__ctx_type_0 {
   fix16_t target;
   fix16_t step;
   int state;
   fix16_t s;
   fix16_t r_step;
   fix16_t r;
   fix16_t out;
   fix16_t fs;
   fix16_t d_step;
   fix16_t d;
   fix16_t buffer[256];
   fix16_t a_target;
   fix16_t a_step;
   fix16_t a;
   Util__ctx_type_1 _inst351;
   Util__ctx_type_1 _inst151;
} ADSR__ctx_type_0;

typedef ADSR__ctx_type_0 ADSR_process_type;

void ADSR__ctx_type_0_init(ADSR__ctx_type_0 &_output_);

static_inline void ADSR_process_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

fix16_t ADSR_process(ADSR__ctx_type_0 &_ctx, uint8_t bgate);

typedef ADSR__ctx_type_0 ADSR_process_buffer_type;

static_inline void ADSR_process_buffer_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

void ADSR_process_buffer(ADSR__ctx_type_0 &_ctx, uint8_t bgate, int nb);

typedef ADSR__ctx_type_0 ADSR_updateSteps_type;

static_inline void ADSR_updateSteps_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

void ADSR_updateSteps(ADSR__ctx_type_0 &_ctx);

typedef ADSR__ctx_type_0 ADSR_setSamplerate_type;

static_inline void ADSR_setSamplerate_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

static_inline void ADSR_setSamplerate(ADSR__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   ADSR_updateSteps(_ctx);
}

typedef ADSR__ctx_type_0 ADSR_config_type;

static_inline void ADSR_config_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

void ADSR_config(ADSR__ctx_type_0 &_ctx, fix16_t newA, fix16_t newD, fix16_t newS, fix16_t newR);

typedef ADSR__ctx_type_0 ADSR_copyTo_type;

static_inline void ADSR_copyTo_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

void ADSR_copyTo(ADSR__ctx_type_0 &_ctx, fix16_t (&oBuffer)[256], int nb);

typedef ADSR__ctx_type_0 ADSR_default_type;

static_inline void ADSR_default_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

void ADSR_default(ADSR__ctx_type_0 &_ctx);

typedef struct FM__ctx_type_0 {
   Notes__ctx_type_0 playingnotes;
   int n;
   ADSR__ctx_type_0 modulatoradsr;
   fix16_t modulator_env;
   fix16_t modulatorRatio;
   OSC__ctx_type_2 modulator;
   fix16_t level;
   uint8_t gate;
   fix16_t fs;
   int env_decimation_factor;
   ADSR__ctx_type_0 carrieradsr;
   fix16_t carrier_half_phase;
   fix16_t carrier_env;
   fix16_t carrierRatio;
   OSC__ctx_type_2 carrier;
   fix16_t buffer_modulator_env_short[256];
   fix16_t buffer_modulator_env[256];
   fix16_t buffer_modulator[256];
   fix16_t buffer_carrier_phase[256];
   fix16_t buffer_carrier_env_short[256];
   fix16_t buffer_carrier_env[256];
   fix16_t buffer[256];
} FM__ctx_type_0;

typedef FM__ctx_type_0 FM_process_type;

void FM__ctx_type_0_init(FM__ctx_type_0 &_output_);

static_inline void FM_process_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

fix16_t FM_process(FM__ctx_type_0 &_ctx);

typedef FM__ctx_type_0 FM_process_buffer_type;

static_inline void FM_process_buffer_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

void FM_process_buffer(FM__ctx_type_0 &_ctx, int nb);

typedef FM__ctx_type_0 FM_getBuffer_type;

static_inline void FM_getBuffer_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_getBuffer(FM__ctx_type_0 &_ctx, fix16_t (&_output_)[256]){
   fix_copy_array(256,_output_,_ctx.buffer);
   return ;
}

typedef FM__ctx_type_0 FM_setSamplerate_type;

static_inline void FM_setSamplerate_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

void FM_setSamplerate(FM__ctx_type_0 &_ctx, fix16_t newFs);

typedef FM__ctx_type_0 FM_setCarrierRatio_type;

static_inline void FM_setCarrierRatio_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_setCarrierRatio(FM__ctx_type_0 &_ctx, fix16_t ratio){
   _ctx.carrierRatio = ratio;
};

typedef FM__ctx_type_0 FM_setModulatorRatio_type;

static_inline void FM_setModulatorRatio_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_setModulatorRatio(FM__ctx_type_0 &_ctx, fix16_t ratio){
   _ctx.modulatorRatio = ratio;
};

typedef FM__ctx_type_0 FM_setModulatorLevel_type;

static_inline void FM_setModulatorLevel_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_setModulatorLevel(FM__ctx_type_0 &_ctx, fix16_t newLevel){
   _ctx.level = newLevel;
   _ctx.carrier_half_phase = (fix_mul(_ctx.level,int_to_fix(OSC_getSize(_ctx.carrier))) >> 1);
}

typedef FM__ctx_type_0 FM_setFrequency_type;

static_inline void FM_setFrequency_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_setFrequency(FM__ctx_type_0 &_ctx, fix16_t freq){
   OSC_setFrequency(_ctx.carrier,fix_mul(_ctx.carrierRatio,freq));
   OSC_setFrequency(_ctx.modulator,fix_mul(_ctx.modulatorRatio,freq));
}

typedef FM__ctx_type_0 FM_setPoly_type;

static_inline void FM_setPoly_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

static_inline void FM_setPoly(FM__ctx_type_0 &_ctx, uint8_t flag){
   Notes_setPoly(_ctx.playingnotes,flag);
};

typedef FM__ctx_type_0 FM_noteOn_type;

static_inline void FM_noteOn_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

void FM_noteOn(FM__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef FM__ctx_type_0 FM_noteOff_type;

static_inline void FM_noteOff_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

void FM_noteOff(FM__ctx_type_0 &_ctx, int note, int channel);

typedef FM__ctx_type_0 FM_default_type;

static_inline void FM_default_init(FM__ctx_type_0 &_output_){
   FM__ctx_type_0_init(_output_);
   return ;
}

void FM_default(FM__ctx_type_0 &_ctx);

typedef struct Voice__ctx_type_0 {
   Notes__ctx_type_0 voicesinactive;
   Notes__ctx_type_0 voicesactive;
   fix16_t voices_ratio;
   int voices[4];
   FM__ctx_type_0 voice3FM;
   FM__ctx_type_0 voice2FM;
   FM__ctx_type_0 voice1FM;
   FM__ctx_type_0 voice0FM;
   int synth;
   int number_voices;
   int notes[128];
   fix16_t fs;
} Voice__ctx_type_0;

typedef Voice__ctx_type_0 Voice_getSample_type;

void Voice__ctx_type_0_init(Voice__ctx_type_0 &_output_);

static_inline void Voice_getSample_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

fix16_t Voice_getSample(Voice__ctx_type_0 &_ctx, int voice);

typedef Voice__ctx_type_0 Voice_process_type;

static_inline void Voice_process_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

fix16_t Voice_process(Voice__ctx_type_0 &_ctx);

typedef Voice__ctx_type_0 Voice__sendNoteOn_type;

static_inline void Voice__sendNoteOn_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice__sendNoteOn(Voice__ctx_type_0 &_ctx, int voice, int note, int velocity, int channel);

typedef Voice__ctx_type_0 Voice__sendNoteOff_type;

static_inline void Voice__sendNoteOff_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice__sendNoteOff(Voice__ctx_type_0 &_ctx, int voice, int note, int channel);

typedef Voice__ctx_type_0 Voice_noteOff_type;

static_inline void Voice_noteOff_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_noteOff(Voice__ctx_type_0 &_ctx, int note, int channel);

typedef Voice__ctx_type_0 Voice_noteOn_type;

static_inline void Voice_noteOn_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_noteOn(Voice__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef Voice__ctx_type_0 Voice_setNbVoices_type;

static_inline void Voice_setNbVoices_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_setNbVoices(Voice__ctx_type_0 &_ctx, int nbvoices);

typedef Voice__ctx_type_0 Voice_setSamplerate_type;

static_inline void Voice_setSamplerate_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_setSamplerate(Voice__ctx_type_0 &_ctx, fix16_t newFs);

typedef Voice__ctx_type_0 Voice_selectSynth_type;

static_inline void Voice_selectSynth_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_selectSynth(Voice__ctx_type_0 &_ctx, int nsynth);

typedef Voice__ctx_type_0 Voice_default_type;

static_inline void Voice_default_init(Voice__ctx_type_0 &_output_){
   Voice__ctx_type_0_init(_output_);
   return ;
}

void Voice_default(Voice__ctx_type_0 &_ctx);

typedef struct Comb__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer_d[256];
   fix16_t buffer[8192];
} Comb__ctx_type_0;

typedef Comb__ctx_type_0 Comb_process_type;

void Comb__ctx_type_0_init(Comb__ctx_type_0 &_output_);

static_inline void Comb_process_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

fix16_t Comb_process(Comb__ctx_type_0 &_ctx, fix16_t sample);

typedef Comb__ctx_type_0 Comb_process_buffer_type;

static_inline void Comb_process_buffer_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

void Comb_process_buffer(Comb__ctx_type_0 &_ctx, int nb, fix16_t (&input)[256]);

typedef Comb__ctx_type_0 Comb_getBuffer_type;

static_inline void Comb_getBuffer_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Comb_getBuffer(Comb__ctx_type_0 &_ctx, fix16_t (&_output_)[256]){
   fix_copy_array(256,_output_,_ctx.buffer_d);
   return ;
}

typedef Comb__ctx_type_0 Comb_copyTo_type;

static_inline void Comb_copyTo_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

void Comb_copyTo(Comb__ctx_type_0 &_ctx, fix16_t (&oBuffer)[256], int nb);

typedef Comb__ctx_type_0 Comb_setDecay_type;

static_inline void Comb_setDecay_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Comb_setDecay(Comb__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef Comb__ctx_type_0 Comb_getMaxDelay_type;

static_inline void Comb_getMaxDelay_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

static_inline int Comb_getMaxDelay(Comb__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0;
   }
   return fix_to_int(fix_floor(fix_div(0x20000000 /* 8192.000000 */,_ctx.fs)));
}

typedef Comb__ctx_type_0 Comb_setDelay_type;

static_inline void Comb_setDelay_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Comb_setDelay(Comb__ctx_type_0 &_ctx, int delayms){
   delayms = int_clip(delayms,0,Comb_getMaxDelay(_ctx));
   _ctx.delay = fix_to_int(fix_mul(_ctx.fs,int_to_fix(delayms)));
   _ctx.delay = int_clip(_ctx.delay,0,8192);
   _ctx.pos = 0;
}

typedef Comb__ctx_type_0 Comb_setSamplerate_type;

static_inline void Comb_setSamplerate_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Comb_setSamplerate(Comb__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef Comb__ctx_type_0 Comb_default_type;

static_inline void Comb_default_init(Comb__ctx_type_0 &_output_){
   Comb__ctx_type_0_init(_output_);
   return ;
}

void Comb_default(Comb__ctx_type_0 &_ctx);

typedef struct Reverb__ctx_type_0 {
   Comb__ctx_type_0 comb1;
} Reverb__ctx_type_0;

typedef Reverb__ctx_type_0 Reverb_process_type;

void Reverb__ctx_type_0_init(Reverb__ctx_type_0 &_output_);

static_inline void Reverb_process_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Reverb_process(Reverb__ctx_type_0 &_ctx, fix16_t sample){
   return Comb_process(_ctx.comb1,sample);
};

typedef Reverb__ctx_type_0 Reverb_setDecay_type;

static_inline void Reverb_setDecay_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Reverb_setDecay(Reverb__ctx_type_0 &_ctx, fix16_t newDecay){
   Comb_setDecay(_ctx.comb1,newDecay);
};

typedef Reverb__ctx_type_0 Reverb_setDelay_type;

static_inline void Reverb_setDelay_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Reverb_setDelay(Reverb__ctx_type_0 &_ctx, int delayms){
   Comb_setDelay(_ctx.comb1,delayms);
};

typedef Reverb__ctx_type_0 Reverb_setSamplerate_type;

static_inline void Reverb_setSamplerate_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Reverb_setSamplerate(Reverb__ctx_type_0 &_ctx, fix16_t newFs){
   Comb_setSamplerate(_ctx.comb1,newFs);
};

typedef Reverb__ctx_type_0 Reverb_default_type;

static_inline void Reverb_default_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Reverb_default(Reverb__ctx_type_0 &_ctx){
   Reverb_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   Reverb_setDelay(_ctx,99);
   Reverb_setDecay(_ctx,0x4a3d /* 0.290000 */);
}



#endif // ENGINE_H
