
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "effects.h"

void effects_Buffer_buffer_large(fix16_t (&oBuff)[2048]){
   int i;
   i = 0;
   while(i < 2048){
      oBuff[i] = 0x0 /* 0.000000 */;
      i = (1 + i);
   }
}

void effects_CombFB__ctx_type_0_init(effects_CombFB__ctx_type_0 &_output_){
   effects_CombFB__ctx_type_0 &_ctx = _output_;
   _ctx.scale = 0x0 /* 0.000000 */;
   _ctx.pos = 0;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.delay = 0;
   _ctx.decay = 0x0 /* 0.000000 */;
   ;
   effects_CombFB_default(_ctx);
   
   return ;
}

fix16_t effects_CombFB_process(effects_CombFB__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t out;
   out = (sample + fix_mul(_ctx.decay,_ctx.buffer[_ctx.pos]));
   _ctx.buffer[_ctx.pos] = out;
   _ctx.pos = (1 + _ctx.pos);
   _ctx.pos = (_ctx.pos % _ctx.delay);
   return fix_mul(_ctx.scale,out);
}

void effects_CombFB_process_bufferTo(effects_CombFB__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t out;
   int i;
   i = 0;
   while(i < nb){
      out = (input[i] + fix_mul(_ctx.decay,_ctx.buffer[_ctx.pos]));
      _ctx.buffer[_ctx.pos] = out;
      oBuffer[i] = fix_mul(_ctx.scale,out);
      _ctx.pos = (1 + _ctx.pos);
      _ctx.pos = (_ctx.pos % _ctx.delay);
      i = (1 + i);
   }
}

void effects_Allpass__ctx_type_0_init(effects_Allpass__ctx_type_0 &_output_){
   effects_Allpass__ctx_type_0 &_ctx = _output_;
   _ctx.scale = 0x0 /* 0.000000 */;
   _ctx.pos = 0;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.delay = 0;
   _ctx.decay = 0x0 /* 0.000000 */;
   ;
   ;
   effects_Allpass_default(_ctx);
   
   return ;
}

fix16_t effects_Allpass_process(effects_Allpass__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t out;
   out = (_ctx.buffer[_ctx.pos] + fix_mul(_ctx.decay,(sample + (- _ctx.buffer_allpassed[_ctx.pos]))));
   _ctx.buffer[_ctx.pos] = sample;
   _ctx.buffer_allpassed[_ctx.pos] = out;
   _ctx.pos = (1 + _ctx.pos);
   _ctx.pos = (_ctx.pos % _ctx.delay);
   return fix_mul(_ctx.scale,out);
}

void effects_Allpass_process_bufferTo(effects_Allpass__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t out;
   int i;
   i = 0;
   while(i < nb){
      out = (_ctx.buffer[_ctx.pos] + fix_mul(_ctx.decay,(input[i] + (- _ctx.buffer_allpassed[_ctx.pos]))));
      _ctx.buffer[_ctx.pos] = input[i];
      _ctx.buffer_allpassed[_ctx.pos] = out;
      oBuffer[i] = fix_mul(_ctx.scale,out);
      _ctx.pos = (1 + _ctx.pos);
      _ctx.pos = (_ctx.pos % _ctx.delay);
      i = (1 + i);
   }
}

void effects_Allpass_default(effects_Allpass__ctx_type_0 &_ctx){
   effects_Buffer_buffer_large(_ctx.buffer);
   effects_Buffer_buffer_large(_ctx.buffer_allpassed);
   effects_Allpass_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   effects_Allpass_setDelayms(_ctx,0x320000 /* 50.000000 */);
   effects_Allpass_setDecay(_ctx,0x8000 /* 0.500000 */);
}

