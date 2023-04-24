
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "synthDrummerBbox.h"

void synthDrummerBbox_DrummerWrapper_getSlicesStart(int (&_output_)[12]){
   int _array_1[12];
   {
      _array_1[0] = 0;
      _array_1[1] = 3000;
      _array_1[2] = 11260;
      _array_1[3] = 22200;
      _array_1[4] = 29400;
      _array_1[5] = 38250;
      _array_1[6] = 47700;
      _array_1[7] = 51500;
      _array_1[8] = 55300;
      _array_1[9] = 63270;
      _array_1[10] = 72470;
      _array_1[11] = 79210;
   }
   int_copy_array(12,_output_,_array_1);
   return ;
}

void synthDrummerBbox_DrummerWrapper_getSlicesEnd(int (&_output_)[12]){
   int _array_1[12];
   {
      _array_1[0] = 2750;
      _array_1[1] = 11150;
      _array_1[2] = 22000;
      _array_1[3] = 29100;
      _array_1[4] = 38100;
      _array_1[5] = 47000;
      _array_1[6] = 51300;
      _array_1[7] = 55100;
      _array_1[8] = 63256;
      _array_1[9] = 72465;
      _array_1[10] = 79200;
      _array_1[11] = 86200;
   }
   int_copy_array(12,_output_,_array_1);
   return ;
}

void synthDrummerBbox_Drummer__ctx_type_0_init(synthDrummerBbox_Drummer__ctx_type_0 &_output_){
   synthDrummerBbox_Drummer__ctx_type_0 &_ctx = _output_;
   _ctx.step = 0x0 /* 0.000000 */;
   int_init_array(12,0,_ctx.slices_start);
   int_init_array(12,0,_ctx.slices_end);
   _ctx.slice = 0;
   _ctx.size = 0;
   _ctx.sampleFs = 0x0 /* 0.000000 */;
   _ctx.posBase = 0;
   _ctx.pos = 0x0 /* 0.000000 */;
   _ctx.noteRatio = 0x0 /* 0.000000 */;
   _ctx.level = 0x0 /* 0.000000 */;
   _ctx.fsRatio = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_o);
   synthDrummerBbox_Drummer_default(_ctx);
   
   return ;
}

fix16_t synthDrummerBbox_Drummer_process(synthDrummerBbox_Drummer__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   if((_ctx.slice >= 0) && (_ctx.slice <= 12)){
      _ctx.pos = (_ctx.pos + _ctx.step);
      while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
         _ctx.posBase = (1024 + _ctx.posBase);
         _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
      }
      int idx;
      idx = (_ctx.posBase + fix_to_int(_ctx.pos));
      if(idx >= _ctx.size){
         _ctx.slice = (-1);
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
      }
      if(idx >= _ctx.slices_end[_ctx.slice]){
         _ctx.slice = (-1);
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
      }
      else
      {
         value = fix_mul(_ctx.level,(synthDrummerBbox_DrummerWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthDrummerBbox_DrummerWrapper_getSample((1 + idx)) + (- synthDrummerBbox_DrummerWrapper_getSample(idx))))));
      }
   }
   return value;
}

void synthDrummerBbox_Drummer_process_bufferTo(synthDrummerBbox_Drummer__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   fix16_t value;
   int i;
   i = 0;
   while(i < nb){
      value = 0x0 /* 0.000000 */;
      if((_ctx.slice >= 0) && (_ctx.slice <= 12)){
         _ctx.pos = (_ctx.pos + _ctx.step);
         while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
            _ctx.posBase = (1024 + _ctx.posBase);
            _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
         }
         int idx;
         idx = (_ctx.posBase + fix_to_int(_ctx.pos));
         if(idx >= _ctx.size){
            _ctx.slice = (-1);
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
         }
         if(idx >= _ctx.slices_end[_ctx.slice]){
            _ctx.slice = (-1);
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
         }
         else
         {
            value = fix_mul(_ctx.level,(synthDrummerBbox_DrummerWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthDrummerBbox_DrummerWrapper_getSample((1 + idx)) + (- synthDrummerBbox_DrummerWrapper_getSample(idx))))));
         }
      }
      oBuffer[i] = value;
      i = (1 + i);
   }
}

