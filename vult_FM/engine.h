
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_H
#define ENGINE_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine.tables.h"

static_inline int Sinus_wav_sin_wave_samples(){
   return 8000;
};

static_inline fix16_t Sinus_wav_sin_wave(int channel, int index){
   if(channel == 0){
      return fix_wrap_array(Sinus_wav_sin_wave_chan_0)[(index % 8000)];
   }
   return 0x0 /* 0.000000 */;
}

typedef struct Sinus_wav__ctx_type_2 {
   fix16_t stepRatio;
   fix16_t step;
   fix16_t phase_base;
   fix16_t phase;
   fix16_t fs;
   fix16_t freq;
} Sinus_wav__ctx_type_2;

typedef Sinus_wav__ctx_type_2 Sinus_wav_process_type;

void Sinus_wav__ctx_type_2_init(Sinus_wav__ctx_type_2 &_output_);

static_inline void Sinus_wav_process_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t Sinus_wav_process(Sinus_wav__ctx_type_2 &_ctx){
   _ctx.phase = (_ctx.phase + _ctx.step);
   _ctx.phase = (_ctx.phase % int_to_fix(Sinus_wav_sin_wave_samples()));
   return Sinus_wav_sin_wave(0,fix_to_int((_ctx.phase + _ctx.phase_base)));
}

typedef Sinus_wav__ctx_type_2 Sinus_wav_getSize_type;

static_inline void Sinus_wav_getSize_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline int Sinus_wav_getSize(Sinus_wav__ctx_type_2 &_ctx){
   return Sinus_wav_sin_wave_samples();
};

typedef Sinus_wav__ctx_type_2 Sinus_wav_updateStep_type;

static_inline void Sinus_wav_updateStep_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline void Sinus_wav_updateStep(Sinus_wav__ctx_type_2 &_ctx){
   _ctx.step = fix_mul(_ctx.freq,_ctx.stepRatio);
};

typedef Sinus_wav__ctx_type_2 Sinus_wav_setSamplerate_type;

static_inline void Sinus_wav_setSamplerate_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

void Sinus_wav_setSamplerate(Sinus_wav__ctx_type_2 &_ctx, fix16_t newFs);

typedef Sinus_wav__ctx_type_2 Sinus_wav_setFrequency_type;

static_inline void Sinus_wav_setFrequency_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline void Sinus_wav_setFrequency(Sinus_wav__ctx_type_2 &_ctx, fix16_t newFreq){
   _ctx.freq = newFreq;
   _ctx.step = fix_mul(_ctx.freq,_ctx.stepRatio);
   Sinus_wav_updateStep(_ctx);
}

typedef Sinus_wav__ctx_type_2 Sinus_wav_setPhase_type;

static_inline void Sinus_wav_setPhase_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline void Sinus_wav_setPhase(Sinus_wav__ctx_type_2 &_ctx, fix16_t newPhase){
   _ctx.phase_base = newPhase;
};

typedef Sinus_wav__ctx_type_2 Sinus_wav_default_type;

static_inline void Sinus_wav_default_init(Sinus_wav__ctx_type_2 &_output_){
   Sinus_wav__ctx_type_2_init(_output_);
   return ;
}

static_inline void Sinus_wav_default(Sinus_wav__ctx_type_2 &_ctx){
   Sinus_wav_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   Sinus_wav_setFrequency(_ctx,0x70a3 /* 0.440000 */);
}

typedef struct Engine__ctx_type_0 {
   Sinus_wav__ctx_type_2 modulator;
   fix16_t fs;
   fix16_t carrier_half_phase;
   Sinus_wav__ctx_type_2 carrier;
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

static_inline void Engine_setSamplerate(Engine__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   Sinus_wav_setSamplerate(_ctx.carrier,_ctx.fs);
   Sinus_wav_setSamplerate(_ctx.modulator,_ctx.fs);
}

typedef Engine__ctx_type_0 Engine_default_type;

static_inline void Engine_default_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0_init(_output_);
   return ;
}

static_inline void Engine_default(Engine__ctx_type_0 &_ctx){
   Engine_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   Sinus_wav_setFrequency(_ctx.carrier,0x70a3 /* 0.440000 */);
   Sinus_wav_setFrequency(_ctx.modulator,0x41 /* 0.001000 */);
   _ctx.carrier_half_phase = (int_to_fix(Sinus_wav_getSize(_ctx.carrier)) >> 1);
}



#endif // ENGINE_H