void effects_Reverb__ctx_type_0_init(effects_Reverb__ctx_type_0 &_output_){
   effects_Reverb__ctx_type_0 &_ctx = _output_;
   _ctx.reverbtime = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.comb3delay = 0;
   effects_CombFB__ctx_type_0_init(_ctx.comb3);
   _ctx.comb2delay = 0;
   effects_CombFB__ctx_type_0_init(_ctx.comb2);
   _ctx.comb1delay = 0;
   effects_CombFB__ctx_type_0_init(_ctx.comb1);
   _ctx.comb0delay = 0;
   effects_CombFB__ctx_type_0_init(_ctx.comb0);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_c3);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_c2);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_c1);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_c0);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_a1);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_a0);
   effects_Allpass__ctx_type_0_init(_ctx.allpass1);
   effects_Allpass__ctx_type_0_init(_ctx.allpass0);
   effects_Reverb_default(_ctx);
   
   return ;
}

void effects_Reverb_process_bufferTo(effects_Reverb__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   effects_CombFB_process_bufferTo(_ctx.comb0,nb,input,_ctx.buffer_c0);
   effects_CombFB_process_bufferTo(_ctx.comb1,nb,input,_ctx.buffer_c1);
   effects_CombFB_process_bufferTo(_ctx.comb2,nb,input,_ctx.buffer_c2);
   effects_CombFB_process_bufferTo(_ctx.comb3,nb,input,_ctx.buffer_c3);
   int i;
   i = 0;
   while(i < nb){
      oBuffer[i] = ((_ctx.buffer_c0[i] + _ctx.buffer_c1[i] + _ctx.buffer_c2[i] + _ctx.buffer_c3[i]) >> 2);
      i = (1 + i);
   }
   effects_Allpass_process_bufferTo(_ctx.allpass0,nb,oBuffer,oBuffer);
   effects_Allpass_process_bufferTo(_ctx.allpass1,nb,oBuffer,oBuffer);
}

void effects_Reverb_setSamplerate(effects_Reverb__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   else
   {
      _ctx.fs = 0x2c1999 /* 44.100000 */;
   }
   effects_CombFB_setSamplerate(_ctx.comb0,newFs);
   effects_CombFB_setSamplerate(_ctx.comb1,newFs);
   effects_CombFB_setSamplerate(_ctx.comb2,newFs);
   effects_CombFB_setSamplerate(_ctx.comb3,newFs);
   effects_Allpass_setSamplerate(_ctx.allpass0,newFs);
   effects_Allpass_setSamplerate(_ctx.allpass1,newFs);
}

void effects_Reverb_setReverbTime(effects_Reverb__ctx_type_0 &_ctx, fix16_t newReverbtime){
   if(newReverbtime > 0x0 /* 0.000000 */){
      _ctx.reverbtime = newReverbtime;
      fix16_t log_base;
      log_base = 0x24d76 /* 2.302585 */;
      fix16_t comb0decay;
      comb0decay = fix_exp(fix_div(fix_mul(fix_mul(-0xc4 /* -0.003000 */,log_base),int_to_fix(_ctx.comb0delay)),fix_mul(_ctx.fs,_ctx.reverbtime)));
      fix16_t comb1decay;
      comb1decay = fix_exp(fix_div(fix_mul(fix_mul(-0xc4 /* -0.003000 */,log_base),int_to_fix(_ctx.comb1delay)),fix_mul(_ctx.fs,_ctx.reverbtime)));
      fix16_t comb2decay;
      comb2decay = fix_exp(fix_div(fix_mul(fix_mul(-0xc4 /* -0.003000 */,log_base),int_to_fix(_ctx.comb2delay)),fix_mul(_ctx.fs,_ctx.reverbtime)));
      fix16_t comb3decay;
      comb3decay = fix_exp(fix_div(fix_mul(fix_mul(-0xc4 /* -0.003000 */,log_base),int_to_fix(_ctx.comb3delay)),fix_mul(_ctx.fs,_ctx.reverbtime)));
      effects_CombFB_setDecay(_ctx.comb0,comb0decay);
      effects_CombFB_setDecay(_ctx.comb1,comb1decay);
      effects_CombFB_setDecay(_ctx.comb2,comb2decay);
      effects_CombFB_setDecay(_ctx.comb3,comb3decay);
   }
}