void synthDrummerBbox_Drummer_setSlices(synthDrummerBbox_Drummer__ctx_type_0 &_ctx, int (&newSlicesStart)[12], int (&newSlicesEnd)[12]){
   if((12 == 12) && (12 == 12) && (12 == 12)){
      int i;
      i = 0;
      int s;
      int e;
      while(i < 12){
         s = int_clip(newSlicesStart[i],0,((-1) + _ctx.size));
         e = int_clip(newSlicesEnd[i],0,((-1) + _ctx.size));
         if(s <= e){
            _ctx.slices_start[i] = s;
            _ctx.slices_end[i] = e;
         }
         i = (1 + i);
      }
   }
}

void synthDrummerBbox_Drummer_setSamplerate(synthDrummerBbox_Drummer__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.fsRatio = fix_div(_ctx.sampleFs,_ctx.fs);
   }
   synthDrummerBbox_Drummer_updateStep(_ctx);
}

void synthDrummerBbox_Drummer_noteOn(synthDrummerBbox_Drummer__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   int root;
   root = 60;
   _ctx.slice = (note % 12);
   if((_ctx.slice >= 0) && (_ctx.slice < 12)){
      _ctx.posBase = _ctx.slices_start[_ctx.slice];
      _ctx.pos = 0x0 /* 0.000000 */;
   }
   int slice_root;
   slice_root = (note + (- _ctx.slice));
   fix16_t log_two;
   log_two = 0xb172 /* 0.693147 */;
   fix16_t octave;
   octave = fix_mul(0x1555 /* 0.083333 */,int_to_fix((slice_root + (- root))));
   _ctx.noteRatio = fix_exp(fix_mul(log_two,octave));
   synthDrummerBbox_Drummer_updateStep(_ctx);
   synthDrummerBbox_Drummer_setLevel(_ctx,synthDrummerBbox_Util_velocityToLevel(velocity));
}

void synthDrummerBbox_Drummer_default(synthDrummerBbox_Drummer__ctx_type_0 &_ctx){
   _ctx.size = synthDrummerBbox_DrummerWrapper_getSampleSize();
   synthDrummerBbox_Drummer_setLevel(_ctx,0x10000 /* 1.000000 */);
   _ctx.sampleFs = 0x1e0000 /* 30.000000 */;
   synthDrummerBbox_Drummer_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   synthDrummerBbox_Drummer_setSlices(_ctx,{0,3000,11260,22200,29400,38250,47700,51500,55300,63270,72470,79210
   },{2750,11150,22000,29100,38100,47000,51300,55100,63256,72465,79200,86200
   });
   synthDrummerBbox_Buffer_buffer(_ctx.buffer_o);
   _ctx.slice = (-1);
}

void synthDrummerBbox_Poly__ctx_type_0_init(synthDrummerBbox_Poly__ctx_type_0 &_output_){
   synthDrummerBbox_Poly__ctx_type_0 &_ctx = _output_;
   synthDrummerBbox_Drummer__ctx_type_0_init(_ctx.voice3);
   synthDrummerBbox_Drummer__ctx_type_0_init(_ctx.voice2);
   synthDrummerBbox_Drummer__ctx_type_0_init(_ctx.voice1);
   synthDrummerBbox_Drummer__ctx_type_0_init(_ctx.voice0);
   _ctx.should_leftovers = false;
   synthDrummerBbox_Poly_default(_ctx);
   
   return ;
}

fix16_t synthDrummerBbox_Poly_getSample(synthDrummerBbox_Poly__ctx_type_0 &_ctx, int voice){
   switch(voice) {
      case 0:
         return synthDrummerBbox_Drummer_process(_ctx.voice0);
      break;
      case 1:
         return synthDrummerBbox_Drummer_process(_ctx.voice1);
      break;
      case 2:
         return synthDrummerBbox_Drummer_process(_ctx.voice2);
      break;
      case 3:
         return synthDrummerBbox_Drummer_process(_ctx.voice3);
      break;
    
   }
   return 0x0 /* 0.000000 */;
}

