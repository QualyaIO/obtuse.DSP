
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef EFFECTS_H
#define EFFECTS_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "effects.tables.h"

static_inline void effects_Buffer_buffer(fix16_t (&oBuff)[128]){
}

void effects_Buffer_buffer_large(fix16_t (&oBuff)[2048]);

static_inline int effects_Buffer_bufferSize(){
   return 128;
};

static_inline int effects_Buffer_bufferLargeSize(){
   return 2048;
};

typedef struct effects_CombFB__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer[2048];
} effects_CombFB__ctx_type_0;

typedef effects_CombFB__ctx_type_0 effects_CombFB_process_type;

void effects_CombFB__ctx_type_0_init(effects_CombFB__ctx_type_0 &_output_);

static_inline void effects_CombFB_process_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

fix16_t effects_CombFB_process(effects_CombFB__ctx_type_0 &_ctx, fix16_t sample);

typedef effects_CombFB__ctx_type_0 effects_CombFB_process_bufferTo_type;

static_inline void effects_CombFB_process_bufferTo_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

void effects_CombFB_process_bufferTo(effects_CombFB__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_CombFB__ctx_type_0 effects_CombFB_setDecay_type;

static_inline void effects_CombFB_setDecay_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFB_setDecay(effects_CombFB__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef effects_CombFB__ctx_type_0 effects_CombFB_getMaxDelay_type;

static_inline void effects_CombFB_getMaxDelay_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline int effects_CombFB_getMaxDelay(effects_CombFB__ctx_type_0 &_ctx){
   return 2048;
};

typedef effects_CombFB__ctx_type_0 effects_CombFB_getMaxDelayms_type;

static_inline void effects_CombFB_getMaxDelayms_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effects_CombFB_getMaxDelayms(effects_CombFB__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x8000000 /* 2048.000000 */,_ctx.fs);
}

typedef effects_CombFB__ctx_type_0 effects_CombFB_setDelay_type;

static_inline void effects_CombFB_setDelay_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFB_setDelay(effects_CombFB__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effects_CombFB_getMaxDelay(_ctx));
   _ctx.pos = (_ctx.pos % _ctx.delay);
}

typedef effects_CombFB__ctx_type_0 effects_CombFB_setDelayms_type;

static_inline void effects_CombFB_setDelayms_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFB_setDelayms(effects_CombFB__ctx_type_0 &_ctx, fix16_t delayms){
   effects_CombFB_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effects_CombFB__ctx_type_0 effects_CombFB_setSamplerate_type;

static_inline void effects_CombFB_setSamplerate_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFB_setSamplerate(effects_CombFB__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effects_CombFB__ctx_type_0 effects_CombFB_default_type;

static_inline void effects_CombFB_default_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFB_default(effects_CombFB__ctx_type_0 &_ctx){
   effects_Buffer_buffer_large(_ctx.buffer);
   effects_CombFB_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effects_CombFB_setDelayms(_ctx,0x320000 /* 50.000000 */);
   effects_CombFB_setDecay(_ctx,0x8000 /* 0.500000 */);
}

typedef struct effects_CombFB__ctx_type_1 {
   effects_CombFB__ctx_type_0 _inst13c;
} effects_CombFB__ctx_type_1;

typedef effects_CombFB__ctx_type_1 effects_CombFB_dummy_type;

static_inline void effects_CombFB__ctx_type_1_init(effects_CombFB__ctx_type_1 &_output_){
   effects_CombFB__ctx_type_1 &_ctx = _output_;
   effects_CombFB__ctx_type_0_init(_ctx._inst13c);
   
   return ;
}

static_inline void effects_CombFB_dummy_init(effects_CombFB__ctx_type_1 &_output_){
   effects_CombFB__ctx_type_1_init(_output_);
   return ;
}

static_inline void effects_CombFB_dummy(effects_CombFB__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_CombFB_process_bufferTo(_ctx._inst13c,0,buff,buff);
}

typedef struct effects_Allpass__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer_allpassed[2048];
   fix16_t buffer[2048];
} effects_Allpass__ctx_type_0;

typedef effects_Allpass__ctx_type_0 effects_Allpass_process_type;

void effects_Allpass__ctx_type_0_init(effects_Allpass__ctx_type_0 &_output_);

static_inline void effects_Allpass_process_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

fix16_t effects_Allpass_process(effects_Allpass__ctx_type_0 &_ctx, fix16_t sample);

typedef effects_Allpass__ctx_type_0 effects_Allpass_process_bufferTo_type;

static_inline void effects_Allpass_process_bufferTo_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

void effects_Allpass_process_bufferTo(effects_Allpass__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_Allpass__ctx_type_0 effects_Allpass_setDecay_type;

static_inline void effects_Allpass_setDecay_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_Allpass_setDecay(effects_Allpass__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + (_ctx.decay << 1)));
}