void effects_Reverb_setDelayms(effects_Reverb__ctx_type_0 &_ctx, fix16_t delayms){
   int delay;
   delay = fix_to_int(fix_mul(_ctx.fs,delayms));
   _ctx.comb3delay = int_clip(delay,1,effects_CombFB_getMaxDelay(_ctx.comb3));
   _ctx.comb0delay = int_clip(((-345) + _ctx.comb3delay),1,effects_CombFB_getMaxDelay(_ctx.comb0));
   _ctx.comb1delay = int_clip(((-222) + _ctx.comb3delay),1,effects_CombFB_getMaxDelay(_ctx.comb1));
   _ctx.comb2delay = int_clip(((-112) + _ctx.comb3delay),1,effects_CombFB_getMaxDelay(_ctx.comb2));
   effects_CombFB_setDelay(_ctx.comb0,_ctx.comb0delay);
   effects_CombFB_setDelay(_ctx.comb1,_ctx.comb1delay);
   effects_CombFB_setDelay(_ctx.comb2,_ctx.comb2delay);
   effects_CombFB_setDelay(_ctx.comb3,_ctx.comb3delay);
   effects_Reverb_setReverbTime(_ctx,_ctx.reverbtime);
}

void effects_Reverb_default(effects_Reverb__ctx_type_0 &_ctx){
   effects_Buffer_buffer(_ctx.buffer_c0);
   effects_Buffer_buffer(_ctx.buffer_c1);
   effects_Buffer_buffer(_ctx.buffer_c2);
   effects_Buffer_buffer(_ctx.buffer_c3);
   effects_Buffer_buffer(_ctx.buffer_a0);
   effects_Buffer_buffer(_ctx.buffer_a1);
   effects_Reverb_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   _ctx.reverbtime = 0xa666 /* 0.650000 */;
   effects_Reverb_setDelayms(_ctx,0x197700 /* 25.464853 */);
   effects_Allpass_setDecay(_ctx.allpass0,0xb333 /* 0.700000 */);
   effects_Allpass_setDecay(_ctx.allpass1,0xb333 /* 0.700000 */);
   effects_Allpass_setDelay(_ctx.allpass0,125);
   effects_Allpass_setDelay(_ctx.allpass1,42);
}

void effects_Ladder__ctx_type_0_init(effects_Ladder__ctx_type_0 &_output_){
   effects_Ladder__ctx_type_0 &_ctx = _output_;
   _ctx.p3 = 0x0 /* 0.000000 */;
   _ctx.p2 = 0x0 /* 0.000000 */;
   _ctx.p1 = 0x0 /* 0.000000 */;
   _ctx.p0 = 0x0 /* 0.000000 */;
   
   return ;
}

