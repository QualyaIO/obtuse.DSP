
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef EFFECTSXL_H
#define EFFECTSXL_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "effectsXL.tables.h"

static_inline void effectsXL_Buffer_buffer(fix16_t (&oBuff)[128]){
}

void effectsXL_Buffer_buffer_large(fix16_t (&oBuff)[16384]);

typedef struct effectsXL_CombFB__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer[16384];
} effectsXL_CombFB__ctx_type_0;

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_process_type;

void effectsXL_CombFB__ctx_type_0_init(effectsXL_CombFB__ctx_type_0 &_output_);

static_inline void effectsXL_CombFB_process_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

fix16_t effectsXL_CombFB_process(effectsXL_CombFB__ctx_type_0 &_ctx, fix16_t sample);

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_process_bufferTo_type;

static_inline void effectsXL_CombFB_process_bufferTo_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_CombFB_process_bufferTo(effectsXL_CombFB__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_setDecay_type;

static_inline void effectsXL_CombFB_setDecay_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_setDecay(effectsXL_CombFB__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_getMaxDelay_type;

static_inline void effectsXL_CombFB_getMaxDelay_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline int effectsXL_CombFB_getMaxDelay(effectsXL_CombFB__ctx_type_0 &_ctx){
   return 16384;
};

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_getMaxDelayms_type;

static_inline void effectsXL_CombFB_getMaxDelayms_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_CombFB_getMaxDelayms(effectsXL_CombFB__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x40000000 /* 16384.000000 */,_ctx.fs);
}

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_setDelay_type;

static_inline void effectsXL_CombFB_setDelay_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_setDelay(effectsXL_CombFB__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effectsXL_CombFB_getMaxDelay(_ctx));
   _ctx.pos = 0;
}

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_setDelayms_type;

static_inline void effectsXL_CombFB_setDelayms_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_setDelayms(effectsXL_CombFB__ctx_type_0 &_ctx, fix16_t delayms){
   effectsXL_CombFB_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_setSamplerate_type;

static_inline void effectsXL_CombFB_setSamplerate_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_setSamplerate(effectsXL_CombFB__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effectsXL_CombFB__ctx_type_0 effectsXL_CombFB_default_type;

static_inline void effectsXL_CombFB_default_init(effectsXL_CombFB__ctx_type_0 &_output_){
   effectsXL_CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_default(effectsXL_CombFB__ctx_type_0 &_ctx){
   effectsXL_Buffer_buffer_large(_ctx.buffer);
   effectsXL_CombFB_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effectsXL_CombFB_setDelayms(_ctx,0x320000 /* 50.000000 */);
   effectsXL_CombFB_setDecay(_ctx,0x8000 /* 0.500000 */);
}

typedef struct effectsXL_CombFB__ctx_type_1 {
   effectsXL_CombFB__ctx_type_0 _inst13c;
} effectsXL_CombFB__ctx_type_1;

typedef effectsXL_CombFB__ctx_type_1 effectsXL_CombFB_dummy_type;

static_inline void effectsXL_CombFB__ctx_type_1_init(effectsXL_CombFB__ctx_type_1 &_output_){
   effectsXL_CombFB__ctx_type_1 &_ctx = _output_;
   effectsXL_CombFB__ctx_type_0_init(_ctx._inst13c);
   
   return ;
}

static_inline void effectsXL_CombFB_dummy_init(effectsXL_CombFB__ctx_type_1 &_output_){
   effectsXL_CombFB__ctx_type_1_init(_output_);
   return ;
}

static_inline void effectsXL_CombFB_dummy(effectsXL_CombFB__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_CombFB_process_bufferTo(_ctx._inst13c,0,buff,buff);
}

typedef struct effectsXL_Allpass__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer_allpassed[16384];
   fix16_t buffer[16384];
} effectsXL_Allpass__ctx_type_0;

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_process_type;

void effectsXL_Allpass__ctx_type_0_init(effectsXL_Allpass__ctx_type_0 &_output_);

static_inline void effectsXL_Allpass_process_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

fix16_t effectsXL_Allpass_process(effectsXL_Allpass__ctx_type_0 &_ctx, fix16_t sample);

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_process_bufferTo_type;

static_inline void effectsXL_Allpass_process_bufferTo_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Allpass_process_bufferTo(effectsXL_Allpass__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_setDecay_type;

static_inline void effectsXL_Allpass_setDecay_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_Allpass_setDecay(effectsXL_Allpass__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + (_ctx.decay << 1)));
}

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_getMaxDelay_type;

static_inline void effectsXL_Allpass_getMaxDelay_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline int effectsXL_Allpass_getMaxDelay(effectsXL_Allpass__ctx_type_0 &_ctx){
   return 16384;
};

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_getMaxDelayms_type;

static_inline void effectsXL_Allpass_getMaxDelayms_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_Allpass_getMaxDelayms(effectsXL_Allpass__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x40000000 /* 16384.000000 */,_ctx.fs);
}

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_setDelay_type;