typedef effects_Allpass__ctx_type_0 effects_Allpass_getMaxDelay_type;

static_inline void effects_Allpass_getMaxDelay_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline int effects_Allpass_getMaxDelay(effects_Allpass__ctx_type_0 &_ctx){
   return 2048;
};

typedef effects_Allpass__ctx_type_0 effects_Allpass_getMaxDelayms_type;

static_inline void effects_Allpass_getMaxDelayms_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effects_Allpass_getMaxDelayms(effects_Allpass__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x8000000 /* 2048.000000 */,_ctx.fs);
}

typedef effects_Allpass__ctx_type_0 effects_Allpass_setDelay_type;

static_inline void effects_Allpass_setDelay_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_Allpass_setDelay(effects_Allpass__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effects_Allpass_getMaxDelay(_ctx));
   _ctx.pos = (_ctx.pos % _ctx.delay);
}

typedef effects_Allpass__ctx_type_0 effects_Allpass_setDelayms_type;

static_inline void effects_Allpass_setDelayms_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_Allpass_setDelayms(effects_Allpass__ctx_type_0 &_ctx, fix16_t delayms){
   effects_Allpass_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effects_Allpass__ctx_type_0 effects_Allpass_setSamplerate_type;

static_inline void effects_Allpass_setSamplerate_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_Allpass_setSamplerate(effects_Allpass__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effects_Allpass__ctx_type_0 effects_Allpass_default_type;

static_inline void effects_Allpass_default_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0_init(_output_);
   return ;
}

void effects_Allpass_default(effects_Allpass__ctx_type_0 &_ctx);

typedef struct effects_Allpass__ctx_type_1 {
   effects_Allpass__ctx_type_0 _inst156;
} effects_Allpass__ctx_type_1;

typedef effects_Allpass__ctx_type_1 effects_Allpass_dummy_type;

static_inline void effects_Allpass__ctx_type_1_init(effects_Allpass__ctx_type_1 &_output_){
   effects_Allpass__ctx_type_1 &_ctx = _output_;
   effects_Allpass__ctx_type_0_init(_ctx._inst156);
   
   return ;
}

static_inline void effects_Allpass_dummy_init(effects_Allpass__ctx_type_1 &_output_){
   effects_Allpass__ctx_type_1_init(_output_);
   return ;
}

static_inline void effects_Allpass_dummy(effects_Allpass__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_Allpass_process_bufferTo(_ctx._inst156,0,buff,buff);
}

typedef struct effects_Reverb__ctx_type_0 {
   fix16_t reverbtime;
   fix16_t fs;
   int comb3delay;
   effects_CombFB__ctx_type_0 comb3;
   int comb2delay;
   effects_CombFB__ctx_type_0 comb2;
   int comb1delay;
   effects_CombFB__ctx_type_0 comb1;
   int comb0delay;
   effects_CombFB__ctx_type_0 comb0;
   fix16_t buffer_c3[128];
   fix16_t buffer_c2[128];
   fix16_t buffer_c1[128];
   fix16_t buffer_c0[128];
   fix16_t buffer_a1[128];
   fix16_t buffer_a0[128];
   effects_Allpass__ctx_type_0 allpass1;
   effects_Allpass__ctx_type_0 allpass0;
} effects_Reverb__ctx_type_0;

typedef effects_Reverb__ctx_type_0 effects_Reverb_process_type;

void effects_Reverb__ctx_type_0_init(effects_Reverb__ctx_type_0 &_output_);

static_inline void effects_Reverb_process_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effects_Reverb_process(effects_Reverb__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t combs_filter;
   combs_filter = ((effects_CombFB_process(_ctx.comb0,sample) + effects_CombFB_process(_ctx.comb1,sample) + effects_CombFB_process(_ctx.comb2,sample) + effects_CombFB_process(_ctx.comb3,sample)) >> 2);
   return effects_Allpass_process(_ctx.allpass1,effects_Allpass_process(_ctx.allpass0,combs_filter));
}

typedef effects_Reverb__ctx_type_0 effects_Reverb_process_bufferTo_type;

static_inline void effects_Reverb_process_bufferTo_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effects_Reverb_process_bufferTo(effects_Reverb__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_Reverb__ctx_type_0 effects_Reverb_setSamplerate_type;

static_inline void effects_Reverb_setSamplerate_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effects_Reverb_setSamplerate(effects_Reverb__ctx_type_0 &_ctx, fix16_t newFs);

typedef effects_Reverb__ctx_type_0 effects_Reverb_setReverbTime_type;

static_inline void effects_Reverb_setReverbTime_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effects_Reverb_setReverbTime(effects_Reverb__ctx_type_0 &_ctx, fix16_t newReverbtime);

typedef effects_Reverb__ctx_type_0 effects_Reverb_setDelayms_type;

static_inline void effects_Reverb_setDelayms_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effects_Reverb_setDelayms(effects_Reverb__ctx_type_0 &_ctx, fix16_t delayms);

typedef effects_Reverb__ctx_type_0 effects_Reverb_default_type;

static_inline void effects_Reverb_default_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effects_Reverb_default(effects_Reverb__ctx_type_0 &_ctx);

typedef struct effects_Reverb__ctx_type_1 {
   effects_Reverb__ctx_type_0 _inst1f2;
} effects_Reverb__ctx_type_1;

typedef effects_Reverb__ctx_type_1 effects_Reverb_dummy_type;

static_inline void effects_Reverb__ctx_type_1_init(effects_Reverb__ctx_type_1 &_output_){
   effects_Reverb__ctx_type_1 &_ctx = _output_;
   effects_Reverb__ctx_type_0_init(_ctx._inst1f2);
   
   return ;
}

static_inline void effects_Reverb_dummy_init(effects_Reverb__ctx_type_1 &_output_){
   effects_Reverb__ctx_type_1_init(_output_);
   return ;
}

static_inline void effects_Reverb_dummy(effects_Reverb__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_Reverb_process_bufferTo(_ctx._inst1f2,0,buff,buff);
}

static_inline fix16_t effects_Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

static_inline fix16_t effects_Util_tonesToCoeff(fix16_t semitones){
   fix16_t log_base;
   log_base = 0xb172 /* 0.693147 */;
   return fix_exp(fix_mul(fix_mul(0x1555 /* 0.083333 */,log_base),semitones));
}

typedef struct effects_Util__ctx_type_2 {
   uint8_t pre;
} effects_Util__ctx_type_2;

typedef effects_Util__ctx_type_2 effects_Util_edge_type;

static_inline void effects_Util__ctx_type_2_init(effects_Util__ctx_type_2 &_output_){
   effects_Util__ctx_type_2 &_ctx = _output_;
   _ctx.pre = false;
   
   return ;
}

static_inline void effects_Util_edge_init(effects_Util__ctx_type_2 &_output_){
   effects_Util__ctx_type_2_init(_output_);
   return ;
}

static_inline uint8_t effects_Util_edge(effects_Util__ctx_type_2 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline fix16_t effects_Util_cubic_clipper(fix16_t x){
   if(x <= -0xaaaa /* -0.666667 */){
      return -0xaaaa /* -0.666667 */;
   }
   else
   {
      if(x >= 0xaaaa /* 0.666667 */){
         return 0xaaaa /* 0.666667 */;
      }
      else
      {
         return (x + fix_mul(fix_mul(fix_mul(-0x5555 /* -0.333333 */,x),x),x));
      }
   }
};

typedef struct effects_Util__ctx_type_4 {
   fix16_t pre_x;
} effects_Util__ctx_type_4;

typedef effects_Util__ctx_type_4 effects_Util_change_type;

static_inline void effects_Util__ctx_type_4_init(effects_Util__ctx_type_4 &_output_){
   effects_Util__ctx_type_4 &_ctx = _output_;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   
   return ;
}

static_inline void effects_Util_change_init(effects_Util__ctx_type_4 &_output_){
   effects_Util__ctx_type_4_init(_output_);
   return ;
}

static_inline uint8_t effects_Util_change(effects_Util__ctx_type_4 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

typedef struct effects_Util__ctx_type_5 {
   fix16_t x;
} effects_Util__ctx_type_5;

typedef effects_Util__ctx_type_5 effects_Util_smooth_type;

static_inline void effects_Util__ctx_type_5_init(effects_Util__ctx_type_5 &_output_){
   effects_Util__ctx_type_5 &_ctx = _output_;
   _ctx.x = 0x0 /* 0.000000 */;
   
   return ;
}

static_inline void effects_Util_smooth_init(effects_Util__ctx_type_5 &_output_){
   effects_Util__ctx_type_5_init(_output_);
   return ;
}

static_inline fix16_t effects_Util_smooth(effects_Util__ctx_type_5 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t effects_Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

typedef struct effects_Ladder__ctx_type_0 {
   fix16_t p3;
   fix16_t p2;
   fix16_t p1;
   fix16_t p0;
} effects_Ladder__ctx_type_0;

typedef effects_Ladder__ctx_type_0 effects_Ladder_heun_type;

void effects_Ladder__ctx_type_0_init(effects_Ladder__ctx_type_0 &_output_);

static_inline void effects_Ladder_heun_init(effects_Ladder__ctx_type_0 &_output_){
   effects_Ladder__ctx_type_0_init(_output_);
   return ;
}

fix16_t effects_Ladder_heun(effects_Ladder__ctx_type_0 &_ctx, fix16_t input, fix16_t fh, fix16_t res);

typedef struct effects_Ladder__ctx_type_1 {
   fix16_t p3;
   fix16_t p2;
   fix16_t p1;
   fix16_t p0;
} effects_Ladder__ctx_type_1;

typedef effects_Ladder__ctx_type_1 effects_Ladder_euler_type;

void effects_Ladder__ctx_type_1_init(effects_Ladder__ctx_type_1 &_output_);

static_inline void effects_Ladder_euler_init(effects_Ladder__ctx_type_1 &_output_){
   effects_Ladder__ctx_type_1_init(_output_);
   return ;
}

fix16_t effects_Ladder_euler(effects_Ladder__ctx_type_1 &_ctx, fix16_t input, fix16_t fh, fix16_t res);

typedef struct effects_Ladder__ctx_type_2 {
   fix16_t tune_table[1024];
   fix16_t tuneRatio;
   fix16_t rsize;
   fix16_t res;
   uint8_t heun;
   effects_Ladder__ctx_type_0 h;
   fix16_t fs_nyquist;
   fix16_t fs;
   fix16_t fh;
   effects_Ladder__ctx_type_1 e;
   fix16_t cut;
   effects_Util__ctx_type_4 _inst43b;
   effects_Util__ctx_type_4 _inst13b;
} effects_Ladder__ctx_type_2;

typedef effects_Ladder__ctx_type_2 effects_Ladder_getTune_type;

void effects_Ladder__ctx_type_2_init(effects_Ladder__ctx_type_2 &_output_);

static_inline void effects_Ladder_getTune_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effects_Ladder_getTune(effects_Ladder__ctx_type_2 &_ctx, fix16_t cut);

typedef effects_Ladder__ctx_type_2 effects_Ladder_process_euler_type;

static_inline void effects_Ladder_process_euler_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effects_Ladder_process_euler(effects_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res);

typedef effects_Ladder__ctx_type_2 effects_Ladder_process_heun_type;

static_inline void effects_Ladder_process_heun_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effects_Ladder_process_heun(effects_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res);

typedef effects_Ladder__ctx_type_2 effects_Ladder_process_type;

static_inline void effects_Ladder_process_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t effects_Ladder_process(effects_Ladder__ctx_type_2 &_ctx, fix16_t input){
   if(_ctx.heun){
      return effects_Ladder_process_heun(_ctx,input,_ctx.cut,_ctx.res);
   }
   else
   {
      return effects_Ladder_process_euler(_ctx,input,_ctx.cut,_ctx.res);
   }
};

typedef effects_Ladder__ctx_type_2 effects_Ladder_process_bufferTo_type;

static_inline void effects_Ladder_process_bufferTo_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effects_Ladder_process_bufferTo(effects_Ladder__ctx_type_2 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_Ladder__ctx_type_2 effects_Ladder_updateTune_type;

static_inline void effects_Ladder_updateTune_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effects_Ladder_updateTune(effects_Ladder__ctx_type_2 &_ctx);

typedef effects_Ladder__ctx_type_2 effects_Ladder_setEstimationMethod_type;

static_inline void effects_Ladder_setEstimationMethod_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effects_Ladder_setEstimationMethod(effects_Ladder__ctx_type_2 &_ctx, int method){
   if(method == 1){
      _ctx.heun = true;
   }
   else
   {
      _ctx.heun = false;
   }
};

typedef effects_Ladder__ctx_type_2 effects_Ladder_setCutOff_type;

static_inline void effects_Ladder_setCutOff_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effects_Ladder_setCutOff(effects_Ladder__ctx_type_2 &_ctx, fix16_t newCut){
   _ctx.cut = fix_clip(newCut,0x0 /* 0.000000 */,_ctx.fs_nyquist);
};

typedef effects_Ladder__ctx_type_2 effects_Ladder_setResonance_type;

static_inline void effects_Ladder_setResonance_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effects_Ladder_setResonance(effects_Ladder__ctx_type_2 &_ctx, fix16_t newRes){
   _ctx.res = newRes;
};

typedef effects_Ladder__ctx_type_2 effects_Ladder_setSamplerate_type;

static_inline void effects_Ladder_setSamplerate_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effects_Ladder_setSamplerate(effects_Ladder__ctx_type_2 &_ctx, fix16_t newFs);

typedef effects_Ladder__ctx_type_2 effects_Ladder_default_type;

static_inline void effects_Ladder_default_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effects_Ladder_default(effects_Ladder__ctx_type_2 &_ctx){
   _ctx.rsize = 0x4000000 /* 1024.000000 */;
   effects_Ladder_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effects_Ladder_setEstimationMethod(_ctx,0);
}

typedef struct effects_Ladder__ctx_type_3 {
   effects_Ladder__ctx_type_2 _inst163;
} effects_Ladder__ctx_type_3;

typedef effects_Ladder__ctx_type_3 effects_Ladder_dummy_type;

static_inline void effects_Ladder__ctx_type_3_init(effects_Ladder__ctx_type_3 &_output_){
   effects_Ladder__ctx_type_3 &_ctx = _output_;
   effects_Ladder__ctx_type_2_init(_ctx._inst163);
   
   return ;
}

static_inline void effects_Ladder_dummy_init(effects_Ladder__ctx_type_3 &_output_){
   effects_Ladder__ctx_type_3_init(_output_);
   return ;
}

static_inline void effects_Ladder_dummy(effects_Ladder__ctx_type_3 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_Ladder_process_bufferTo(_ctx._inst163,0,buff,buff);
}

typedef struct effects_CombFF__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer[2048];
} effects_CombFF__ctx_type_0;

typedef effects_CombFF__ctx_type_0 effects_CombFF_process_type;

void effects_CombFF__ctx_type_0_init(effects_CombFF__ctx_type_0 &_output_);

static_inline void effects_CombFF_process_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

fix16_t effects_CombFF_process(effects_CombFF__ctx_type_0 &_ctx, fix16_t sample);

typedef effects_CombFF__ctx_type_0 effects_CombFF_process_bufferTo_type;

static_inline void effects_CombFF_process_bufferTo_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

void effects_CombFF_process_bufferTo(effects_CombFF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_CombFF__ctx_type_0 effects_CombFF_setDecay_type;

static_inline void effects_CombFF_setDecay_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFF_setDecay(effects_CombFF__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef effects_CombFF__ctx_type_0 effects_CombFF_getMaxDelay_type;

static_inline void effects_CombFF_getMaxDelay_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline int effects_CombFF_getMaxDelay(effects_CombFF__ctx_type_0 &_ctx){
   return 2048;
};

typedef effects_CombFF__ctx_type_0 effects_CombFF_getMaxDelayms_type;

static_inline void effects_CombFF_getMaxDelayms_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effects_CombFF_getMaxDelayms(effects_CombFF__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x8000000 /* 2048.000000 */,_ctx.fs);
}

typedef effects_CombFF__ctx_type_0 effects_CombFF_setDelay_type;

static_inline void effects_CombFF_setDelay_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFF_setDelay(effects_CombFF__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effects_CombFF_getMaxDelay(_ctx));
   _ctx.pos = (_ctx.pos % _ctx.delay);
}

typedef effects_CombFF__ctx_type_0 effects_CombFF_setDelayms_type;

static_inline void effects_CombFF_setDelayms_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFF_setDelayms(effects_CombFF__ctx_type_0 &_ctx, fix16_t delayms){
   effects_CombFF_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effects_CombFF__ctx_type_0 effects_CombFF_setSamplerate_type;

static_inline void effects_CombFF_setSamplerate_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFF_setSamplerate(effects_CombFF__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effects_CombFF__ctx_type_0 effects_CombFF_default_type;

static_inline void effects_CombFF_default_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_CombFF_default(effects_CombFF__ctx_type_0 &_ctx){
   effects_Buffer_buffer_large(_ctx.buffer);
   effects_CombFF_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effects_CombFF_setDelayms(_ctx,0x320000 /* 50.000000 */);
   effects_CombFF_setDecay(_ctx,0x8000 /* 0.500000 */);
}

typedef struct effects_CombFF__ctx_type_1 {
   effects_CombFF__ctx_type_0 _inst115;
} effects_CombFF__ctx_type_1;

typedef effects_CombFF__ctx_type_1 effects_CombFF_dummy_type;

static_inline void effects_CombFF__ctx_type_1_init(effects_CombFF__ctx_type_1 &_output_){
   effects_CombFF__ctx_type_1 &_ctx = _output_;
   effects_CombFF__ctx_type_0_init(_ctx._inst115);
   
   return ;
}

static_inline void effects_CombFF_dummy_init(effects_CombFF__ctx_type_1 &_output_){
   effects_CombFF__ctx_type_1_init(_output_);
   return ;
}

static_inline void effects_CombFF_dummy(effects_CombFF__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_CombFF_process_bufferTo(_ctx._inst115,0,buff,buff);
}

static_inline fix16_t effects_Saturator_tanh_table_raw_c0(int index){
   return effects_Saturator_tanh_table_c0[index];
};

static_inline fix16_t effects_Saturator_tanh_table_raw_c1(int index){
   return effects_Saturator_tanh_table_c1[index];
};

static_inline fix16_t effects_Saturator_tanh_table_raw_c2(int index){
   return effects_Saturator_tanh_table_c2[index];
};

static_inline fix16_t effects_Saturator_tanh_table(fix16_t x){
   int index;
   index = int_clip(fix_to_int(fix_mul(0x3fe000 /* 63.875000 */,(0x40000 /* 4.000000 */ + x))),0,511);
   return (fix_wrap_array(effects_Saturator_tanh_table_c0)[index] + fix_mul(x,(fix_wrap_array(effects_Saturator_tanh_table_c1)[index] + fix_mul(x,fix_wrap_array(effects_Saturator_tanh_table_c2)[index]))));
}

fix16_t effects_Saturator_tanh_wrapper(fix16_t x);

static_inline fix16_t effects_Saturator_getMinCoeff(){
   return -0x3e80000 /* -1000.000000 */;
};

static_inline fix16_t effects_Saturator_getMaxCoeff(){
   return 0x3e80000 /* 1000.000000 */;
};

typedef struct effects_Saturator__ctx_type_7 {
   fix16_t threshopp;
   fix16_t threshinv;
   fix16_t thresh;
   fix16_t coeff;
} effects_Saturator__ctx_type_7;

typedef effects_Saturator__ctx_type_7 effects_Saturator_process_type;

void effects_Saturator__ctx_type_7_init(effects_Saturator__ctx_type_7 &_output_);

static_inline void effects_Saturator_process_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7_init(_output_);
   return ;
}

fix16_t effects_Saturator_process(effects_Saturator__ctx_type_7 &_ctx, fix16_t x);

typedef effects_Saturator__ctx_type_7 effects_Saturator_process_bufferTo_type;

static_inline void effects_Saturator_process_bufferTo_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7_init(_output_);
   return ;
}

void effects_Saturator_process_bufferTo(effects_Saturator__ctx_type_7 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_Saturator__ctx_type_7 effects_Saturator_setThreshold_type;

static_inline void effects_Saturator_setThreshold_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7_init(_output_);
   return ;
}

static_inline void effects_Saturator_setThreshold(effects_Saturator__ctx_type_7 &_ctx, fix16_t t){
   _ctx.thresh = fix_clip(t,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.threshopp = (0x10000 /* 1.000000 */ + (- _ctx.thresh));
   if(_ctx.thresh < 0x10000 /* 1.000000 */){
      _ctx.threshinv = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + (- _ctx.thresh)));
   }
}

typedef effects_Saturator__ctx_type_7 effects_Saturator_setCoeff_type;

static_inline void effects_Saturator_setCoeff_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7_init(_output_);
   return ;
}

static_inline void effects_Saturator_setCoeff(effects_Saturator__ctx_type_7 &_ctx, fix16_t c){
   _ctx.coeff = fix_clip(c,-0x3e80000 /* -1000.000000 */,0x3e80000 /* 1000.000000 */);
};

typedef effects_Saturator__ctx_type_7 effects_Saturator_default_type;

static_inline void effects_Saturator_default_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7_init(_output_);
   return ;
}

static_inline void effects_Saturator_default(effects_Saturator__ctx_type_7 &_ctx){
   effects_Saturator_setCoeff(_ctx,0x10000 /* 1.000000 */);
   effects_Saturator_setThreshold(_ctx,0xcccc /* 0.800000 */);
}

typedef struct effects_Saturator__ctx_type_8 {
   effects_Saturator__ctx_type_7 _inst15c;
} effects_Saturator__ctx_type_8;

typedef effects_Saturator__ctx_type_8 effects_Saturator_dummy_type;

static_inline void effects_Saturator__ctx_type_8_init(effects_Saturator__ctx_type_8 &_output_){
   effects_Saturator__ctx_type_8 &_ctx = _output_;
   effects_Saturator__ctx_type_7_init(_ctx._inst15c);
   
   return ;
}

static_inline void effects_Saturator_dummy_init(effects_Saturator__ctx_type_8 &_output_){
   effects_Saturator__ctx_type_8_init(_output_);
   return ;
}

static_inline void effects_Saturator_dummy(effects_Saturator__ctx_type_8 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_Saturator_process_bufferTo(_ctx._inst15c,0,buff,buff);
}

typedef struct effects_SVF__ctx_type_0 {
   fix16_t z2;
   fix16_t z1;
   fix16_t targetFreq;
   int sel;
   fix16_t rsize;
   fix16_t q;
   fix16_t inv_den;
   fix16_t g_table[1024];
   fix16_t gRatio;
   fix16_t g;
   fix16_t fs_nyquist;
   fix16_t fs;
   fix16_t freq;
   effects_Util__ctx_type_5 _inst955;
   effects_Util__ctx_type_4 _inst173b;
   effects_Util__ctx_type_5 _inst1655;
   effects_Util__ctx_type_4 _inst103b;
   fix16_t R;
} effects_SVF__ctx_type_0;

typedef effects_SVF__ctx_type_0 effects_SVF_updateGTable_type;

void effects_SVF__ctx_type_0_init(effects_SVF__ctx_type_0 &_output_);

static_inline void effects_SVF_updateGTable_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

void effects_SVF_updateGTable(effects_SVF__ctx_type_0 &_ctx);

typedef effects_SVF__ctx_type_0 effects_SVF_updateG_type;

static_inline void effects_SVF_updateG_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

void effects_SVF_updateG(effects_SVF__ctx_type_0 &_ctx);

typedef effects_SVF__ctx_type_0 effects_SVF_updateCoeffs_type;

static_inline void effects_SVF_updateCoeffs_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_SVF_updateCoeffs(effects_SVF__ctx_type_0 &_ctx){
   _ctx.R = fix_div(0x10000 /* 1.000000 */,((0x0 /* 0.000000 */ + _ctx.q) << 1));
   _ctx.inv_den = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + fix_mul(_ctx.g,_ctx.g) + (fix_mul(_ctx.R,_ctx.g) << 1)));
}

