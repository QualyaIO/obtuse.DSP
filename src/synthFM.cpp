
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "synthFM.h"

fix16_t synthFM_Wavetable_getSample(int wavetableIdx, int index){
   fix16_t sample;
   sample = 0x0 /* 0.000000 */;
   switch(wavetableIdx) {
      case 0:
         sample = synthFM_Wavetable_sin_wave(0,index);
      break;
      case 1:
         sample = synthFM_Wavetable_tri_wave(0,index);
      break;
      case 2:
         sample = synthFM_Wavetable_saw_wave(0,index);
      break;
      case 3:
         sample = synthFM_Wavetable_square_wave(0,index);
      break;
      case 4:
         sample = synthFM_Wavetable_sin_wave(0,index);
      break;
      case 5:
         sample = synthFM_Wavetable_tri_wave_bl(0,index);
      break;
      case 6:
         sample = synthFM_Wavetable_saw_wave_bl(0,index);
      break;
      case 7:
         sample = synthFM_Wavetable_square_wave_bl(0,index);
      break;
    
   }
   return sample;
}

fix16_t synthFM_Wavetable_getSampleFrom(fix16_t (&wavetable)[4096], fix16_t index){
   int idx1;
   idx1 = fix_to_int(index);
   int idx2;
   idx2 = (1 + fix_to_int(index));
   if(idx2 >= 4096){
      idx2 = (idx2 % 4096);
      if(idx1 >= 4096){
         idx1 = (idx1 % 4096);
      }
   }
   return (wavetable[idx1] + fix_mul((index % 0x10000 /* 1.000000 */),(wavetable[idx2] + (- wavetable[idx1]))));
}

void synthFM_Wavetable_morphTo(fix16_t wavetableIdx, fix16_t phase, fix16_t (&buffer)[4096]){
   wavetableIdx = fix_clip(wavetableIdx,0x0 /* 0.000000 */,0x80000 /* 8.000000 */);
   int phase_shift;
   phase_shift = fix_to_int((phase << 12));
   int wavetable1;
   wavetable1 = fix_to_int(fix_floor(wavetableIdx));
   int wavetable2;
   wavetable2 = (1 + wavetable1);
   if(wavetable2 >= 8){
      wavetable2 = 0;
   }
   if(wavetable1 >= 8){
      wavetable1 = 0;
   }
   fix16_t ratio;
   ratio = (wavetableIdx % 0x10000 /* 1.000000 */);
   int i;
   i = 0;
   fix16_t s1;
   fix16_t s2;
   while(i < 4096){
      s1 = synthFM_Wavetable_getSample(wavetable1,(i + phase_shift));
      s2 = synthFM_Wavetable_getSample(wavetable2,i);
      buffer[i] = (s1 + fix_mul(ratio,(s2 + (- s1))));
      i = (1 + i);
   }
}

void synthFM_Wavetable_getRandomMorph(fix16_t (&oBuff)[4096]){
   int basetable;
   basetable = 0;
   if(8 > 1){
      basetable = (irandom() % 7);
   }
   fix16_t wavetableIdx;
   wavetableIdx = (fix_random() + int_to_fix(basetable));
   synthFM_Wavetable_bufferWavetable(oBuff);
   synthFM_Wavetable_morphTo(wavetableIdx,0x0 /* 0.000000 */,oBuff);
}

fix16_t synthFM_Wavetable_getRandRandomMorph(fix16_t (&oBuff)[4096]){
   synthFM_Wavetable_getRandomMorph(oBuff);
   int idx;
   idx = 0;
   if(4096 > 0){
      idx = (irandom() % 4096);
   }
   return synthFM_Wavetable_getSampleFrom(oBuff,int_to_fix(idx));
}

void synthFM_Buffer_buffer_large(fix16_t (&oBuff)[2048]){
   int i;
   i = 0;
   while(i < 2048){
      oBuff[i] = 0x0 /* 0.000000 */;
      i = (1 + i);
   }
}

void synthFM_OSC__ctx_type_0_init(synthFM_OSC__ctx_type_0 &_output_){
   synthFM_OSC__ctx_type_0 &_ctx = _output_;
   _ctx.stepRatio = 0x0 /* 0.000000 */;
   _ctx.step = 0x0 /* 0.000000 */;
   _ctx.rsize = 0x0 /* 0.000000 */;
   _ctx.phase_base = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.last_val_feedback = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   synthFM_OSC_default(_ctx);
   
   return ;
}

void synthFM_OSC_process_bufferTo(synthFM_OSC__ctx_type_0 &_ctx, fix16_t (&wavetable)[4096], int nb, fix16_t (&env)[128], fix16_t (&phase_shift)[128], fix16_t (&phase_env)[128], fix16_t phase_shift_level, uint8_t shift_level, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t max_phase;
   max_phase = (_ctx.rsize << 1);
   fix16_t phase_range;
   phase_range = fix_mul(max_phase,phase_shift_level);
   fix16_t level_shift_coeff;
   level_shift_coeff = (phase_shift_level >> 1);
   int i;
   i = 0;
   if(shift_level){
      while(i < nb){
         _ctx.phase = (_ctx.phase + _ctx.step);
         while(_ctx.phase > _ctx.rsize){
            _ctx.phase = (_ctx.phase + (- _ctx.rsize));
         }
         oBuffer[i] = fix_mul(fix_mul(env[i],synthFM_Wavetable_getSampleFrom(wavetable,_ctx.phase)),(0x10000 /* 1.000000 */ + (- fix_mul(level_shift_coeff,(phase_env[i] + phase_shift[i])))));
         i = (1 + i);
      }
   }
   else
   {
      while(i < nb){
         _ctx.phase = (_ctx.phase + _ctx.step);
         while(_ctx.phase > _ctx.rsize){
            _ctx.phase = (_ctx.phase + (- _ctx.rsize));
         }
         oBuffer[i] = fix_mul(env[i],synthFM_Wavetable_getSampleFrom(wavetable,(_ctx.phase + max_phase + fix_mul(phase_range,phase_shift[i]))));
         i = (1 + i);
      }
   }
}