void synthDrummerBbox_Poly_default(synthDrummerBbox_Poly__ctx_type_0 &_ctx){
   _ctx.should_leftovers = true;
   synthDrummerBbox_Drummer_default(_ctx.voice0);
   synthDrummerBbox_Drummer_default(_ctx.voice1);
   synthDrummerBbox_Drummer_default(_ctx.voice2);
   synthDrummerBbox_Drummer_default(_ctx.voice3);
}

void synthDrummerBbox_Notes__ctx_type_0_init(synthDrummerBbox_Notes__ctx_type_0 &_output_){
   synthDrummerBbox_Notes__ctx_type_0 &_ctx = _output_;
   _ctx.poly = false;
   int_init_array(128,0,_ctx.notes);
   _ctx.nb_notes = 0;
   int_init_array(128,0,_ctx.last_notes);
   synthDrummerBbox_Notes_default(_ctx);
   
   return ;
}

int synthDrummerBbox_Notes_firstNote(synthDrummerBbox_Notes__ctx_type_0 &_ctx){
   int first_played;
   first_played = 0;
   if(_ctx.nb_notes > 0){
      first_played = _ctx.last_notes[0];
   }
   return first_played;
}

int synthDrummerBbox_Notes_lastNote(synthDrummerBbox_Notes__ctx_type_0 &_ctx){
   int last_played;
   last_played = 0;
   if(_ctx.nb_notes > 0){
      last_played = _ctx.last_notes[((-1) + _ctx.nb_notes)];
   }
   return last_played;
}

uint8_t synthDrummerBbox_Notes_noteOn(synthDrummerBbox_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   if(_ctx.notes[note] <= 0){
      if(bool_not(_ctx.poly)){
         _ctx.nb_notes = (1 + _ctx.nb_notes);
         if(_ctx.nb_notes > 128){
            _ctx.nb_notes = 128;
         }
      }
      else
      {
         int last_note;
         last_note = synthDrummerBbox_Notes_lastNote(_ctx);
         if(last_note > 0){
            _ctx.notes[((-1) + last_note)] = 0;
         }
         _ctx.nb_notes = 1;
      }
      _ctx.notes[note] = _ctx.nb_notes;
      _ctx.last_notes[((-1) + _ctx.nb_notes)] = (1 + note);
      return true;
   }
   return false;
}

uint8_t synthDrummerBbox_Notes_noteOff(synthDrummerBbox_Notes__ctx_type_0 &_ctx, int note, int channel){
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

void synthDrummerBbox_Voice__ctx_type_0_init(synthDrummerBbox_Voice__ctx_type_0 &_output_){
   synthDrummerBbox_Voice__ctx_type_0 &_ctx = _output_;
   synthDrummerBbox_Notes__ctx_type_0_init(_ctx.voicesinactive);
   synthDrummerBbox_Notes__ctx_type_0_init(_ctx.voicesactive);
   _ctx.voices_ratio = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.voices);
   synthDrummerBbox_Poly__ctx_type_0_init(_ctx.poly);
   _ctx.number_voices = 0;
   int_init_array(128,0,_ctx.notes);
   _ctx.normalize = false;
   _ctx.leftovers_decay = 0x0 /* 0.000000 */;
   _ctx.leftovers = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.last_velocities);
   fix_init_array(4,0x0 /* 0.000000 */,_ctx.last_values);
   _ctx.fs = 0x0 /* 0.000000 */;
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v3);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v2);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v1);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v0);
   synthDrummerBbox_Voice_default(_ctx);
   
   return ;
}