typedef effects_SVF__ctx_type_0 effects_SVF_setFreq_type;

static_inline void effects_SVF_setFreq_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_SVF_setFreq(effects_SVF__ctx_type_0 &_ctx, fix16_t newFreq){
   _ctx.targetFreq = fix_clip(newFreq,0x0 /* 0.000000 */,_ctx.fs_nyquist);
   effects_SVF_updateG(_ctx);
   effects_SVF_updateCoeffs(_ctx);
}

typedef effects_SVF__ctx_type_0 effects_SVF_setQ_type;

static_inline void effects_SVF_setQ_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_SVF_setQ(effects_SVF__ctx_type_0 &_ctx, fix16_t newQ){
   if(newQ >= 0x0 /* 0.000000 */){
      _ctx.q = newQ;
   }
   effects_SVF_updateCoeffs(_ctx);
}

typedef effects_SVF__ctx_type_0 effects_SVF_setType_type;

static_inline void effects_SVF_setType_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_SVF_setType(effects_SVF__ctx_type_0 &_ctx, int newSel){
   _ctx.sel = int_clip(newSel,0,4);
};

typedef effects_SVF__ctx_type_0 effects_SVF_process_type;

static_inline void effects_SVF_process_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

fix16_t effects_SVF_process(effects_SVF__ctx_type_0 &_ctx, fix16_t input);