void synthFM_OSC_process_bufferTo_simple(synthFM_OSC__ctx_type_0 &_ctx, fix16_t (&wavetable)[4096], int nb, fix16_t (&env)[128], fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   int i;
   i = 0;
   while(i < nb){
      _ctx.phase = (_ctx.phase + _ctx.step);
      while(_ctx.phase > _ctx.rsize){
         _ctx.phase = (_ctx.phase + (- _ctx.rsize));
      }
      oBuffer[i] = fix_mul(env[i],synthFM_Wavetable_getSampleFrom(wavetable,(_ctx.phase + _ctx.phase_base)));
      i = (1 + i);
   }
}

void synthFM_OSC_process_bufferTo_feedback(synthFM_OSC__ctx_type_0 &_ctx, fix16_t (&wavetable)[4096], int nb, fix16_t (&env)[128], fix16_t feedback, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t max_phase;
   max_phase = (_ctx.rsize << 1);
   fix16_t phase_range;
   phase_range = fix_mul(feedback,max_phase);
   int i;
   i = 0;
   while(i < nb){
      _ctx.phase = (_ctx.phase + _ctx.step);
      while(_ctx.phase > _ctx.rsize){
         _ctx.phase = (_ctx.phase + (- _ctx.rsize));
      }
      _ctx.last_val_feedback = fix_mul(env[i],synthFM_Wavetable_getSampleFrom(wavetable,(_ctx.phase + _ctx.phase_base + max_phase + fix_mul(_ctx.last_val_feedback,phase_range))));
      oBuffer[i] = _ctx.last_val_feedback;
      i = (1 + i);
   }
}

void synthFM_OSC_process_bufferTo_simplest(synthFM_OSC__ctx_type_0 &_ctx, fix16_t (&wavetable)[4096], int nb, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   int i;
   i = 0;
   while(i < nb){
      _ctx.phase = (_ctx.phase + _ctx.step);
      while(_ctx.phase > _ctx.rsize){
         _ctx.phase = (_ctx.phase + (- _ctx.rsize));
      }
      oBuffer[i] = synthFM_Wavetable_getSampleFrom(wavetable,(_ctx.phase + _ctx.phase_base));
      i = (1 + i);
   }
}

void synthFM_OSC_setSamplerate(synthFM_OSC__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.stepRatio = fix_div(_ctx.rsize,_ctx.fs);
   }
   synthFM_OSC_updateStep(_ctx);
}

void synthFM_OSC__ctx_type_1_init(synthFM_OSC__ctx_type_1 &_output_){
   synthFM_OSC__ctx_type_1 &_ctx = _output_;
   synthFM_OSC__ctx_type_0_init(_ctx._inst4ad);
   synthFM_OSC__ctx_type_0_init(_ctx._inst35f);
   synthFM_OSC__ctx_type_0_init(_ctx._inst2a3);
   synthFM_OSC__ctx_type_0_init(_ctx._inst133);
   
   return ;
}

void synthFM_OSC_dummy(synthFM_OSC__ctx_type_1 &_ctx, fix16_t (&wavetable)[4096]){
   fix16_t buff[128];
   synthFM_Buffer_buffer(buff);
   synthFM_OSC_process_bufferTo(_ctx._inst133,wavetable,0,buff,buff,buff,0x0 /* 0.000000 */,false,buff);
   synthFM_OSC_process_bufferTo_simple(_ctx._inst2a3,wavetable,0,buff,buff);
   synthFM_OSC_process_bufferTo_feedback(_ctx._inst35f,wavetable,0,buff,0x0 /* 0.000000 */,buff);
   synthFM_OSC_process_bufferTo_simplest(_ctx._inst4ad,wavetable,0,buff);
}

void synthFM_Notes__ctx_type_0_init(synthFM_Notes__ctx_type_0 &_output_){
   synthFM_Notes__ctx_type_0 &_ctx = _output_;
   _ctx.poly = false;
   int_init_array(128,0,_ctx.notes);
   _ctx.nb_notes = 0;
   int_init_array(128,0,_ctx.last_notes);
   _ctx.allowDuplicates = false;
   synthFM_Notes_default(_ctx);
   
   return ;
}

int synthFM_Notes_firstNote(synthFM_Notes__ctx_type_0 &_ctx){
   int first_played;
   first_played = 0;
   if(_ctx.nb_notes > 0){
      first_played = _ctx.last_notes[0];
   }
   return first_played;
}

int synthFM_Notes_lastNote(synthFM_Notes__ctx_type_0 &_ctx){
   int last_played;
   last_played = 0;
   if(_ctx.nb_notes > 0){
      last_played = _ctx.last_notes[((-1) + _ctx.nb_notes)];
   }
   return last_played;
}

uint8_t synthFM_Notes_noteOff(synthFM_Notes__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   if(_ctx.notes[note] > 0){
      if(_ctx.poly){
         _ctx.notes[note] = 0;
         _ctx.nb_notes = 0;
      }
      else
      {
         int i;
         i = ((-1) + _ctx.notes[note]);
         while(i < _ctx.nb_notes){
            if(i < 127){
               _ctx.last_notes[i] = _ctx.last_notes[(1 + i)];
            }
            else
            {
               _ctx.last_notes[i] = 0;
            }
            if(_ctx.last_notes[i] > 0){
               _ctx.notes[((-1) + _ctx.last_notes[i])] = (1 + i);
            }
            i = (1 + i);
         }
         _ctx.notes[note] = 0;
         _ctx.nb_notes = ((-1) + _ctx.nb_notes);
         if(_ctx.nb_notes < 0){
            _ctx.nb_notes = 0;
         }
      }
      return true;
   }
   return false;
}

uint8_t synthFM_Notes_noteOn(synthFM_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   uint8_t isNew;
   isNew = (_ctx.notes[note] <= 0);
   if(_ctx.allowDuplicates || isNew){
      if(bool_not(_ctx.poly)){
         if(bool_not(isNew)){
            synthFM_Notes_noteOff(_ctx,note,channel);
         }
         _ctx.nb_notes = (1 + _ctx.nb_notes);
         if(_ctx.nb_notes > 128){
            _ctx.nb_notes = 128;
         }
      }
      else
      {
         int last_note;
         last_note = synthFM_Notes_lastNote(_ctx);
         if(last_note > 0){
            _ctx.notes[((-1) + last_note)] = 0;
         }
         _ctx.nb_notes = 1;
      }
      _ctx.notes[note] = _ctx.nb_notes;
      _ctx.last_notes[((-1) + _ctx.nb_notes)] = (1 + note);
   }
   return isNew;
}