fix16_t synthDrummerBbox_Voice_process(synthDrummerBbox_Voice__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   while(i < _ctx.number_voices){
      _ctx.last_values[i] = synthDrummerBbox_Poly_getSample(_ctx.poly,i);
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

void synthDrummerBbox_Voice_process_bufferTo(synthDrummerBbox_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   int v;
   v = 0;
   int i;
   i = 0;
   if(v < _ctx.number_voices){
      synthDrummerBbox_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
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
      synthDrummerBbox_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
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

void synthDrummerBbox_Voice_process_bufferTo_alt(synthDrummerBbox_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   synthDrummerBbox_Poly_runVoice(_ctx.poly,0,nb,_ctx.buffer_v0);
   synthDrummerBbox_Poly_runVoice(_ctx.poly,1,nb,_ctx.buffer_v1);
   synthDrummerBbox_Poly_runVoice(_ctx.poly,2,nb,_ctx.buffer_v2);
   synthDrummerBbox_Poly_runVoice(_ctx.poly,3,nb,_ctx.buffer_v3);
   if(nb > 0){
      _ctx.last_values[0] = _ctx.buffer_v0[((-1) + nb)];
      _ctx.last_values[1] = _ctx.buffer_v1[((-1) + nb)];
      _ctx.last_values[2] = _ctx.buffer_v2[((-1) + nb)];
      _ctx.last_values[3] = _ctx.buffer_v3[((-1) + nb)];
   }
   int i;
   i = 0;
   if(_ctx.normalize){
      while(i < nb){
         oBuffer[i] = fix_mul(_ctx.voices_ratio,(_ctx.buffer_v0[i] + _ctx.buffer_v1[i] + _ctx.buffer_v2[i] + _ctx.buffer_v3[i]));
         i = (1 + i);
      }
      i = 0;
      while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
         _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
         oBuffer[i] = (oBuffer[i] + fix_mul(_ctx.leftovers,_ctx.voices_ratio));
         i = (1 + i);
      }
   }
   else
   {
      while(i < nb){
         oBuffer[i] = (_ctx.buffer_v0[i] + _ctx.buffer_v1[i] + _ctx.buffer_v2[i] + _ctx.buffer_v3[i]);
         i = (1 + i);
      }
      i = 0;
      while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
         _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
         oBuffer[i] = (_ctx.leftovers + oBuffer[i]);
         i = (1 + i);
      }
   }
}

void synthDrummerBbox_Voice_noteOff(synthDrummerBbox_Voice__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= 4)){
      if(synthDrummerBbox_Notes_noteOff(_ctx.voicesactive,((-1) + v),0)){
         synthDrummerBbox_Poly_sendNoteOff(_ctx.poly,((-1) + v),note,channel);
         _ctx.notes[note] = 0;
         _ctx.voices[((-1) + v)] = 0;
         if(v <= _ctx.number_voices){
            synthDrummerBbox_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0);
         }
      }
   }
}

void synthDrummerBbox_Voice_noteOn(synthDrummerBbox_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   velocity = int_clip(velocity,0,127);
   if(_ctx.notes[note] <= 0){
      int v;
      v = synthDrummerBbox_Notes_firstNote(_ctx.voicesinactive);
      if((v <= 0) || (v > _ctx.number_voices)){
         int active_v;
         active_v = synthDrummerBbox_Notes_firstNote(_ctx.voicesactive);
         if(active_v > 0){
            synthDrummerBbox_Voice_noteOff(_ctx,_ctx.voices[((-1) + active_v)],0);
         }
      }
      v = synthDrummerBbox_Notes_firstNote(_ctx.voicesinactive);
      if((v > 0) && (v <= _ctx.number_voices)){
         if(synthDrummerBbox_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthDrummerBbox_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)){
            if(synthDrummerBbox_Poly_shouldLeftOvers(_ctx.poly)){
               _ctx.leftovers = (_ctx.leftovers + _ctx.last_values[((-1) + v)]);
            }
            else
            {
               int diff_velocity;
               diff_velocity = (_ctx.last_velocities[((-1) + v)] + (- velocity));
               fix16_t diff_level;
               diff_level = 0x0 /* 0.000000 */;
               if(diff_velocity > 0){
                  diff_level = fix_mul(0x204 /* 0.007874 */,int_to_fix(diff_velocity));
               }
               _ctx.leftovers = (_ctx.leftovers + fix_mul(diff_level,_ctx.last_values[((-1) + v)]));
            }
            synthDrummerBbox_Poly_sendNoteOn(_ctx.poly,((-1) + v),note,velocity,channel);
            _ctx.notes[note] = v;
            _ctx.voices[((-1) + v)] = note;
            _ctx.last_velocities[((-1) + v)] = velocity;
         }
      }
   }
}