fix16_t effects_Ladder_heun(effects_Ladder__ctx_type_0 &_ctx, fix16_t input, fix16_t fh, fix16_t res){
   fix16_t wt0;
   wt0 = effects_Util_cubic_clipper((input + (- (fix_mul(_ctx.p3,res) << 2))));
   fix16_t wt1;
   wt1 = effects_Util_cubic_clipper(_ctx.p0);
   fix16_t dpt0;
   dpt0 = fix_mul(fh,(wt0 + (- wt1)));
   fix16_t wt3;
   wt3 = effects_Util_cubic_clipper(_ctx.p1);
   fix16_t dpt1;
   dpt1 = fix_mul(fh,(wt1 + (- wt3)));
   fix16_t wt5;
   wt5 = effects_Util_cubic_clipper(_ctx.p2);
   fix16_t dpt2;
   dpt2 = fix_mul(fh,(wt3 + (- wt5)));
   fix16_t wt7;
   wt7 = effects_Util_cubic_clipper(_ctx.p3);
   fix16_t dpt3;
   dpt3 = fix_mul(fh,(wt5 + (- wt7)));
   fix16_t pt0;
   pt0 = (_ctx.p0 + dpt0);
   fix16_t pt1;
   pt1 = (_ctx.p1 + dpt1);
   fix16_t pt2;
   pt2 = (_ctx.p2 + dpt2);
   fix16_t pt3;
   pt3 = (_ctx.p3 + dpt3);
   fix16_t w0;
   w0 = effects_Util_cubic_clipper((input + (- (fix_mul(pt3,res) << 2))));
   fix16_t w1;
   w1 = effects_Util_cubic_clipper(pt0);
   fix16_t dp0;
   dp0 = fix_mul(fh,(w0 + (- w1)));
   fix16_t w3;
   w3 = effects_Util_cubic_clipper(pt1);
   fix16_t dp1;
   dp1 = fix_mul(fh,(w1 + (- w3)));
   fix16_t w5;
   w5 = effects_Util_cubic_clipper(pt2);
   fix16_t dp2;
   dp2 = fix_mul(fh,(w3 + (- w5)));
   fix16_t w7;
   w7 = effects_Util_cubic_clipper(pt3);
   fix16_t dp3;
   dp3 = fix_mul(fh,(w5 + (- w7)));
   _ctx.p0 = (_ctx.p0 + ((dp0 + dpt0) >> 1));
   _ctx.p1 = (_ctx.p1 + ((dp1 + dpt1) >> 1));
   _ctx.p2 = (_ctx.p2 + ((dp2 + dpt2) >> 1));
   _ctx.p3 = (_ctx.p3 + ((dp3 + dpt3) >> 1));
   return _ctx.p3;
}

void effects_Ladder__ctx_type_1_init(effects_Ladder__ctx_type_1 &_output_){
   effects_Ladder__ctx_type_1 &_ctx = _output_;
   _ctx.p3 = 0x0 /* 0.000000 */;
   _ctx.p2 = 0x0 /* 0.000000 */;
   _ctx.p1 = 0x0 /* 0.000000 */;
   _ctx.p0 = 0x0 /* 0.000000 */;
   
   return ;
}

fix16_t effects_Ladder_euler(effects_Ladder__ctx_type_1 &_ctx, fix16_t input, fix16_t fh, fix16_t res){
   fix16_t w0;
   w0 = effects_Util_cubic_clipper((input + (- (fix_mul(_ctx.p3,res) << 2))));
   fix16_t w1;
   w1 = effects_Util_cubic_clipper(_ctx.p0);
   fix16_t dpt0;
   dpt0 = fix_mul(fh,(w0 + (- w1)));
   fix16_t w3;
   w3 = effects_Util_cubic_clipper(_ctx.p1);
   fix16_t dpt1;
   dpt1 = fix_mul(fh,(w1 + (- w3)));
   fix16_t w5;
   w5 = effects_Util_cubic_clipper(_ctx.p2);
   fix16_t dpt2;
   dpt2 = fix_mul(fh,(w3 + (- w5)));
   fix16_t w7;
   w7 = effects_Util_cubic_clipper(_ctx.p3);
   fix16_t dpt3;
   dpt3 = fix_mul(fh,(w5 + (- w7)));
   _ctx.p0 = (_ctx.p0 + dpt0);
   _ctx.p1 = (_ctx.p1 + dpt1);
   _ctx.p2 = (_ctx.p2 + dpt2);
   _ctx.p3 = (_ctx.p3 + dpt3);
   return _ctx.p3;
}

void effects_Ladder__ctx_type_2_init(effects_Ladder__ctx_type_2 &_output_){
   effects_Ladder__ctx_type_2 &_ctx = _output_;
   ;
   _ctx.tuneRatio = 0x0 /* 0.000000 */;
   _ctx.rsize = 0x0 /* 0.000000 */;
   _ctx.res = 0x0 /* 0.000000 */;
   _ctx.heun = false;
   effects_Ladder__ctx_type_0_init(_ctx.h);
   _ctx.fs_nyquist = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.fh = 0x0 /* 0.000000 */;
   effects_Ladder__ctx_type_1_init(_ctx.e);
   _ctx.cut = 0x0 /* 0.000000 */;
   effects_Util__ctx_type_4_init(_ctx._inst43b);
   effects_Util__ctx_type_4_init(_ctx._inst13b);
   
   return ;
}

