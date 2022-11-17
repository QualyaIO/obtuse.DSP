
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_H
#define ENGINE_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine.tables.h"

typedef struct Reverb__ctx_type_0 {
   int pos;
   fix16_t decay;
   fix16_t buffer[40000];
} Reverb__ctx_type_0;

typedef Reverb__ctx_type_0 Reverb_process_type;

void Reverb__ctx_type_0_init(Reverb__ctx_type_0 &_output_);

static_inline void Reverb_process_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

fix16_t Reverb_process(Reverb__ctx_type_0 &_ctx, fix16_t sample);

typedef struct Notes__ctx_type_0 {
   int notes[128];
   int nb_notes;
   int last_notes[128];
} Notes__ctx_type_0;

typedef Notes__ctx_type_0 Notes_default_type;

void Notes__ctx_type_0_init(Notes__ctx_type_0 &_output_);

static_inline void Notes_default_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void Notes_default(Notes__ctx_type_0 &_ctx){
}

typedef Notes__ctx_type_0 Notes_nbNotes_type;

static_inline void Notes_nbNotes_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline int Notes_nbNotes(Notes__ctx_type_0 &_ctx){
   return _ctx.nb_notes;
};

typedef Notes__ctx_type_0 Notes_noteOn_type;

static_inline void Notes_noteOn_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

void Notes_noteOn(Notes__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef Notes__ctx_type_0 Notes_noteOff_type;

static_inline void Notes_noteOff_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

void Notes_noteOff(Notes__ctx_type_0 &_ctx, int note, int channel);

typedef Notes__ctx_type_0 Notes_lastNote_type;

static_inline void Notes_lastNote_init(Notes__ctx_type_0 &_output_){
   Notes__ctx_type_0_init(_output_);
   return ;
}

int Notes_lastNote(Notes__ctx_type_0 &_ctx);

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

static_inline void Util_buffer(fix16_t (&_output_)[56]){
   fix16_t buff[56];
   fix_copy_array(56,_output_,buff);
   return ;
}

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
   fix16_t a_target;
   fix16_t a_step;
   fix16_t a;
   Util__ctx_type_1 _inst151;
} ADSR__ctx_type_0;

typedef ADSR__ctx_type_0 ADSR_process_type;

void ADSR__ctx_type_0_init(ADSR__ctx_type_0 &_output_);

static_inline void ADSR_process_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

fix16_t ADSR_process(ADSR__ctx_type_0 &_ctx, uint8_t bgate);

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

typedef ADSR__ctx_type_0 ADSR_default_type;

static_inline void ADSR_default_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0_init(_output_);
   return ;
}

static_inline void ADSR_default(ADSR__ctx_type_0 &_ctx){
   _ctx.a_target = 0x10000 /* 1.000000 */;
   ADSR_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   ADSR_config(_ctx,0x0 /* 0.000000 */,0x0 /* 0.000000 */,0x8000 /* 0.500000 */,0x0 /* 0.000000 */);
}

static_inline int OSC_sin_wave_samples(){
   return 8000;
};

static_inline fix16_t OSC_sin_wave(int channel, int index){
   if(channel == 0){
      return fix_wrap_array(OSC_sin_wave_chan_0)[(index % 8000)];
   }
   return 0x0 /* 0.000000 */;
}

typedef struct OSC__ctx_type_2 {
   int wavetable;
   fix16_t stepRatio;
   fix16_t step;
   fix16_t phase_base;
   fix16_t phase;
   fix16_t fs;
   fix16_t freq;
   fix16_t buffer[56];
} OSC__ctx_type_2;

typedef OSC__ctx_type_2 OSC_get_sample_type;

void OSC__ctx_type_2_init(OSC__ctx_type_2 &_output_);

static_inline void OSC_get_sample_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

fix16_t OSC_get_sample(OSC__ctx_type_2 &_ctx, int index);

typedef OSC__ctx_type_2 OSC_getSize_type;

static_inline void OSC_getSize_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

int OSC_getSize(OSC__ctx_type_2 &_ctx);