void synthFM_ADSR__ctx_type_0_init(synthFM_ADSR__ctx_type_0 &_output_){
   synthFM_ADSR__ctx_type_0 &_ctx = _output_;
   _ctx.getMaxValues_ret_3 = 0x0 /* 0.000000 */;
   _ctx.getMaxValues_ret_2 = 0x0 /* 0.000000 */;
   _ctx.getMaxValues_ret_1 = 0x0 /* 0.000000 */;
   _ctx.getMaxValues_ret_0 = 0x0 /* 0.000000 */;
   
   return ;
}

void synthFM_ADSR_getMaxValues(synthFM_ADSR__ctx_type_0 &_ctx){
   fix16_t max_t;
   max_t = 0x3c0000 /* 60.000000 */;
   _ctx.getMaxValues_ret_0 = max_t;
   _ctx.getMaxValues_ret_1 = max_t;
   _ctx.getMaxValues_ret_2 = 0x10000 /* 1.000000 */;
   _ctx.getMaxValues_ret_3 = max_t;
   return ;
}

fix16_t synthFM_ADSR_getMaxAttack(synthFM_ADSR__ctx_type_1 &_ctx){
   fix16_t max_a;
   synthFM_ADSR_getMaxValues(_ctx._inst173);
   max_a = synthFM_ADSR_getMaxValues_ret_0(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_1(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_2(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_3(_ctx._inst173);
   return max_a;
}

fix16_t synthFM_ADSR_getMaxDecay(synthFM_ADSR__ctx_type_2 &_ctx){
   fix16_t max_d;
   synthFM_ADSR_getMaxValues(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_0(_ctx._inst173);
   max_d = synthFM_ADSR_getMaxValues_ret_1(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_2(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_3(_ctx._inst173);
   return max_d;
}

fix16_t synthFM_ADSR_getMaxSurtain(synthFM_ADSR__ctx_type_3 &_ctx){
   fix16_t max_s;
   synthFM_ADSR_getMaxValues(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_0(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_1(_ctx._inst173);
   max_s = synthFM_ADSR_getMaxValues_ret_2(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_3(_ctx._inst173);
   return max_s;
}

fix16_t synthFM_ADSR_getMaxRelease(synthFM_ADSR__ctx_type_4 &_ctx){
   fix16_t max_r;
   synthFM_ADSR_getMaxValues(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_0(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_1(_ctx._inst173);
   synthFM_ADSR_getMaxValues_ret_2(_ctx._inst173);
   max_r = synthFM_ADSR_getMaxValues_ret_3(_ctx._inst173);
   return max_r;
}

void synthFM_ADSR__ctx_type_5_init(synthFM_ADSR__ctx_type_5 &_output_){
   synthFM_ADSR__ctx_type_5 &_ctx = _output_;
   _ctx.target = 0x0 /* 0.000000 */;
   _ctx.step = 0x0 /* 0.000000 */;
   _ctx.state = 0;
   _ctx.s = 0x0 /* 0.000000 */;
   _ctx.retrigger = false;
   _ctx.r_step = 0x0 /* 0.000000 */;
   _ctx.r = 0x0 /* 0.000000 */;
   _ctx.out = 0x0 /* 0.000000 */;
   _ctx.min_t = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.d_step = 0x0 /* 0.000000 */;
   _ctx.d = 0x0 /* 0.000000 */;
   _ctx.a_target = 0x0 /* 0.000000 */;
   _ctx.a_step = 0x0 /* 0.000000 */;
   _ctx.a = 0x0 /* 0.000000 */;
   synthFM_ADSR__ctx_type_0_init(_ctx._inst3673);
   synthFM_Util__ctx_type_2_init(_ctx._inst1851);
   synthFM_Util__ctx_type_2_init(_ctx._inst151);
   synthFM_ADSR_default(_ctx);
   
   return ;
}

fix16_t synthFM_ADSR_process(synthFM_ADSR__ctx_type_5 &_ctx, uint8_t bgate){
   fix16_t scale;
   scale = 0x3e80000 /* 1000.000000 */;
   fix16_t scale_i;
   scale_i = 0x41 /* 0.001000 */;
   if(synthFM_Util_edge(_ctx._inst151,bgate) || _ctx.retrigger){
      _ctx.state = 1;
      _ctx.target = fix_mul(_ctx.a_target,scale);
      _ctx.step = _ctx.a_step;
      _ctx.retrigger = false;
   }
   if(_ctx.state == 0){
      _ctx.out = 0x0 /* 0.000000 */;
   }
   else
   {
      _ctx.out = (_ctx.out + _ctx.step);
   }
   if(_ctx.state == 1){
      if(_ctx.out >= _ctx.target){
         _ctx.step = _ctx.d_step;
         _ctx.out = _ctx.target;
         _ctx.target = fix_mul(_ctx.s,scale);
         _ctx.state = 2;
      }
      if(bool_not(bgate)){
         _ctx.step = synthFM_ADSR_stepToRelease(_ctx,fix_mul(_ctx.out,scale_i));
         _ctx.target = 0x0 /* 0.000000 */;
         _ctx.state = 4;
      }
   }
   if(_ctx.state == 2){
      if(bool_not(bgate)){
         _ctx.step = synthFM_ADSR_stepToRelease(_ctx,fix_mul(_ctx.out,scale_i));
         _ctx.target = 0x0 /* 0.000000 */;
         _ctx.state = 4;
      }
      if(_ctx.out <= _ctx.target){
         _ctx.out = _ctx.target;
         _ctx.step = 0x0 /* 0.000000 */;
         _ctx.state = 3;
      }
   }
   if(_ctx.state == 3){
      if(bool_not(bgate)){
         _ctx.step = _ctx.r_step;
         _ctx.target = 0x0 /* 0.000000 */;
         _ctx.state = 4;
      }
   }
   if(_ctx.state == 4){
      if(_ctx.out <= 0x0 /* 0.000000 */){
         _ctx.out = 0x0 /* 0.000000 */;
         _ctx.state = 0;
         _ctx.step = 0x0 /* 0.000000 */;
         _ctx.target = 0x0 /* 0.000000 */;
      }
   }
   return fix_clip(fix_mul(_ctx.out,scale_i),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
}

uint8_t synthFM_ADSR_process_bufferTo(synthFM_ADSR__ctx_type_5 &_ctx, uint8_t bgate, int nb, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   fix16_t scale;
   scale = 0x3e80000 /* 1000.000000 */;
   fix16_t scale_i;
   scale_i = 0x41 /* 0.001000 */;
   uint8_t idle;
   idle = true;
   int i;
   i = 0;
   while(i < nb){
      if(synthFM_Util_edge(_ctx._inst1851,bgate) || _ctx.retrigger){
         _ctx.state = 1;
         _ctx.target = fix_mul(_ctx.a_target,scale);
         _ctx.step = _ctx.a_step;
         _ctx.retrigger = false;
      }
      if(_ctx.state == 0){
         _ctx.out = 0x0 /* 0.000000 */;
      }
      else
      {
         idle = false;
         _ctx.out = (_ctx.out + _ctx.step);
         if(_ctx.state == 1){
            if(_ctx.out >= _ctx.target){
               _ctx.step = _ctx.d_step;
               _ctx.out = _ctx.target;
               _ctx.target = fix_mul(_ctx.s,scale);
               _ctx.state = 2;
            }
            if(bool_not(bgate)){
               _ctx.step = synthFM_ADSR_stepToRelease(_ctx,fix_mul(_ctx.out,scale_i));
               _ctx.target = 0x0 /* 0.000000 */;
               _ctx.state = 4;
            }
         }
         if(_ctx.state == 2){
            if(bool_not(bgate)){
               _ctx.step = synthFM_ADSR_stepToRelease(_ctx,fix_mul(_ctx.out,scale_i));
               _ctx.target = 0x0 /* 0.000000 */;
               _ctx.state = 4;
            }
            if(_ctx.out <= _ctx.target){
               _ctx.out = _ctx.target;
               _ctx.step = 0x0 /* 0.000000 */;
               _ctx.state = 3;
            }
         }
         if(_ctx.state == 3){
            if(bool_not(bgate)){
               _ctx.step = _ctx.r_step;
               _ctx.target = 0x0 /* 0.000000 */;
               _ctx.state = 4;
            }
         }
         if(_ctx.state == 4){
            if(_ctx.out <= 0x0 /* 0.000000 */){
               _ctx.out = 0x0 /* 0.000000 */;
               _ctx.state = 0;
               _ctx.step = 0x0 /* 0.000000 */;
               _ctx.target = 0x0 /* 0.000000 */;
            }
         }
      }
      oBuffer[i] = fix_clip(fix_mul(_ctx.out,scale_i),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
      i = (1 + i);
   }
   return idle;
}

void synthFM_ADSR_config(synthFM_ADSR__ctx_type_5 &_ctx, fix16_t newA, fix16_t newD, fix16_t newS, fix16_t newR){
   fix16_t max_a;
   fix16_t max_d;
   fix16_t max_s;
   fix16_t max_r;
   synthFM_ADSR_getMaxValues(_ctx._inst3673);
   max_a = synthFM_ADSR_getMaxValues_ret_0(_ctx._inst3673);
   max_d = synthFM_ADSR_getMaxValues_ret_1(_ctx._inst3673);
   max_s = synthFM_ADSR_getMaxValues_ret_2(_ctx._inst3673);
   max_r = synthFM_ADSR_getMaxValues_ret_3(_ctx._inst3673);
   _ctx.a = fix_clip(newA,0x0 /* 0.000000 */,max_a);
   _ctx.d = fix_clip(newD,0x0 /* 0.000000 */,max_d);
   _ctx.s = fix_clip(newS,0x0 /* 0.000000 */,max_s);
   _ctx.r = fix_clip(newR,0x0 /* 0.000000 */,max_r);
   synthFM_ADSR_updateSteps(_ctx);
}

void synthFM_FM__ctx_type_0_init(synthFM_FM__ctx_type_0 &_output_){
   synthFM_FM__ctx_type_0 &_ctx = _output_;
   _ctx.target_level = 0x0 /* 0.000000 */;
   _ctx.sustaining = false;
   _ctx.sustain = false;
   synthFM_Notes__ctx_type_0_init(_ctx.playingnotes);
   _ctx.n = 0;
   synthFM_ADSR__ctx_type_5_init(_ctx.modulatoradsr);
   _ctx.modulator_target_level = false;
   _ctx.modulator_phase_shift = 0x0 /* 0.000000 */;
   _ctx.modulator_phase_range = 0x0 /* 0.000000 */;
   _ctx.modulator_max_phase = 0x0 /* 0.000000 */;
   _ctx.modulator_level_coeff = 0x0 /* 0.000000 */;
   _ctx.modulator_level = 0x0 /* 0.000000 */;
   _ctx.modulator_feedback = 0x0 /* 0.000000 */;
   _ctx.modulator_env = 0x0 /* 0.000000 */;
   _ctx.modulatorRatio = 0x0 /* 0.000000 */;
   synthFM_OSC__ctx_type_0_init(_ctx.modulator);
   _ctx.level_step_ref = 0x0 /* 0.000000 */;
   _ctx.level_step = 0x0 /* 0.000000 */;
   _ctx.level = 0x0 /* 0.000000 */;
   _ctx.gate = false;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.freq = 0x0 /* 0.000000 */;
   _ctx.env_decimation_factor = 0;
   synthFM_ADSR__ctx_type_5_init(_ctx.carrieradsr);
   _ctx.carrier_phase_range = 0x0 /* 0.000000 */;
   _ctx.carrier_max_phase = 0x0 /* 0.000000 */;
   _ctx.carrier_env = 0x0 /* 0.000000 */;
   _ctx.carrierRatio = 0x0 /* 0.000000 */;
   synthFM_OSC__ctx_type_0_init(_ctx.carrier);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_modulator_env_short);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_modulator_env);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_modulator);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_carrier_env_short);
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_carrier_env);
   _ctx.bend = 0x0 /* 0.000000 */;
   synthFM_FM_default(_ctx);
   
   return ;
}

fix16_t synthFM_FM_process(synthFM_FM__ctx_type_0 &_ctx, fix16_t (&wavetable_modulator)[4096], fix16_t (&wavetable_carrier)[4096]){
   _ctx.n = (1 + _ctx.n);
   uint8_t update_env;
   update_env = true;
   if(_ctx.env_decimation_factor > 0){
      update_env = ((_ctx.n % _ctx.env_decimation_factor) == 0);
   }
   fix16_t carrier_val;
   carrier_val = 0x0 /* 0.000000 */;
   if(update_env){
      if(_ctx.level != _ctx.target_level){
         _ctx.level = (_ctx.level + _ctx.level_step);
         if(((_ctx.level_step > 0x0 /* 0.000000 */) && (_ctx.level > _ctx.target_level)) || ((_ctx.level_step < 0x0 /* 0.000000 */) && (_ctx.level < _ctx.target_level))){
            _ctx.level = _ctx.target_level;
         }
      }
      _ctx.carrier_env = fix_mul(_ctx.level,synthFM_ADSR_process(_ctx.carrieradsr,(_ctx.gate || _ctx.sustaining)));
      _ctx.modulator_env = synthFM_ADSR_process(_ctx.modulatoradsr,(_ctx.gate || _ctx.sustaining));
   }
   if(_ctx.carrier_env > 0x0 /* 0.000000 */){
      if(_ctx.modulator_target_level){
         fix16_t carrier_level;
         carrier_level = 0x10000 /* 1.000000 */;
         if(_ctx.modulator_env > 0x0 /* 0.000000 */){
            fix16_t modulator_val;
            modulator_val = fix_mul(_ctx.modulator_env,synthFM_OSC_process(_ctx.modulator,wavetable_modulator));
            carrier_level = (0x10000 /* 1.000000 */ + (- fix_mul(_ctx.modulator_level_coeff,(_ctx.modulator_env + modulator_val))));
            if(_ctx.modulator_phase_range != 0x0 /* 0.000000 */){
               synthFM_OSC_setPhase(_ctx.modulator,(_ctx.modulator_max_phase + _ctx.modulator_phase_shift + fix_mul(_ctx.modulator_phase_range,modulator_val)));
            }
         }
         else
         {
            synthFM_OSC_resetPhase(_ctx.modulator);
            synthFM_OSC_setPhase(_ctx.modulator,_ctx.modulator_phase_shift);
         }
         carrier_val = fix_mul(fix_mul(_ctx.carrier_env,carrier_level),synthFM_OSC_process(_ctx.carrier,wavetable_carrier));
      }
      else
      {
         fix16_t carrier_phase;
         carrier_phase = 0x0 /* 0.000000 */;
         if(_ctx.modulator_env > 0x0 /* 0.000000 */){
            fix16_t modulator_val;
            modulator_val = fix_mul(_ctx.modulator_env,synthFM_OSC_process(_ctx.modulator,wavetable_modulator));
            carrier_phase = (_ctx.carrier_max_phase + fix_mul(_ctx.carrier_phase_range,modulator_val));
            if(_ctx.modulator_phase_range != 0x0 /* 0.000000 */){
               synthFM_OSC_setPhase(_ctx.modulator,(_ctx.modulator_max_phase + _ctx.modulator_phase_shift + fix_mul(_ctx.modulator_phase_range,modulator_val)));
            }
         }
         else
         {
            synthFM_OSC_resetPhase(_ctx.modulator);
            synthFM_OSC_setPhase(_ctx.modulator,_ctx.modulator_phase_shift);
         }
         synthFM_OSC_setPhase(_ctx.carrier,carrier_phase);
         carrier_val = fix_mul(_ctx.carrier_env,synthFM_OSC_process(_ctx.carrier,wavetable_carrier));
      }
   }
   else
   {
      synthFM_OSC_resetPhase(_ctx.carrier);
      if(_ctx.modulator_env <= 0x0 /* 0.000000 */){
         synthFM_OSC_resetPhase(_ctx.modulator);
         synthFM_OSC_setPhase(_ctx.modulator,_ctx.modulator_phase_shift);
      }
   }
   return carrier_val;
}

void synthFM_FM_process_bufferTo(synthFM_FM__ctx_type_0 &_ctx, fix16_t (&wavetable_modulator)[4096], fix16_t (&wavetable_carrier)[4096], int nb, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   uint8_t env_modulator_idle;
   env_modulator_idle = true;
   uint8_t env_carrier_idle;
   env_carrier_idle = true;
   int env_df;
   env_df = _ctx.env_decimation_factor;
   if(env_df < 1){
      env_df = 1;
   }
   if(_ctx.env_decimation_factor > 1){
      int nb_env;
      nb_env = ((_ctx.n + nb) / _ctx.env_decimation_factor);
      if(nb_env > 0){
         env_carrier_idle = synthFM_ADSR_process_bufferTo(_ctx.carrieradsr,(_ctx.gate || _ctx.sustaining),nb_env,_ctx.buffer_carrier_env_short);
         env_modulator_idle = synthFM_ADSR_process_bufferTo(_ctx.modulatoradsr,(_ctx.gate || _ctx.sustaining),nb_env,_ctx.buffer_modulator_env_short);
         int i;
         i = 0;
         int i_env;
         i_env = 0;
         while(i < nb){
            _ctx.n = ((1 + _ctx.n) % _ctx.env_decimation_factor);
            if(_ctx.n == 0){
               if(_ctx.level != _ctx.target_level){
                  _ctx.level = (_ctx.level + _ctx.level_step);
                  if(((_ctx.level_step > 0x0 /* 0.000000 */) && (_ctx.level > _ctx.target_level)) || ((_ctx.level_step < 0x0 /* 0.000000 */) && (_ctx.level < _ctx.target_level))){
                     _ctx.level = _ctx.target_level;
                  }
               }
               _ctx.modulator_env = _ctx.buffer_modulator_env_short[i_env];
               _ctx.carrier_env = fix_mul(_ctx.level,_ctx.buffer_carrier_env_short[i_env]);
               i_env = (1 + i_env);
            }
            _ctx.buffer_modulator_env[i] = _ctx.modulator_env;
            _ctx.buffer_carrier_env[i] = _ctx.carrier_env;
            i = (1 + i);
         }
      }
   }
   else
   {
      env_carrier_idle = synthFM_ADSR_process_bufferTo(_ctx.carrieradsr,(_ctx.gate || _ctx.sustaining),nb,_ctx.buffer_carrier_env);
      env_modulator_idle = synthFM_ADSR_process_bufferTo(_ctx.modulatoradsr,(_ctx.gate || _ctx.sustaining),nb,_ctx.buffer_modulator_env);
   }
   if(env_carrier_idle){
      synthFM_OSC_resetPhase(_ctx.carrier);
      if(env_modulator_idle){
         synthFM_OSC_resetPhase(_ctx.modulator);
         synthFM_OSC_setPhase(_ctx.modulator,_ctx.modulator_phase_shift);
      }
      int i;
      i = 0;
      while(i < nb){
         oBuffer[i] = 0x0 /* 0.000000 */;
         i = (1 + i);
      }
   }
   else
   {
      if(env_modulator_idle){
         synthFM_OSC_resetPhase(_ctx.modulator);
         synthFM_OSC_setPhase(_ctx.modulator,_ctx.modulator_phase_shift);
         int i;
         i = 0;
         while(i < nb){
            _ctx.buffer_modulator[i] = 0x0 /* 0.000000 */;
            i = (1 + i);
         }
      }
      else
      {
         if(_ctx.modulator_feedback != 0x0 /* 0.000000 */){
            synthFM_OSC_process_bufferTo_feedback(_ctx.modulator,wavetable_modulator,nb,_ctx.buffer_modulator_env,_ctx.modulator_feedback,_ctx.buffer_modulator);
         }
         else
         {
            synthFM_OSC_process_bufferTo_simple(_ctx.modulator,wavetable_modulator,nb,_ctx.buffer_modulator_env,_ctx.buffer_modulator);
         }
      }
      synthFM_OSC_process_bufferTo(_ctx.carrier,wavetable_carrier,nb,_ctx.buffer_carrier_env,_ctx.buffer_modulator,_ctx.buffer_modulator_env,_ctx.modulator_level,_ctx.modulator_target_level,oBuffer);
   }
}

void synthFM_FM_setSamplerate(synthFM_FM__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   synthFM_OSC_setSamplerate(_ctx.carrier,_ctx.fs);
   synthFM_OSC_setSamplerate(_ctx.modulator,_ctx.fs);
   fix16_t ADSR_fs;
   ADSR_fs = _ctx.fs;
   if(_ctx.env_decimation_factor > 0){
      ADSR_fs = fix_div(_ctx.fs,int_to_fix(_ctx.env_decimation_factor));
   }
   synthFM_ADSR_setSamplerate(_ctx.carrieradsr,ADSR_fs);
   synthFM_ADSR_setSamplerate(_ctx.modulatoradsr,ADSR_fs);
   synthFM_FM__updateLevelStep(_ctx);
}

void synthFM_FM_setLevel(synthFM_FM__ctx_type_0 &_ctx, fix16_t newLevel){
   _ctx.target_level = fix_clip(newLevel,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(_ctx.target_level < _ctx.level){
      _ctx.level_step = (- _ctx.level_step_ref);
   }
   else
   {
      _ctx.level_step = _ctx.level_step_ref;
   }
   if(fix_abs((_ctx.target_level + (- _ctx.level))) <= _ctx.level_step_ref){
      _ctx.level = _ctx.target_level;
   }
}

void synthFM_FM_setFrequency(synthFM_FM__ctx_type_0 &_ctx, fix16_t newFreq){
   if(newFreq >= 0x0 /* 0.000000 */){
      _ctx.freq = newFreq;
      fix16_t bendFreq;
      bendFreq = _ctx.freq;
      if(_ctx.bend != 0x0 /* 0.000000 */){
         bendFreq = fix_mul(_ctx.freq,synthFM_Util_tonesToCoeff(_ctx.bend));
      }
      if(_ctx.carrierRatio >= 0x0 /* 0.000000 */){
         synthFM_OSC_setFrequency(_ctx.carrier,fix_mul(_ctx.carrierRatio,bendFreq));
      }
      if(_ctx.modulatorRatio >= 0x0 /* 0.000000 */){
         synthFM_OSC_setFrequency(_ctx.modulator,fix_mul(_ctx.modulatorRatio,bendFreq));
      }
   }
}

void synthFM_FM_setSustain(synthFM_FM__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.sustain = flag;
   if(_ctx.gate && _ctx.sustain){
      _ctx.sustaining = true;
   }
   if(bool_not(_ctx.sustain)){
      _ctx.sustaining = false;
   }
}

uint8_t synthFM_FM_noteOn(synthFM_FM__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   uint8_t isNew;
   isNew = synthFM_Notes_noteOn(_ctx.playingnotes,note,velocity,channel);
   synthFM_FM_setFrequency(_ctx,synthFM_Util_noteToFrequency(note));
   synthFM_FM_setLevel(_ctx,synthFM_Util_velocityToLevel(velocity));
   _ctx.gate = true;
   if(_ctx.sustain){
      _ctx.sustaining = true;
   }
   if(synthFM_Notes_getPoly(_ctx.playingnotes)){
      synthFM_ADSR_retrig(_ctx.carrieradsr);
      synthFM_ADSR_retrig(_ctx.modulatoradsr);
   }
   return isNew;
}

void synthFM_FM_noteOff(synthFM_FM__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   if(synthFM_Notes_noteOff(_ctx.playingnotes,note,channel)){
      if(synthFM_Notes_nbNotes(_ctx.playingnotes) > 0){
         int last_played;
         last_played = synthFM_Notes_lastNote(_ctx.playingnotes);
         if((last_played > 0) && (last_played <= 128)){
            synthFM_FM_setFrequency(_ctx,synthFM_Util_noteToFrequency(((-1) + last_played)));
         }
      }
      else
      {
         _ctx.gate = false;
      }
   }
}

void synthFM_FM_default(synthFM_FM__ctx_type_0 &_ctx){
   synthFM_Buffer_buffer(_ctx.buffer_modulator);
   synthFM_Buffer_buffer(_ctx.buffer_carrier_env_short);
   synthFM_Buffer_buffer(_ctx.buffer_modulator_env_short);
   synthFM_Buffer_buffer(_ctx.buffer_carrier_env);
   synthFM_Buffer_buffer(_ctx.buffer_modulator_env);
   synthFM_FM_setEnvDecimationFactor(_ctx,3);
   synthFM_OSC_default(_ctx.carrier);
   synthFM_OSC_default(_ctx.modulator);
   synthFM_ADSR_default(_ctx.carrieradsr);
   synthFM_ADSR_default(_ctx.modulatoradsr);
   synthFM_FM_setModulatorADSR(_ctx,0x0 /* 0.000000 */,0x0 /* 0.000000 */,0x8000 /* 0.500000 */,0x0 /* 0.000000 */);
   synthFM_FM_setCarrierADSR(_ctx,0x0 /* 0.000000 */,0x0 /* 0.000000 */,0x8000 /* 0.500000 */,0x0 /* 0.000000 */);
   synthFM_FM_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   synthFM_FM_setCarrierRatio(_ctx,0x10000 /* 1.000000 */);
   synthFM_FM_setModulatorTargetLevel(_ctx,false);
   synthFM_FM_setModulatorRatio(_ctx,0x20000 /* 2.000000 */);
   synthFM_FM_setModulatorLevel(_ctx,0x1999 /* 0.100000 */);
   synthFM_FM_setLevel(_ctx,0x10000 /* 1.000000 */);
   synthFM_FM_setFrequency(_ctx,0x70a3 /* 0.440000 */);
   synthFM_Notes_default(_ctx.playingnotes);
   synthFM_Notes_setAllowDuplicates(_ctx.playingnotes,true);
   synthFM_FM_setPoly(_ctx,false);
}

void synthFM_Poly__ctx_type_0_init(synthFM_Poly__ctx_type_0 &_output_){
   synthFM_Poly__ctx_type_0 &_ctx = _output_;
   ;
   ;
   synthFM_FM__ctx_type_0_init(_ctx.voice3);
   synthFM_FM__ctx_type_0_init(_ctx.voice2);
   synthFM_FM__ctx_type_0_init(_ctx.voice1);
   synthFM_FM__ctx_type_0_init(_ctx.voice0);
   _ctx.should_leftovers = false;
   _ctx.lastModulatorWavetablePhaseIdx = 0x0 /* 0.000000 */;
   _ctx.lastModulatorWavetableIdx = 0x0 /* 0.000000 */;
   _ctx.lastCarrierWavetablePhaseIdx = 0x0 /* 0.000000 */;
   _ctx.lastCarrierWavetableIdx = 0x0 /* 0.000000 */;
   _ctx.initModulatorWavetable = false;
   _ctx.initCarrierWavetable = false;
   synthFM_Poly_default(_ctx);
   
   return ;
}

fix16_t synthFM_Poly_getSample(synthFM_Poly__ctx_type_0 &_ctx, int voice){
   switch(voice) {
      case 0:
         return synthFM_FM_process(_ctx.voice0,_ctx.wavetable_modulator,_ctx.wavetable_carrier);
      break;
      case 1:
         return synthFM_FM_process(_ctx.voice1,_ctx.wavetable_modulator,_ctx.wavetable_carrier);
      break;
      case 2:
         return synthFM_FM_process(_ctx.voice2,_ctx.wavetable_modulator,_ctx.wavetable_carrier);
      break;
      case 3:
         return synthFM_FM_process(_ctx.voice3,_ctx.wavetable_modulator,_ctx.wavetable_carrier);
      break;
    
   }
   return 0x0 /* 0.000000 */;
}

void synthFM_Poly_default(synthFM_Poly__ctx_type_0 &_ctx){
   _ctx.should_leftovers = false;
   synthFM_Wavetable_bufferWavetable(_ctx.wavetable_modulator);
   synthFM_Wavetable_bufferWavetable(_ctx.wavetable_carrier);
   _ctx.initModulatorWavetable = false;
   _ctx.initCarrierWavetable = false;
   synthFM_Poly_synthSetModulatorWavetable(_ctx,0x0 /* 0.000000 */);
   synthFM_Poly_synthSetCarrierWavetable(_ctx,0x0 /* 0.000000 */);
   synthFM_FM_default(_ctx.voice0);
   synthFM_FM_setPoly(_ctx.voice0,true);
   synthFM_FM_default(_ctx.voice1);
   synthFM_FM_setPoly(_ctx.voice1,true);
   synthFM_FM_default(_ctx.voice2);
   synthFM_FM_setPoly(_ctx.voice2,true);
   synthFM_FM_default(_ctx.voice3);
   synthFM_FM_setPoly(_ctx.voice3,true);
}

void synthFM_Voice__ctx_type_0_init(synthFM_Voice__ctx_type_0 &_output_){
   synthFM_Voice__ctx_type_0 &_ctx = _output_;
   synthFM_Notes__ctx_type_0_init(_ctx.voicesinactive);
   synthFM_Notes__ctx_type_0_init(_ctx.voicesactive);
   _ctx.voices_ratio = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.voices);
   synthFM_Notes__ctx_type_0_init(_ctx.voiceinsactive);
   _ctx.reuse = false;
   synthFM_Poly__ctx_type_0_init(_ctx.poly);
   _ctx.number_voices = 0;
   int_init_array(128,0,_ctx.notes);
   _ctx.normalize = false;
   _ctx.leftovers_decay = 0x0 /* 0.000000 */;
   _ctx.leftovers = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.last_velocities);
   fix_init_array(4,0x0 /* 0.000000 */,_ctx.last_values);
   _ctx.fs = 0x0 /* 0.000000 */;
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.buffer_v0);
   synthFM_Voice_default(_ctx);
   
   return ;
}

fix16_t synthFM_Voice_process(synthFM_Voice__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   while(i < _ctx.number_voices){
      _ctx.last_values[i] = synthFM_Poly_getSample(_ctx.poly,i);
      value = (value + _ctx.last_values[i]);
      i = (1 + i);
   }
   if(_ctx.leftovers != 0x0 /* 0.000000 */){
      _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
      value = (_ctx.leftovers + value);
   }
   if(_ctx.normalize){
      return fix_mul(_ctx.voices_ratio,value);
   }
   return value;
}

void synthFM_Voice_process_bufferTo(synthFM_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[128]){
   nb = int_clip(nb,0,128);
   if(nb == 0){
      nb = 128;
   }
   int v;
   v = 0;
   int i;
   i = 0;
   if(v < _ctx.number_voices){
      synthFM_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
      i = 0;
      while(i < nb){
         oBuffer[i] = _ctx.buffer_v0[i];
         i = (1 + i);
      }
      if(nb > 0){
         _ctx.last_values[v] = _ctx.buffer_v0[((-1) + nb)];
      }
      v = (1 + v);
   }
   while(v < _ctx.number_voices){
      synthFM_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
      i = 0;
      while(i < nb){
         oBuffer[i] = (_ctx.buffer_v0[i] + oBuffer[i]);
         i = (1 + i);
      }
      if(nb > 0){
         _ctx.last_values[v] = _ctx.buffer_v0[((-1) + nb)];
      }
      v = (1 + v);
   }
   i = 0;
   while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
      _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
      oBuffer[i] = (_ctx.leftovers + oBuffer[i]);
      i = (1 + i);
   }
   if(_ctx.normalize){
      i = 0;
      while(i < nb){
         oBuffer[i] = fix_mul(_ctx.voices_ratio,oBuffer[i]);
         i = (1 + i);
      }
   }
}

void synthFM_Voice_noteOff(synthFM_Voice__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= 4)){
      if(synthFM_Notes_noteOff(_ctx.voicesactive,((-1) + v),0)){
         synthFM_Poly_sendNoteOff(_ctx.poly,((-1) + v),note,channel);
         _ctx.notes[note] = (- v);
         _ctx.voices[((-1) + v)] = (- (1 + note));
         if(v <= _ctx.number_voices){
            synthFM_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0);
         }
      }
   }
}

void synthFM_Voice_noteOn(synthFM_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   velocity = int_clip(velocity,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= _ctx.number_voices)){
      if(bool_not((synthFM_Notes_noteOff(_ctx.voicesactive,((-1) + v),0) && synthFM_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0) && synthFM_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthFM_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
         _ctx.notes[note] = 0;
         _ctx.voices[((-1) + v)] = 0;
         v = 0;
      }
   }
   else
   {
      if(_ctx.reuse && (v < 0) && ((- v) <= _ctx.number_voices) && (_ctx.voices[((-1) + (- v))] == (- (1 + note))) && (_ctx.notes[note] == v)){
         v = (- v);
         if(bool_not((synthFM_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthFM_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
            _ctx.notes[note] = 0;
            _ctx.voices[((-1) + v)] = 0;
            v = 0;
         }
      }
      else
      {
         v = synthFM_Notes_firstNote(_ctx.voicesinactive);
         if((v <= 0) || (v > _ctx.number_voices)){
            int active_v;
            active_v = synthFM_Notes_firstNote(_ctx.voicesactive);
            if(active_v > 0){
               synthFM_Voice_noteOff(_ctx,_ctx.voices[((-1) + active_v)],0);
            }
         }
         v = synthFM_Notes_firstNote(_ctx.voicesinactive);
         if((v > 0) && (v <= _ctx.number_voices)){
            if(bool_not((synthFM_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthFM_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
               v = 0;
            }
         }
         else
         {
            v = 0;
         }
      }
   }
   if(v > 0){
      if(synthFM_Poly_shouldLeftOvers(_ctx.poly)){
         _ctx.leftovers = (_ctx.leftovers + _ctx.last_values[((-1) + v)]);
      }
      synthFM_Poly_sendNoteOn(_ctx.poly,((-1) + v),note,velocity,channel);
      _ctx.notes[note] = v;
      _ctx.voices[((-1) + v)] = note;
      _ctx.last_velocities[((-1) + v)] = velocity;
   }
}

void synthFM_Voice_setNbVoices(synthFM_Voice__ctx_type_0 &_ctx, int nbvoices){
   nbvoices = int_clip(nbvoices,0,4);
   int i;
   i = synthFM_Notes_nbNotes(_ctx.voicesactive);
   while((i > nbvoices) && (i > 0)){
      synthFM_Voice_noteOff(_ctx,_ctx.voices[((-1) + i)],0);
      synthFM_Notes_noteOff(_ctx.voicesinactive,((-1) + i),0);
      i = ((-1) + i);
   }
   i = synthFM_Notes_nbNotes(_ctx.voicesinactive);
   if(i < nbvoices){
      while(i < nbvoices){
         synthFM_Notes_noteOn(_ctx.voicesinactive,i,127,0);
         i = (1 + i);
      }
   }
   else
   {
      while(i >= nbvoices){
         synthFM_Notes_noteOff(_ctx.voicesinactive,i,0);
         i = ((-1) + i);
      }
   }
   _ctx.number_voices = nbvoices;
   if(_ctx.number_voices > 0){
      _ctx.voices_ratio = fix_div(0x10000 /* 1.000000 */,int_to_fix(_ctx.number_voices));
   }
}

void synthFM_Voice_setSamplerate(synthFM_Voice__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   synthFM_Poly_setSamplerate(_ctx.poly,_ctx.fs);
   fix16_t log_base;
   log_base = 0x24d76 /* 2.302585 */;
   _ctx.leftovers_decay = fix_exp(fix_div(fix_mul(-0xc4 /* -0.003000 */,log_base),fix_mul(0x3333 /* 0.200000 */,_ctx.fs)));
}

void synthFM_Voice_default(synthFM_Voice__ctx_type_0 &_ctx){
   synthFM_Poly_default(_ctx.poly);
   synthFM_Buffer_buffer(_ctx.buffer_v0);
   if(_ctx.number_voices == 0){
      _ctx.number_voices = 4;
   }
   synthFM_Voice_setNbVoices(_ctx,_ctx.number_voices);
   synthFM_Notes_default(_ctx.voicesactive);
   synthFM_Notes_setPoly(_ctx.voicesactive,false);
   synthFM_Notes_setAllowDuplicates(_ctx.voicesactive,false);
   synthFM_Notes_default(_ctx.voicesinactive);
   synthFM_Notes_setPoly(_ctx.voicesinactive,false);
   synthFM_Notes_setAllowDuplicates(_ctx.voiceinsactive,false);
   synthFM_Voice_setNormalize(_ctx,true);
   synthFM_Voice_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   synthFM_Voice_setReuse(_ctx,false);
}