fix16_t effects_Ladder_getTune(effects_Ladder__ctx_type_2 &_ctx, fix16_t cut){
   _ctx.cut = fix_clip(_ctx.cut,0x0 /* 0.000000 */,(_ctx.fs >> 1));
   fix16_t idx;
   idx = fix_mul(_ctx.cut,_ctx.tuneRatio);
   int iIdx;
   iIdx = fix_to_int(idx);
   if(iIdx < 1023){
      return (_ctx.tune_table[iIdx] + fix_mul((idx % 0x10000 /* 1.000000 */),(_ctx.tune_table[(1 + iIdx)] + (- _ctx.tune_table[iIdx]))));
   }
   else
   {
      return _ctx.tune_table[1023];
   }
}

fix16_t effects_Ladder_process_euler(effects_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res){
   if(effects_Util_change(_ctx._inst13b,_ctx.cut)){
      _ctx.fh = effects_Ladder_getTune(_ctx,_ctx.cut);
   }
   fix16_t out;
   out = effects_Ladder_euler(_ctx.e,input,_ctx.fh,_ctx.res);
   return out;
}

fix16_t effects_Ladder_process_heun(effects_Ladder__ctx_type_2 &_ctx, fix16_t input, fix16_t cut, fix16_t res){
   if(effects_Util_change(_ctx._inst43b,_ctx.cut)){
      _ctx.fh = effects_Ladder_getTune(_ctx,_ctx.cut);
   }
   fix16_t out;
   out = effects_Ladder_heun(_ctx.h,input,_ctx.fh,_ctx.res);
   return out;
}

void effects_Ladder_process_bufferTo(effects_Ladder__ctx_type_2 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   int min_nb;
   min_nb = 128;
   if(128 < min_nb){
      min_nb = 128;
   }
   nb = int_clip(nb,0,min_nb);
   if(nb == 0){
      nb = min_nb;
   }
   int i;
   i = 0;
   if(_ctx.heun){
      while(i < nb){
         oBuffer[i] = effects_Ladder_process_heun(_ctx,input[i],_ctx.cut,_ctx.res);
         i = (1 + i);
      }
   }
   else
   {
      while(i < nb){
         oBuffer[i] = effects_Ladder_process_euler(_ctx,input[i],_ctx.cut,_ctx.res);
         i = (1 + i);
      }
   }
}

void effects_Ladder_updateTune(effects_Ladder__ctx_type_2 &_ctx){
   fix16_t fi;
   int i;
   i = 0;
   while(i < 1024){
      fi = fix_div(fix_mul(_ctx.fs_nyquist,int_to_fix(i)),_ctx.rsize);
      _ctx.tune_table[i] = fix_div(fix_mul(0x6487e /* 6.283185 */,fi),(_ctx.fs << 2));
      i = (1 + i);
   }
}

void effects_Ladder_setSamplerate(effects_Ladder__ctx_type_2 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.fs_nyquist = (_ctx.fs >> 1);
      _ctx.tuneRatio = fix_div(_ctx.rsize,_ctx.fs_nyquist);
      effects_Ladder_updateTune(_ctx);
   }
}

void effects_CombFF__ctx_type_0_init(effects_CombFF__ctx_type_0 &_output_){
   effects_CombFF__ctx_type_0 &_ctx = _output_;
   _ctx.scale = 0x0 /* 0.000000 */;
   _ctx.pos = 0;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.delay = 0;
   _ctx.decay = 0x0 /* 0.000000 */;
   ;
   effects_CombFF_default(_ctx);
   
   return ;
}