typedef OSC__ctx_type_2 OSC_process_buffer_type;

static_inline void OSC_process_buffer_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_process_buffer(OSC__ctx_type_2 &_ctx, int nb);

typedef OSC__ctx_type_2 OSC_process_type;

static_inline void OSC_process_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

fix16_t OSC_process(OSC__ctx_type_2 &_ctx);

typedef OSC__ctx_type_2 OSC_updateStep_type;

static_inline void OSC_updateStep_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

static_inline void OSC_updateStep(OSC__ctx_type_2 &_ctx){
   _ctx.step = fix_mul(_ctx.freq,_ctx.stepRatio);
};

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
   _ctx.wavetable = index;
};

typedef OSC__ctx_type_2 OSC_default_type;

static_inline void OSC_default_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2_init(_output_);
   return ;
}

void OSC_default(OSC__ctx_type_2 &_ctx);

typedef struct Engine__ctx_type_0 {
   Notes__ctx_type_0 playingnotes;
   int n;
   ADSR__ctx_type_0 modulatoradsr;
   fix16_t modulator_env;
   fix16_t modulatorRatio;
   OSC__ctx_type_2 modulator;
   uint8_t gate;
   fix16_t fs;
   int env_decimation_factor;
   ADSR__ctx_type_0 carrieradsr;
   fix16_t carrier_half_phase;
   fix16_t carrier_env;
   fix16_t carrierRatio;
   OSC__ctx_type_2 carrier;
} Engine__ctx_type_0;

typedef Engine__ctx_type_0 Engine_process_type;

void Engine__ctx_type_0_init(Engine__ctx_type_0 &_output_);

static_inline void Engine_process_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

fix16_t Engine_process(Engine__ctx_type_0 &_ctx);

typedef Engine__ctx_type_0 Engine_setSamplerate_type;

static_inline void Engine_setSamplerate_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

void Engine_setSamplerate(Engine__ctx_type_0 &_ctx, fix16_t newFs);

typedef Engine__ctx_type_0 Engine_setCarrierRatio_type;

static_inline void Engine_setCarrierRatio_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_setCarrierRatio(Engine__ctx_type_0 &_ctx, fix16_t ratio){
   _ctx.carrierRatio = ratio;
};

typedef Engine__ctx_type_0 Engine_setModulatorRatio_type;

static_inline void Engine_setModulatorRatio_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_setModulatorRatio(Engine__ctx_type_0 &_ctx, fix16_t ratio){
   _ctx.modulatorRatio = ratio;
};

typedef Engine__ctx_type_0 Engine_setModulatorLevel_type;

static_inline void Engine_setModulatorLevel_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_setModulatorLevel(Engine__ctx_type_0 &_ctx, fix16_t level){
   _ctx.carrier_half_phase = (fix_mul(level,int_to_fix(OSC_getSize(_ctx.carrier))) >> 1);
};

typedef Engine__ctx_type_0 Engine_setFrequency_type;

static_inline void Engine_setFrequency_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_setFrequency(Engine__ctx_type_0 &_ctx, fix16_t freq){
   OSC_setFrequency(_ctx.carrier,fix_mul(_ctx.carrierRatio,freq));
   OSC_setFrequency(_ctx.modulator,fix_mul(_ctx.modulatorRatio,freq));
}

typedef Engine__ctx_type_0 Engine_noteOn_type;

static_inline void Engine_noteOn_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_noteOn(Engine__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   Notes_noteOn(_ctx.playingnotes,note,velocity,channel);
   Engine_setFrequency(_ctx,Util_noteToFrequency(note));
   _ctx.gate = true;
}

typedef Engine__ctx_type_0 Engine_noteOff_type;

static_inline void Engine_noteOff_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

void Engine_noteOff(Engine__ctx_type_0 &_ctx, int note, int channel);

typedef Engine__ctx_type_0 Engine_default_type;

static_inline void Engine_default_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

void Engine_default(Engine__ctx_type_0 &_ctx);



#endif // ENGINE_H