typedef effects_SVF__ctx_type_0 effects_SVF_process_bufferTo_type;

static_inline void effects_SVF_process_bufferTo_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

void effects_SVF_process_bufferTo(effects_SVF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effects_SVF__ctx_type_0 effects_SVF_setSamplerate_type;

static_inline void effects_SVF_setSamplerate_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

void effects_SVF_setSamplerate(effects_SVF__ctx_type_0 &_ctx, fix16_t newFs);

typedef effects_SVF__ctx_type_0 effects_SVF_default_type;

static_inline void effects_SVF_default_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effects_SVF_default(effects_SVF__ctx_type_0 &_ctx){
   _ctx.rsize = 0x4000000 /* 1024.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   _ctx.q = 0x1999 /* 0.100000 */;
   effects_SVF_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}

typedef struct effects_SVF__ctx_type_1 {
   effects_SVF__ctx_type_0 _inst1f;
} effects_SVF__ctx_type_1;

typedef effects_SVF__ctx_type_1 effects_SVF_dummy_type;

static_inline void effects_SVF__ctx_type_1_init(effects_SVF__ctx_type_1 &_output_){
   effects_SVF__ctx_type_1 &_ctx = _output_;
   effects_SVF__ctx_type_0_init(_ctx._inst1f);
   
   return ;
}

static_inline void effects_SVF_dummy_init(effects_SVF__ctx_type_1 &_output_){
   effects_SVF__ctx_type_1_init(_output_);
   return ;
}

static_inline void effects_SVF_dummy(effects_SVF__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effects_Buffer_buffer(buff);
   effects_SVF_process_bufferTo(_ctx._inst1f,0,buff,buff);
}



#endif // EFFECTS_H