fix16_t effects_CombFF_process(effects_CombFF__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t decayed;
   decayed = fix_mul(_ctx.decay,_ctx.buffer[_ctx.pos]);
   _ctx.buffer[_ctx.pos] = sample;
   _ctx.pos = (1 + _ctx.pos);
   _ctx.pos = (_ctx.pos % _ctx.delay);
   return fix_mul(_ctx.scale,(decayed + sample));
}

void effects_CombFF_process_bufferTo(effects_CombFF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t decayed;
   int i;
   i = 0;
   while(i < nb){
      decayed = fix_mul(_ctx.decay,_ctx.buffer[_ctx.pos]);
      _ctx.buffer[_ctx.pos] = input[i];
      oBuffer[i] = fix_mul(_ctx.scale,(decayed + _ctx.buffer[_ctx.pos]));
      _ctx.pos = (1 + _ctx.pos);
      _ctx.pos = (_ctx.pos % _ctx.delay);
      i = (1 + i);
   }
}

fix16_t effects_Saturator_tanh_wrapper(fix16_t x){
   if(x > 0x40000 /* 4.000000 */){
      return 0x10000 /* 1.000000 */;
   }
   if(x < -0x40000 /* -4.000000 */){
      return -0x10000 /* -1.000000 */;
   }
   return effects_Saturator_tanh_table(x);
}

void effects_Saturator__ctx_type_7_init(effects_Saturator__ctx_type_7 &_output_){
   effects_Saturator__ctx_type_7 &_ctx = _output_;
   _ctx.threshopp = 0x0 /* 0.000000 */;
   _ctx.threshinv = 0x0 /* 0.000000 */;
   _ctx.thresh = 0x0 /* 0.000000 */;
   _ctx.coeff = 0x0 /* 0.000000 */;
   effects_Saturator_default(_ctx);
   
   return ;
}

fix16_t effects_Saturator_process(effects_Saturator__ctx_type_7 &_ctx, fix16_t x){
   if((x == 0x0 /* 0.000000 */) || (_ctx.coeff == 0x0 /* 0.000000 */)){
      return 0x0 /* 0.000000 */;
   }
   if(_ctx.coeff != 0x10000 /* 1.000000 */){
      x = fix_mul(_ctx.coeff,x);
   }
   if(fix_abs(x) <= _ctx.thresh){
      return x;
   }
   else
   {
      if(x > 0x0 /* 0.000000 */){
         if(_ctx.thresh >= 0x10000 /* 1.000000 */){
            return 0x10000 /* 1.000000 */;
         }
         else
         {
            if(_ctx.thresh <= 0x0 /* 0.000000 */){
               return effects_Saturator_tanh_wrapper(x);
            }
            else
            {
               return (_ctx.thresh + fix_mul(_ctx.threshopp,effects_Saturator_tanh_wrapper(fix_mul(_ctx.threshinv,(x + (- _ctx.thresh))))));
            }
         }
      }
      else
      {
         if(_ctx.thresh >= 0x10000 /* 1.000000 */){
            return -0x10000 /* -1.000000 */;
         }
         else
         {
            if(_ctx.thresh <= 0x0 /* 0.000000 */){
               return effects_Saturator_tanh_table(x);
            }
            else
            {
               return (- (_ctx.thresh + fix_mul(_ctx.threshopp,effects_Saturator_tanh_wrapper(fix_mul(_ctx.threshinv,((- _ctx.thresh) + (- x)))))));
            }
         }
      }
   }
}

