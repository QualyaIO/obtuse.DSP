
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "engine.h"

void ADSR__ctx_type_0_init(ADSR__ctx_type_0 &_output_){
   ADSR__ctx_type_0 _ctx;
   _ctx.target = 0x0 /* 0.000000 */;
   _ctx.state = 0;
   _ctx.scale = 0x0 /* 0.000000 */;
   _ctx.s = 0x0 /* 0.000000 */;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.r_rate = 0x0 /* 0.000000 */;
   _ctx.out = 0x0 /* 0.000000 */;
   _ctx.d_rate = 0x0 /* 0.000000 */;
   _ctx.a_rate = 0x0 /* 0.000000 */;
   Util__ctx_type_2_init(_ctx._inst955);
   Util__ctx_type_1_init(_ctx._inst251);
   ADSR_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t ADSR_process(ADSR__ctx_type_0 &_ctx, fix16_t gate){
   _ctx.out = (_ctx.out + fix_mul(fix_mul(0x106 /* 0.004000 */,_ctx.rate),(_ctx.target + (- _ctx.out))));
   uint8_t bgate;
   bgate = (gate > 0x0 /* 0.000000 */);
   if(_ctx.state == 0){
      if(Util_edge(_ctx._inst251,bgate)){
         _ctx.state = 1;
         _ctx.scale = fix_mul(0x3333 /* 0.200000 */,gate);
      }
      _ctx.rate = _ctx.r_rate;
      _ctx.target = 0x0 /* 0.000000 */;
   }
   if(_ctx.state == 1){
      if(bool_not(bgate)){
         _ctx.state = 0;
      }
      if(_ctx.out > 0x4000000 /* 1024.000000 */){
         _ctx.state = 2;
      }
      _ctx.rate = _ctx.a_rate;
      _ctx.target = 0x4cccccc /* 1228.800000 */;
   }
   if(_ctx.state == 2){
      if(bool_not(bgate)){
         _ctx.state = 0;
      }
      _ctx.rate = _ctx.d_rate;
      _ctx.target = (_ctx.s << 10);
   }
   return fix_mul(Util_smooth(_ctx._inst955,_ctx.scale),fix_clip((_ctx.out >> 10),0x0 /* 0.000000 */,0x10000 /* 1.000000 */));
}

void ADSR_config(ADSR__ctx_type_0 &_ctx, fix16_t newA, fix16_t newD, fix16_t newS, fix16_t newR){
   fix16_t a;
   a = fix_clip(newA,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   fix16_t d;
   d = fix_clip(newD,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.s = fix_clip(newS,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   fix16_t r;
   r = fix_clip(newR,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.a_rate = fix_div(0x10000 /* 1.000000 */,(0x28f /* 0.010000 */ + fix_mul(0x640000 /* 100.000000 */,a)));
   _ctx.d_rate = fix_div(0x10000 /* 1.000000 */,(0x28f /* 0.010000 */ + fix_mul(0x640000 /* 100.000000 */,d)));
   _ctx.r_rate = fix_div(0x10000 /* 1.000000 */,(0x28f /* 0.010000 */ + fix_mul(0x640000 /* 100.000000 */,r)));
}

void OSC__ctx_type_2_init(OSC__ctx_type_2 &_output_){
   OSC__ctx_type_2 _ctx;
   _ctx.wavetable = 0;
   _ctx.stepRatio = 0x0 /* 0.000000 */;
   _ctx.step = 0x0 /* 0.000000 */;
   _ctx.phase_base = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   OSC_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t OSC_process(OSC__ctx_type_2 &_ctx){
   _ctx.phase = (_ctx.phase + _ctx.step);
   fix16_t size;
   size = int_to_fix(OSC_getSize(_ctx));
   if(_ctx.phase > size){
      _ctx.phase = (_ctx.phase + (- size));
   }
   return OSC_sin_wave(0,fix_to_int((_ctx.phase + _ctx.phase_base)));
}

void OSC_setSamplerate(OSC__ctx_type_2 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.stepRatio = fix_div(int_to_fix(OSC_getSize(_ctx)),_ctx.fs);
   }
   OSC_updateStep(_ctx);
}

void Engine__ctx_type_0_init(Engine__ctx_type_0 &_output_){
   Engine__ctx_type_0 _ctx;
   ADSR__ctx_type_0_init(_ctx.modulatoradsr);
   _ctx.modulatorRatio = 0x0 /* 0.000000 */;
   OSC__ctx_type_2_init(_ctx.modulator);
   _ctx.gate = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   ADSR__ctx_type_0_init(_ctx.carrieradsr);
   _ctx.carrier_half_phase = 0x0 /* 0.000000 */;
   _ctx.carrierRatio = 0x0 /* 0.000000 */;
   OSC__ctx_type_2_init(_ctx.carrier);
   Engine_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t Engine_process(Engine__ctx_type_0 &_ctx){
   fix16_t modulator_env;
   modulator_env = ADSR_process(_ctx.modulatoradsr,_ctx.gate);
   fix16_t carrier_env;
   carrier_env = ADSR_process(_ctx.carrieradsr,_ctx.gate);
   fix16_t modulator_val;
   if(modulator_env > 0x0 /* 0.000000 */){
      modulator_val = fix_mul(modulator_env,(0x10000 /* 1.000000 */ + OSC_process(_ctx.modulator)));
   }
   fix16_t carrier_val;
   if(carrier_env > 0x0 /* 0.000000 */){
      carrier_val = fix_mul(modulator_env,(0x10000 /* 1.000000 */ + OSC_process(_ctx.carrier)));
   }
   fix16_t carrier_phase;
   carrier_phase = fix_mul(_ctx.carrier_half_phase,modulator_val);
   OSC_setPhase(_ctx.carrier,carrier_phase);
   fix16_t c;
   c = OSC_process(_ctx.carrier);
   return c;
}

void Engine_default(Engine__ctx_type_0 &_ctx){
   Engine_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   Engine_setCarrierRatio(_ctx,0x10000 /* 1.000000 */);
   Engine_setModulatorRatio(_ctx,0x20000 /* 2.000000 */);
   Engine_setModulatorLevel(_ctx,0x1999 /* 0.100000 */);
   Engine_setFrequency(_ctx,0x70a3 /* 0.440000 */);
}