static_inline void effectsXL_Allpass_setDelay_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_Allpass_setDelay(effectsXL_Allpass__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effectsXL_Allpass_getMaxDelay(_ctx));
   _ctx.pos = 0;
}

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_setDelayms_type;

static_inline void effectsXL_Allpass_setDelayms_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_Allpass_setDelayms(effectsXL_Allpass__ctx_type_0 &_ctx, fix16_t delayms){
   effectsXL_Allpass_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_setSamplerate_type;

static_inline void effectsXL_Allpass_setSamplerate_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_Allpass_setSamplerate(effectsXL_Allpass__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effectsXL_Allpass__ctx_type_0 effectsXL_Allpass_default_type;

static_inline void effectsXL_Allpass_default_init(effectsXL_Allpass__ctx_type_0 &_output_){
   effectsXL_Allpass__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Allpass_default(effectsXL_Allpass__ctx_type_0 &_ctx);

typedef struct effectsXL_Allpass__ctx_type_1 {
   effectsXL_Allpass__ctx_type_0 _inst156;
} effectsXL_Allpass__ctx_type_1;

typedef effectsXL_Allpass__ctx_type_1 effectsXL_Allpass_dummy_type;

static_inline void effectsXL_Allpass__ctx_type_1_init(effectsXL_Allpass__ctx_type_1 &_output_){
   effectsXL_Allpass__ctx_type_1 &_ctx = _output_;
   effectsXL_Allpass__ctx_type_0_init(_ctx._inst156);
   
   return ;
}

static_inline void effectsXL_Allpass_dummy_init(effectsXL_Allpass__ctx_type_1 &_output_){
   effectsXL_Allpass__ctx_type_1_init(_output_);
   return ;
}

static_inline void effectsXL_Allpass_dummy(effectsXL_Allpass__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_Allpass_process_bufferTo(_ctx._inst156,0,buff,buff);
}

typedef struct effectsXL_Reverb__ctx_type_0 {
   fix16_t reverbtime;
   fix16_t fs;
   int comb3delay;
   effectsXL_CombFB__ctx_type_0 comb3;
   int comb2delay;
   effectsXL_CombFB__ctx_type_0 comb2;
   int comb1delay;
   effectsXL_CombFB__ctx_type_0 comb1;
   int comb0delay;
   effectsXL_CombFB__ctx_type_0 comb0;
   fix16_t buffer_c3[128];
   fix16_t buffer_c2[128];
   fix16_t buffer_c1[128];
   fix16_t buffer_c0[128];
   fix16_t buffer_a1[128];
   fix16_t buffer_a0[128];
   effectsXL_Allpass__ctx_type_0 allpass1;
   effectsXL_Allpass__ctx_type_0 allpass0;
} effectsXL_Reverb__ctx_type_0;

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_process_type;

void effectsXL_Reverb__ctx_type_0_init(effectsXL_Reverb__ctx_type_0 &_output_);

static_inline void effectsXL_Reverb_process_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_Reverb_process(effectsXL_Reverb__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t combs_filter;
   combs_filter = ((effectsXL_CombFB_process(_ctx.comb0,sample) + effectsXL_CombFB_process(_ctx.comb1,sample) + effectsXL_CombFB_process(_ctx.comb2,sample) + effectsXL_CombFB_process(_ctx.comb3,sample)) >> 2);
   return effectsXL_Allpass_process(_ctx.allpass1,effectsXL_Allpass_process(_ctx.allpass0,combs_filter));
}

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_process_bufferTo_type;

static_inline void effectsXL_Reverb_process_bufferTo_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Reverb_process_bufferTo(effectsXL_Reverb__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_setSamplerate_type;

static_inline void effectsXL_Reverb_setSamplerate_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Reverb_setSamplerate(effectsXL_Reverb__ctx_type_0 &_ctx, fix16_t newFs);

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_setReverbTime_type;

static_inline void effectsXL_Reverb_setReverbTime_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Reverb_setReverbTime(effectsXL_Reverb__ctx_type_0 &_ctx, fix16_t newReverbtime);

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_setDelayms_type;

static_inline void effectsXL_Reverb_setDelayms_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Reverb_setDelayms(effectsXL_Reverb__ctx_type_0 &_ctx, fix16_t delayms);

typedef effectsXL_Reverb__ctx_type_0 effectsXL_Reverb_default_type;

static_inline void effectsXL_Reverb_default_init(effectsXL_Reverb__ctx_type_0 &_output_){
   effectsXL_Reverb__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_Reverb_default(effectsXL_Reverb__ctx_type_0 &_ctx);

typedef struct effectsXL_Reverb__ctx_type_1 {
   effectsXL_Reverb__ctx_type_0 _inst1f2;
} effectsXL_Reverb__ctx_type_1;

typedef effectsXL_Reverb__ctx_type_1 effectsXL_Reverb_dummy_type;

static_inline void effectsXL_Reverb__ctx_type_1_init(effectsXL_Reverb__ctx_type_1 &_output_){
   effectsXL_Reverb__ctx_type_1 &_ctx = _output_;
   effectsXL_Reverb__ctx_type_0_init(_ctx._inst1f2);
   
   return ;
}

static_inline void effectsXL_Reverb_dummy_init(effectsXL_Reverb__ctx_type_1 &_output_){
   effectsXL_Reverb__ctx_type_1_init(_output_);
   return ;
}

static_inline void effectsXL_Reverb_dummy(effectsXL_Reverb__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_Reverb_process_bufferTo(_ctx._inst1f2,0,buff,buff);
}

static_inline fix16_t effectsXL_Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

static_inline fix16_t effectsXL_Util_tonesToCoeff(fix16_t semitones){
   fix16_t log_base;
   log_base = 0xb172 /* 0.693147 */;
   return fix_exp(fix_mul(fix_mul(0x1555 /* 0.083333 */,log_base),semitones));
}

typedef struct effectsXL_Util__ctx_type_2 {
   uint8_t pre;
} effectsXL_Util__ctx_type_2;

typedef effectsXL_Util__ctx_type_2 effectsXL_Util_edge_type;

static_inline void effectsXL_Util__ctx_type_2_init(effectsXL_Util__ctx_type_2 &_output_){
   effectsXL_Util__ctx_type_2 &_ctx = _output_;
   _ctx.pre = false;
   
   return ;
}

static_inline void effectsXL_Util_edge_init(effectsXL_Util__ctx_type_2 &_output_){
   effectsXL_Util__ctx_type_2_init(_output_);
   return ;
}

static_inline uint8_t effectsXL_Util_edge(effectsXL_Util__ctx_type_2 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline fix16_t effectsXL_Util_cubic_clipper(fix16_t x){
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

typedef struct effectsXL_Util__ctx_type_4 {
   fix16_t pre_x;
} effectsXL_Util__ctx_type_4;

typedef effectsXL_Util__ctx_type_4 effectsXL_Util_change_type;

static_inline void effectsXL_Util__ctx_type_4_init(effectsXL_Util__ctx_type_4 &_output_){
   effectsXL_Util__ctx_type_4 &_ctx = _output_;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   
   return ;
}

static_inline void effectsXL_Util_change_init(effectsXL_Util__ctx_type_4 &_output_){
   effectsXL_Util__ctx_type_4_init(_output_);
   return ;
}

static_inline uint8_t effectsXL_Util_change(effectsXL_Util__ctx_type_4 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

typedef struct effectsXL_Util__ctx_type_5 {
   fix16_t x;
} effectsXL_Util__ctx_type_5;

typedef effectsXL_Util__ctx_type_5 effectsXL_Util_smooth_type;

static_inline void effectsXL_Util__ctx_type_5_init(effectsXL_Util__ctx_type_5 &_output_){
   effectsXL_Util__ctx_type_5 &_ctx = _output_;
   _ctx.x = 0x0 /* 0.000000 */;
   
   return ;
}

static_inline void effectsXL_Util_smooth_init(effectsXL_Util__ctx_type_5 &_output_){
   effectsXL_Util__ctx_type_5_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_Util_smooth(effectsXL_Util__ctx_type_5 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t effectsXL_Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

typedef struct effectsXL_Ladder__ctx_type_0 {
   fix16_t p3;
   fix16_t p2;
   fix16_t p1;
   fix16_t p0;
} effectsXL_Ladder__ctx_type_0;

typedef effectsXL_Ladder__ctx_type_0 effectsXL_Ladder_heun_type;

void effectsXL_Ladder__ctx_type_0_init(effectsXL_Ladder__ctx_type_0 &_output_);

static_inline void effectsXL_Ladder_heun_init(effectsXL_Ladder__ctx_type_0 &_output_){
   effectsXL_Ladder__ctx_type_0_init(_output_);
   return ;
}

fix16_t effectsXL_Ladder_heun(effectsXL_Ladder__ctx_type_0 &_ctx, fix16_t input, fix16_t fh, fix16_t res);

typedef struct effectsXL_Ladder__ctx_type_1 {
   fix16_t p3;
   fix16_t p2;
   fix16_t p1;
   fix16_t p0;
} effectsXL_Ladder__ctx_type_1;

typedef effectsXL_Ladder__ctx_type_1 effectsXL_Ladder_euler_type;

void effectsXL_Ladder__ctx_type_1_init(effectsXL_Ladder__ctx_type_1 &_output_);

static_inline void effectsXL_Ladder_euler_init(effectsXL_Ladder__ctx_type_1 &_output_){
   effectsXL_Ladder__ctx_type_1_init(_output_);
   return ;
}

fix16_t effectsXL_Ladder_euler(effectsXL_Ladder__ctx_type_1 &_ctx, fix16_t input, fix16_t fh, fix16_t res);

typedef struct effectsXL_Ladder__ctx_type_2 {
   fix16_t tune_table[1024];
   fix16_t tuneRatio;
   fix16_t rsize;
   fix16_t res;
   uint8_t heun;
   effectsXL_Ladder__ctx_type_0 h;
   fix16_t fs_nyquist;
   fix16_t fs;
   fix16_t fh;
   effectsXL_Ladder__ctx_type_1 e;
   fix16_t cut;
   effectsXL_Util__ctx_type_4 _inst43b;
   effectsXL_Util__ctx_type_4 _inst13b;
} effectsXL_Ladder__ctx_type_2;

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_getTune_type;

void effectsXL_Ladder__ctx_type_2_init(effectsXL_Ladder__ctx_type_2 &_output_);

static_inline void effectsXL_Ladder_getTune_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effectsXL_Ladder_getTune(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t cut);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_process_euler_type;

static_inline void effectsXL_Ladder_process_euler_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effectsXL_Ladder_process_euler(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_process_heun_type;

static_inline void effectsXL_Ladder_process_heun_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

fix16_t effectsXL_Ladder_process_heun(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_process_type;

static_inline void effectsXL_Ladder_process_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_Ladder_process(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t input){
   if(_ctx.heun){
      return effectsXL_Ladder_process_heun(_ctx,input,_ctx.cut,_ctx.res);
   }
   else
   {
      return effectsXL_Ladder_process_euler(_ctx,input,_ctx.cut,_ctx.res);
   }
};

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_process_bufferTo_type;

static_inline void effectsXL_Ladder_process_bufferTo_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effectsXL_Ladder_process_bufferTo(effectsXL_Ladder__ctx_type_2 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_updateTune_type;

static_inline void effectsXL_Ladder_updateTune_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effectsXL_Ladder_updateTune(effectsXL_Ladder__ctx_type_2 &_ctx);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_setEstimationMethod_type;

static_inline void effectsXL_Ladder_setEstimationMethod_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effectsXL_Ladder_setEstimationMethod(effectsXL_Ladder__ctx_type_2 &_ctx, int method){
   if(method == 1){
      _ctx.heun = true;
   }
   else
   {
      _ctx.heun = false;
   }
};

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_setCutOff_type;

static_inline void effectsXL_Ladder_setCutOff_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effectsXL_Ladder_setCutOff(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t newCut){
   _ctx.cut = fix_clip(newCut,0x0 /* 0.000000 */,_ctx.fs_nyquist);
};

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_setResonance_type;

static_inline void effectsXL_Ladder_setResonance_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effectsXL_Ladder_setResonance(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t newRes){
   _ctx.res = newRes;
};

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_setSamplerate_type;

static_inline void effectsXL_Ladder_setSamplerate_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

void effectsXL_Ladder_setSamplerate(effectsXL_Ladder__ctx_type_2 &_ctx, fix16_t newFs);

typedef effectsXL_Ladder__ctx_type_2 effectsXL_Ladder_default_type;

static_inline void effectsXL_Ladder_default_init(effectsXL_Ladder__ctx_type_2 &_output_){
   effectsXL_Ladder__ctx_type_2_init(_output_);
   return ;
}

static_inline void effectsXL_Ladder_default(effectsXL_Ladder__ctx_type_2 &_ctx){
   _ctx.rsize = 0x4000000 /* 1024.000000 */;
   effectsXL_Ladder_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effectsXL_Ladder_setEstimationMethod(_ctx,0);
}

typedef struct effectsXL_Ladder__ctx_type_3 {
   effectsXL_Ladder__ctx_type_2 _inst163;
} effectsXL_Ladder__ctx_type_3;

typedef effectsXL_Ladder__ctx_type_3 effectsXL_Ladder_dummy_type;

static_inline void effectsXL_Ladder__ctx_type_3_init(effectsXL_Ladder__ctx_type_3 &_output_){
   effectsXL_Ladder__ctx_type_3 &_ctx = _output_;
   effectsXL_Ladder__ctx_type_2_init(_ctx._inst163);
   
   return ;
}

static_inline void effectsXL_Ladder_dummy_init(effectsXL_Ladder__ctx_type_3 &_output_){
   effectsXL_Ladder__ctx_type_3_init(_output_);
   return ;
}

static_inline void effectsXL_Ladder_dummy(effectsXL_Ladder__ctx_type_3 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_Ladder_process_bufferTo(_ctx._inst163,0,buff,buff);
}

typedef struct effectsXL_CombFF__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer[16384];
} effectsXL_CombFF__ctx_type_0;

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_process_type;

void effectsXL_CombFF__ctx_type_0_init(effectsXL_CombFF__ctx_type_0 &_output_);

static_inline void effectsXL_CombFF_process_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

fix16_t effectsXL_CombFF_process(effectsXL_CombFF__ctx_type_0 &_ctx, fix16_t sample);

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_process_bufferTo_type;

static_inline void effectsXL_CombFF_process_bufferTo_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_CombFF_process_bufferTo(effectsXL_CombFF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_setDecay_type;

static_inline void effectsXL_CombFF_setDecay_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_setDecay(effectsXL_CombFF__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_getMaxDelay_type;

static_inline void effectsXL_CombFF_getMaxDelay_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline int effectsXL_CombFF_getMaxDelay(effectsXL_CombFF__ctx_type_0 &_ctx){
   return 16384;
};

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_getMaxDelayms_type;

static_inline void effectsXL_CombFF_getMaxDelayms_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t effectsXL_CombFF_getMaxDelayms(effectsXL_CombFF__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x40000000 /* 16384.000000 */,_ctx.fs);
}

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_setDelay_type;

static_inline void effectsXL_CombFF_setDelay_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_setDelay(effectsXL_CombFF__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,1,effectsXL_CombFF_getMaxDelay(_ctx));
   _ctx.pos = 0;
}

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_setDelayms_type;

static_inline void effectsXL_CombFF_setDelayms_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_setDelayms(effectsXL_CombFF__ctx_type_0 &_ctx, fix16_t delayms){
   effectsXL_CombFF_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_setSamplerate_type;

static_inline void effectsXL_CombFF_setSamplerate_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_setSamplerate(effectsXL_CombFF__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef effectsXL_CombFF__ctx_type_0 effectsXL_CombFF_default_type;

static_inline void effectsXL_CombFF_default_init(effectsXL_CombFF__ctx_type_0 &_output_){
   effectsXL_CombFF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_default(effectsXL_CombFF__ctx_type_0 &_ctx){
   effectsXL_Buffer_buffer_large(_ctx.buffer);
   effectsXL_CombFF_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effectsXL_CombFF_setDelayms(_ctx,0x320000 /* 50.000000 */);
   effectsXL_CombFF_setDecay(_ctx,0x8000 /* 0.500000 */);
}

typedef struct effectsXL_CombFF__ctx_type_1 {
   effectsXL_CombFF__ctx_type_0 _inst115;
} effectsXL_CombFF__ctx_type_1;

typedef effectsXL_CombFF__ctx_type_1 effectsXL_CombFF_dummy_type;

static_inline void effectsXL_CombFF__ctx_type_1_init(effectsXL_CombFF__ctx_type_1 &_output_){
   effectsXL_CombFF__ctx_type_1 &_ctx = _output_;
   effectsXL_CombFF__ctx_type_0_init(_ctx._inst115);
   
   return ;
}

static_inline void effectsXL_CombFF_dummy_init(effectsXL_CombFF__ctx_type_1 &_output_){
   effectsXL_CombFF__ctx_type_1_init(_output_);
   return ;
}

static_inline void effectsXL_CombFF_dummy(effectsXL_CombFF__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_CombFF_process_bufferTo(_ctx._inst115,0,buff,buff);
}

static_inline fix16_t effectsXL_Saturator_tanh_table_raw_c0(int index){
   return effectsXL_Saturator_tanh_table_c0[index];
};

static_inline fix16_t effectsXL_Saturator_tanh_table_raw_c1(int index){
   return effectsXL_Saturator_tanh_table_c1[index];
};

static_inline fix16_t effectsXL_Saturator_tanh_table_raw_c2(int index){
   return effectsXL_Saturator_tanh_table_c2[index];
};

static_inline fix16_t effectsXL_Saturator_tanh_table(fix16_t x){
   int index;
   index = int_clip(fix_to_int(fix_mul(0x3fe000 /* 63.875000 */,(0x40000 /* 4.000000 */ + x))),0,511);
   return (fix_wrap_array(effectsXL_Saturator_tanh_table_c0)[index] + fix_mul(x,(fix_wrap_array(effectsXL_Saturator_tanh_table_c1)[index] + fix_mul(x,fix_wrap_array(effectsXL_Saturator_tanh_table_c2)[index]))));
}

static_inline fix16_t effectsXL_Saturator_getMinCoeff(){
   return -0x3e80000 /* -1000.000000 */;
};

static_inline fix16_t effectsXL_Saturator_getMaxCoeff(){
   return 0x3e80000 /* 1000.000000 */;
};

typedef struct effectsXL_Saturator__ctx_type_6 {
   fix16_t threshopp;
   fix16_t threshinv;
   fix16_t thresh;
   fix16_t coeff;
} effectsXL_Saturator__ctx_type_6;

typedef effectsXL_Saturator__ctx_type_6 effectsXL_Saturator_process_type;

void effectsXL_Saturator__ctx_type_6_init(effectsXL_Saturator__ctx_type_6 &_output_);

static_inline void effectsXL_Saturator_process_init(effectsXL_Saturator__ctx_type_6 &_output_){
   effectsXL_Saturator__ctx_type_6_init(_output_);
   return ;
}

fix16_t effectsXL_Saturator_process(effectsXL_Saturator__ctx_type_6 &_ctx, fix16_t x);

typedef effectsXL_Saturator__ctx_type_6 effectsXL_Saturator_process_bufferTo_type;

static_inline void effectsXL_Saturator_process_bufferTo_init(effectsXL_Saturator__ctx_type_6 &_output_){
   effectsXL_Saturator__ctx_type_6_init(_output_);
   return ;
}

void effectsXL_Saturator_process_bufferTo(effectsXL_Saturator__ctx_type_6 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_Saturator__ctx_type_6 effectsXL_Saturator_setThreshold_type;

static_inline void effectsXL_Saturator_setThreshold_init(effectsXL_Saturator__ctx_type_6 &_output_){
   effectsXL_Saturator__ctx_type_6_init(_output_);
   return ;
}

static_inline void effectsXL_Saturator_setThreshold(effectsXL_Saturator__ctx_type_6 &_ctx, fix16_t t){
   _ctx.thresh = fix_clip(t,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.threshopp = (0x10000 /* 1.000000 */ + (- _ctx.thresh));
   if(_ctx.thresh < 0x10000 /* 1.000000 */){
      _ctx.threshinv = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + (- _ctx.thresh)));
   }
}

typedef effectsXL_Saturator__ctx_type_6 effectsXL_Saturator_setCoeff_type;

static_inline void effectsXL_Saturator_setCoeff_init(effectsXL_Saturator__ctx_type_6 &_output_){
   effectsXL_Saturator__ctx_type_6_init(_output_);
   return ;
}

static_inline void effectsXL_Saturator_setCoeff(effectsXL_Saturator__ctx_type_6 &_ctx, fix16_t c){
   _ctx.coeff = fix_clip(c,-0x3e80000 /* -1000.000000 */,0x3e80000 /* 1000.000000 */);
};

typedef effectsXL_Saturator__ctx_type_6 effectsXL_Saturator_default_type;

static_inline void effectsXL_Saturator_default_init(effectsXL_Saturator__ctx_type_6 &_output_){
   effectsXL_Saturator__ctx_type_6_init(_output_);
   return ;
}

static_inline void effectsXL_Saturator_default(effectsXL_Saturator__ctx_type_6 &_ctx){
   effectsXL_Saturator_setCoeff(_ctx,0x10000 /* 1.000000 */);
   effectsXL_Saturator_setThreshold(_ctx,0xcccc /* 0.800000 */);
}

typedef struct effectsXL_Saturator__ctx_type_7 {
   effectsXL_Saturator__ctx_type_6 _inst15c;
} effectsXL_Saturator__ctx_type_7;

typedef effectsXL_Saturator__ctx_type_7 effectsXL_Saturator_dummy_type;

static_inline void effectsXL_Saturator__ctx_type_7_init(effectsXL_Saturator__ctx_type_7 &_output_){
   effectsXL_Saturator__ctx_type_7 &_ctx = _output_;
   effectsXL_Saturator__ctx_type_6_init(_ctx._inst15c);
   
   return ;
}

static_inline void effectsXL_Saturator_dummy_init(effectsXL_Saturator__ctx_type_7 &_output_){
   effectsXL_Saturator__ctx_type_7_init(_output_);
   return ;
}

static_inline void effectsXL_Saturator_dummy(effectsXL_Saturator__ctx_type_7 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_Saturator_process_bufferTo(_ctx._inst15c,0,buff,buff);
}

typedef struct effectsXL_SVF__ctx_type_0 {
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
   effectsXL_Util__ctx_type_5 _inst955;
   effectsXL_Util__ctx_type_4 _inst173b;
   effectsXL_Util__ctx_type_5 _inst1655;
   effectsXL_Util__ctx_type_4 _inst103b;
   fix16_t R;
} effectsXL_SVF__ctx_type_0;

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_updateGTable_type;

void effectsXL_SVF__ctx_type_0_init(effectsXL_SVF__ctx_type_0 &_output_);

static_inline void effectsXL_SVF_updateGTable_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_SVF_updateGTable(effectsXL_SVF__ctx_type_0 &_ctx);

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_updateG_type;

static_inline void effectsXL_SVF_updateG_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_SVF_updateG(effectsXL_SVF__ctx_type_0 &_ctx);

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_updateCoeffs_type;

static_inline void effectsXL_SVF_updateCoeffs_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_updateCoeffs(effectsXL_SVF__ctx_type_0 &_ctx){
   _ctx.R = fix_div(0x10000 /* 1.000000 */,((0x0 /* 0.000000 */ + _ctx.q) << 1));
   _ctx.inv_den = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + fix_mul(_ctx.g,_ctx.g) + (fix_mul(_ctx.R,_ctx.g) << 1)));
}

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_setFreq_type;

static_inline void effectsXL_SVF_setFreq_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_setFreq(effectsXL_SVF__ctx_type_0 &_ctx, fix16_t newFreq){
   _ctx.targetFreq = fix_clip(newFreq,0x0 /* 0.000000 */,_ctx.fs_nyquist);
   effectsXL_SVF_updateG(_ctx);
   effectsXL_SVF_updateCoeffs(_ctx);
}

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_setQ_type;

static_inline void effectsXL_SVF_setQ_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_setQ(effectsXL_SVF__ctx_type_0 &_ctx, fix16_t newQ){
   if(newQ >= 0x0 /* 0.000000 */){
      _ctx.q = newQ;
   }
   effectsXL_SVF_updateCoeffs(_ctx);
}

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_setType_type;

static_inline void effectsXL_SVF_setType_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_setType(effectsXL_SVF__ctx_type_0 &_ctx, int newSel){
   _ctx.sel = int_clip(newSel,0,4);
};

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_process_type;

static_inline void effectsXL_SVF_process_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

fix16_t effectsXL_SVF_process(effectsXL_SVF__ctx_type_0 &_ctx, fix16_t input);

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_process_bufferTo_type;

static_inline void effectsXL_SVF_process_bufferTo_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_SVF_process_bufferTo(effectsXL_SVF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]);

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_setSamplerate_type;

static_inline void effectsXL_SVF_setSamplerate_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

void effectsXL_SVF_setSamplerate(effectsXL_SVF__ctx_type_0 &_ctx, fix16_t newFs);

typedef effectsXL_SVF__ctx_type_0 effectsXL_SVF_default_type;

static_inline void effectsXL_SVF_default_init(effectsXL_SVF__ctx_type_0 &_output_){
   effectsXL_SVF__ctx_type_0_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_default(effectsXL_SVF__ctx_type_0 &_ctx){
   _ctx.rsize = 0x4000000 /* 1024.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   _ctx.q = 0x1999 /* 0.100000 */;
   effectsXL_SVF_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}

typedef struct effectsXL_SVF__ctx_type_1 {
   effectsXL_SVF__ctx_type_0 _inst1f;
} effectsXL_SVF__ctx_type_1;

typedef effectsXL_SVF__ctx_type_1 effectsXL_SVF_dummy_type;

static_inline void effectsXL_SVF__ctx_type_1_init(effectsXL_SVF__ctx_type_1 &_output_){
   effectsXL_SVF__ctx_type_1 &_ctx = _output_;
   effectsXL_SVF__ctx_type_0_init(_ctx._inst1f);
   
   return ;
}

static_inline void effectsXL_SVF_dummy_init(effectsXL_SVF__ctx_type_1 &_output_){
   effectsXL_SVF__ctx_type_1_init(_output_);
   return ;
}

static_inline void effectsXL_SVF_dummy(effectsXL_SVF__ctx_type_1 &_ctx){
   fix16_t buff[128];
   effectsXL_Buffer_buffer(buff);
   effectsXL_SVF_process_bufferTo(_ctx._inst1f,0,buff,buff);
}



#endif // EFFECTSXL_H