void effects_Saturator_process_bufferTo(effects_Saturator__ctx_type_7 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   int i;
   i = 0;
   if(_ctx.coeff == 0x0 /* 0.000000 */){
      i = 0;
      while(i < nb){
         oBuffer[i] = 0x0 /* 0.000000 */;
         i = (1 + i);
      }
   }
   else
   {
      if(_ctx.coeff != 0x10000 /* 1.000000 */){
         i = 0;
         while(i < nb){
            if(input[i] == 0x0 /* 0.000000 */){
               oBuffer[i] = 0x0 /* 0.000000 */;
            }
            else
            {
               oBuffer[i] = fix_mul(_ctx.coeff,input[i]);
            }
            i = (1 + i);
         }
      }
      else
      {
         i = 0;
         while(i < nb){
            oBuffer[i] = input[i];
            i = (1 + i);
         }
      }
      if(_ctx.thresh >= 0x10000 /* 1.000000 */){
         i = 0;
         while(i < nb){
            if(oBuffer[i] > 0x10000 /* 1.000000 */){
               oBuffer[i] = 0x10000 /* 1.000000 */;
            }
            else
            {
               if(oBuffer[i] < -0x10000 /* -1.000000 */){
                  oBuffer[i] = -0x10000 /* -1.000000 */;
               }
            }
            i = (1 + i);
         }
      }
      else
      {
         if(_ctx.thresh <= 0x0 /* 0.000000 */){
            i = 0;
            while(i < nb){
               oBuffer[i] = effects_Saturator_tanh_wrapper(oBuffer[i]);
               i = (1 + i);
            }
         }
         else
         {
            i = 0;
            while(i < nb){
               if(oBuffer[i] > _ctx.thresh){
                  oBuffer[i] = (_ctx.thresh + fix_mul(_ctx.threshopp,effects_Saturator_tanh_wrapper(fix_mul(_ctx.threshinv,(oBuffer[i] + (- _ctx.thresh))))));
               }
               else
               {
                  if(oBuffer[i] < (- _ctx.thresh)){
                     oBuffer[i] = (- (_ctx.thresh + fix_mul(_ctx.threshopp,effects_Saturator_tanh_wrapper(fix_mul(_ctx.threshinv,((- _ctx.thresh) + (- oBuffer[i])))))));
                  }
               }
               i = (1 + i);
            }
         }
      }
   }
}

void effects_SVF__ctx_type_0_init(effects_SVF__ctx_type_0 &_output_){
   effects_SVF__ctx_type_0 &_ctx = _output_;
   _ctx.z2 = 0x0 /* 0.000000 */;
   _ctx.z1 = 0x0 /* 0.000000 */;
   _ctx.targetFreq = 0x0 /* 0.000000 */;
   _ctx.sel = 0;
   _ctx.rsize = 0x0 /* 0.000000 */;
   _ctx.q = 0x0 /* 0.000000 */;
   _ctx.inv_den = 0x0 /* 0.000000 */;
   ;
   _ctx.gRatio = 0x0 /* 0.000000 */;
   _ctx.g = 0x0 /* 0.000000 */;
   _ctx.fs_nyquist = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   effects_Util__ctx_type_5_init(_ctx._inst955);
   effects_Util__ctx_type_4_init(_ctx._inst173b);
   effects_Util__ctx_type_5_init(_ctx._inst1655);
   effects_Util__ctx_type_4_init(_ctx._inst103b);
   _ctx.R = 0x0 /* 0.000000 */;
   effects_SVF_default(_ctx);
   
   return ;
}

void effects_SVF_updateGTable(effects_SVF__ctx_type_0 &_ctx){
   fix16_t wd;
   fix16_t T;
   fix16_t wa;
   fix16_t fi;
   int i;
   i = 0;
   while(i < 1024){
      fi = fix_div(fix_mul(_ctx.fs_nyquist,int_to_fix(i)),_ctx.rsize);
      wd = fix_mul(0x6487e /* 6.283185 */,fi);
      T = fix_div(0x10000 /* 1.000000 */,_ctx.fs);
      wa = fix_mul(fix_tan((fix_mul(T,wd) >> 1)),fix_div(0x20000 /* 2.000000 */,T));
      _ctx.g_table[i] = (fix_mul(T,wa) >> 1);
      i = (1 + i);
   }
}