void synthDrummerBbox_Voice_setNbVoices(synthDrummerBbox_Voice__ctx_type_0 &_ctx, int nbvoices){
   nbvoices = int_clip(nbvoices,0,4);
   int i;
   i = synthDrummerBbox_Notes_nbNotes(_ctx.voicesactive);
   while((i > nbvoices) && (i > 0)){
      synthDrummerBbox_Voice_noteOff(_ctx,_ctx.voices[((-1) + i)],0);
      synthDrummerBbox_Notes_noteOff(_ctx.voicesinactive,((-1) + i),0);
      i = ((-1) + i);
   }
   i = synthDrummerBbox_Notes_nbNotes(_ctx.voicesinactive);
   if(i < nbvoices){
      while(i < nbvoices){
         synthDrummerBbox_Notes_noteOn(_ctx.voicesinactive,i,127,0);
         i = (1 + i);
      }
   }
   else
   {
      while(i >= nbvoices){
         synthDrummerBbox_Notes_noteOff(_ctx.voicesinactive,i,0);
         i = ((-1) + i);
      }
   }
   _ctx.number_voices = nbvoices;
   if(_ctx.number_voices > 0){
      _ctx.voices_ratio = fix_div(0x10000 /* 1.000000 */,int_to_fix(_ctx.number_voices));
   }
}

void synthDrummerBbox_Voice_setSamplerate(synthDrummerBbox_Voice__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   synthDrummerBbox_Poly_setSamplerate(_ctx.poly,_ctx.fs);
   fix16_t log_base;
   log_base = 0x24d76 /* 2.302585 */;
   _ctx.leftovers_decay = fix_exp(fix_div(fix_mul(-0xc4 /* -0.003000 */,log_base),fix_mul(0x3333 /* 0.200000 */,_ctx.fs)));
}

void synthDrummerBbox_Voice_default(synthDrummerBbox_Voice__ctx_type_0 &_ctx){
   synthDrummerBbox_Poly_default(_ctx.poly);
   synthDrummerBbox_Buffer_buffer(_ctx.buffer_v0);
   synthDrummerBbox_Buffer_buffer(_ctx.buffer_v1);
   synthDrummerBbox_Buffer_buffer(_ctx.buffer_v2);
   synthDrummerBbox_Buffer_buffer(_ctx.buffer_v3);
   if(_ctx.number_voices == 0){
      _ctx.number_voices = 4;
   }
   synthDrummerBbox_Voice_setNbVoices(_ctx,_ctx.number_voices);
   synthDrummerBbox_Notes_default(_ctx.voicesactive);
   synthDrummerBbox_Notes_setPoly(_ctx.voicesactive,false);
   synthDrummerBbox_Notes_default(_ctx.voicesinactive);
   synthDrummerBbox_Notes_setPoly(_ctx.voicesinactive,false);
   synthDrummerBbox_Voice_setNormalize(_ctx,true);
   synthDrummerBbox_Voice_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}

void synthDrummerBbox_Voice__ctx_type_1_init(synthDrummerBbox_Voice__ctx_type_1 &_output_){
   synthDrummerBbox_Voice__ctx_type_1 &_ctx = _output_;
   synthDrummerBbox_Voice__ctx_type_0_init(_ctx._inst275);
   synthDrummerBbox_Voice__ctx_type_0_init(_ctx._inst1b9);
   
   return ;
}