void effects_SVF_updateG(effects_SVF__ctx_type_0 &_ctx){
   _ctx.freq = fix_clip(_ctx.freq,0x0 /* 0.000000 */,_ctx.fs_nyquist);
   fix16_t idx;
   idx = fix_mul(_ctx.freq,_ctx.gRatio);
   int iIdx;
   iIdx = fix_to_int(idx);
   if(iIdx < 1023){
      _ctx.g = (_ctx.g_table[iIdx] + fix_mul((idx % 0x10000 /* 1.000000 */),(_ctx.g_table[(1 + iIdx)] + (- _ctx.g_table[iIdx]))));
   }
   else
   {
      _ctx.g = _ctx.g_table[1023];
   }
}

fix16_t effects_SVF_process(effects_SVF__ctx_type_0 &_ctx, fix16_t input){
   _ctx.freq = effects_Util_smooth(_ctx._inst955,_ctx.targetFreq,0x1999 /* 0.100000 */);
   if(effects_Util_change(_ctx._inst103b,_ctx.freq)){
      effects_SVF_updateG(_ctx);
      effects_SVF_updateCoeffs(_ctx);
   }
   fix16_t high;
   high = fix_mul(_ctx.inv_den,(input + (- _ctx.z2) + (- fix_mul(_ctx.z1,(_ctx.g + (_ctx.R << 1))))));
   fix16_t band;
   band = (_ctx.z1 + fix_mul(_ctx.g,high));
   fix16_t low;
   low = (_ctx.z2 + fix_mul(_ctx.g,band));
   _ctx.z1 = (band + fix_mul(_ctx.g,high));
   _ctx.z2 = (low + fix_mul(_ctx.g,band));
   fix16_t output;
   switch(_ctx.sel) {
      case 1:
         output = low;
      break;
      case 2:
         output = high;
      break;
      case 3:
         output = band;
      break;
      case 4:
         output = (high + low);
      break;
    default: 
      output = input;
   }
   return output;
}

void effects_SVF_process_bufferTo(effects_SVF__ctx_type_0 &_ctx, int nb, fix16_t (&input)[128], fix16_t (&oBuffer)[128]){
   int min_nb;
   min_nb = 128;
   if(128 < min_nb){
      min_nb = 128;
   }
   nb = int_clip(nb,0,min_nb);
   if(nb == 0){
      nb = min_nb;
   }
   int i;
   i = 0;
   while(i < nb){
      _ctx.freq = effects_Util_smooth(_ctx._inst1655,_ctx.targetFreq,0x1999 /* 0.100000 */);
      if(effects_Util_change(_ctx._inst173b,_ctx.freq)){
         effects_SVF_updateG(_ctx);
         effects_SVF_updateCoeffs(_ctx);
      }
      fix16_t high;
      high = fix_mul(_ctx.inv_den,(input[i] + (- _ctx.z2) + (- fix_mul(_ctx.z1,(_ctx.g + (_ctx.R << 1))))));
      fix16_t band;
      band = (_ctx.z1 + fix_mul(_ctx.g,high));
      fix16_t low;
      low = (_ctx.z2 + fix_mul(_ctx.g,band));
      _ctx.z1 = (band + fix_mul(_ctx.g,high));
      _ctx.z2 = (low + fix_mul(_ctx.g,band));
      switch(_ctx.sel) {
         case 1:
            oBuffer[i] = low;
         break;
         case 2:
            oBuffer[i] = high;
         break;
         case 3:
            oBuffer[i] = band;
         break;
         case 4:
            oBuffer[i] = (high + low);
         break;
       default: 
         oBuffer[i] = input[i];
      }
      i = (1 + i);
   }
}

void effects_SVF_setSamplerate(effects_SVF__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.fs_nyquist = fix_mul(0x7333 /* 0.450000 */,_ctx.fs);
      _ctx.gRatio = fix_div(_ctx.rsize,_ctx.fs_nyquist);
      effects_SVF_updateGTable(_ctx);
      effects_SVF_updateG(_ctx);
      effects_SVF_updateCoeffs(_ctx);
   }
}


