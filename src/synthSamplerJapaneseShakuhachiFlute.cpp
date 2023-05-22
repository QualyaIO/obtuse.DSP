
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "synthSamplerJapaneseShakuhachiFlute.h"

void synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0_init(synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_output_){
   synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_ctx = _output_;
   _ctx.poly = false;
   int_init_array(128,0,_ctx.notes);
   _ctx.nb_notes = 0;
   int_init_array(128,0,_ctx.last_notes);
   _ctx.allowDuplicates = false;
   synthSamplerJapaneseShakuhachiFlute_Notes_default(_ctx);
   
   return ;
}

int synthSamplerJapaneseShakuhachiFlute_Notes_firstNote(synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_ctx){
   int first_played;
   first_played = 0;
   if(_ctx.nb_notes > 0){
      first_played = _ctx.last_notes[0];
   }
   return first_played;
}

int synthSamplerJapaneseShakuhachiFlute_Notes_lastNote(synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_ctx){
   int last_played;
   last_played = 0;
   if(_ctx.nb_notes > 0){
      last_played = _ctx.last_notes[((-1) + _ctx.nb_notes)];
   }
   return last_played;
}

uint8_t synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_ctx, int note, int channel){
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

uint8_t synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   uint8_t isNew;
   isNew = (_ctx.notes[note] <= 0);
   if(_ctx.allowDuplicates || isNew){
      if(bool_not(_ctx.poly)){
         if(bool_not(isNew)){
            synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx,note,channel);
         }
         _ctx.nb_notes = (1 + _ctx.nb_notes);
         if(_ctx.nb_notes > 128){
            _ctx.nb_notes = 128;
         }
      }
      else
      {
         int last_note;
         last_note = synthSamplerJapaneseShakuhachiFlute_Notes_lastNote(_ctx);
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

void synthSamplerJapaneseShakuhachiFlute_Buffer_buffer_large(fix16_t (&oBuff)[2048]){
   int i;
   i = 0;
   while(i < 2048){
      oBuff[i] = 0x0 /* 0.000000 */;
      i = (1 + i);
   }
}

void synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0_init(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_output_){
   synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx = _output_;
   _ctx.sustaining = false;
   _ctx.sustain = false;
   _ctx.step = 0x0 /* 0.000000 */;
   _ctx.state = 0;
   _ctx.size = 0;
   _ctx.sampleNote = 0;
   _ctx.sampleFs = 0x0 /* 0.000000 */;
   _ctx.quickKill = false;
   _ctx.qkStep = 0x0 /* 0.000000 */;
   _ctx.posBase = 0;
   _ctx.pos = 0x0 /* 0.000000 */;
   synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0_init(_ctx.playingnotes);
   _ctx.noteRatio = 0x0 /* 0.000000 */;
   _ctx.nextVelocity = 0;
   _ctx.nextNote = 0;
   _ctx.loopy = false;
   _ctx.loopS = 0;
   _ctx.loopE = 0;
   _ctx.level = 0x0 /* 0.000000 */;
   _ctx.gate = false;
   _ctx.fsRatio = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   _ctx.crossfade = false;
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_o);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_cross);
   _ctx.bend = 0x0 /* 0.000000 */;
   synthSamplerJapaneseShakuhachiFlute_Sampler_default(_ctx);
   
   return ;
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, int note){
   fix16_t log_two;
   log_two = 0xb172 /* 0.693147 */;
   fix16_t semitones;
   semitones = fix_mul(0x1555 /* 0.083333 */,int_to_fix((note + (- _ctx.sampleNote))));
   _ctx.noteRatio = fix_exp(fix_mul(log_two,semitones));
   synthSamplerJapaneseShakuhachiFlute_Sampler_updateStep(_ctx);
}

fix16_t synthSamplerJapaneseShakuhachiFlute_Sampler_process(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   if(_ctx.state > 0){
      _ctx.pos = (_ctx.pos + _ctx.step);
      while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
         _ctx.posBase = (1024 + _ctx.posBase);
         _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
      }
      int idx;
      idx = (_ctx.posBase + fix_to_int(_ctx.pos));
      if(idx >= _ctx.size){
         _ctx.state = 0;
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
      }
      else
      {
         if((_ctx.state == 1) && bool_not(_ctx.quickKill) && (_ctx.gate || _ctx.sustaining) && _ctx.loopy && _ctx.crossfade && (idx >= (_ctx.loopE + (- (256 / 2)))) && (idx <= (_ctx.loopE + (256 / 2)))){
            _ctx.state = 2;
            idx = (idx + (- _ctx.loopE) + (256 / 2));
            _ctx.posBase = idx;
            _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
         }
         else
         {
            if((_ctx.state == 1) && bool_not(_ctx.quickKill) && (_ctx.gate || _ctx.sustaining) && _ctx.loopy && (idx >= _ctx.loopE)){
               idx = (_ctx.loopS + idx + (- _ctx.loopE));
               _ctx.posBase = idx;
               _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
            }
         }
         if((_ctx.state == 2) && (idx >= 255)){
            idx = (_ctx.loopS + idx + (- (256 / 2)));
            _ctx.posBase = idx;
            _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
            if(_ctx.gate || _ctx.sustaining){
               _ctx.state = 1;
            }
            else
            {
               _ctx.state = 3;
            }
         }
         if(_ctx.quickKill){
            _ctx.level = (_ctx.level + (- _ctx.qkStep));
            if(_ctx.level < 0x0 /* 0.000000 */){
               _ctx.level = 0x0 /* 0.000000 */;
            }
         }
         if(_ctx.state == 2){
            value = fix_mul(_ctx.level,(_ctx.buffer_cross[idx] + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(_ctx.buffer_cross[(1 + idx)] + (- _ctx.buffer_cross[idx])))));
         }
         else
         {
            value = fix_mul(_ctx.level,(synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample((1 + idx)) + (- synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample(idx))))));
         }
      }
      if(_ctx.quickKill && ((_ctx.level <= 0x0 /* 0.000000 */) || (_ctx.state <= 0))){
         _ctx.quickKill = false;
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
         _ctx.state = 1;
         synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(_ctx,_ctx.nextNote);
         synthSamplerJapaneseShakuhachiFlute_Sampler_setLevel(_ctx,synthSamplerJapaneseShakuhachiFlute_Util_velocityToLevel(_ctx.nextVelocity));
      }
   }
   return value;
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_process_bufferTo(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   int idx;
   idx = 0;
   int i;
   i = 0;
   while(i < nb){
      if(_ctx.state > 0){
         _ctx.pos = (_ctx.pos + _ctx.step);
         while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
            _ctx.posBase = (1024 + _ctx.posBase);
            _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
         }
         idx = (_ctx.posBase + fix_to_int(_ctx.pos));
         if(idx > _ctx.size){
            _ctx.state = 0;
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
            oBuffer[i] = 0x0 /* 0.000000 */;
         }
         else
         {
            if((_ctx.state == 1) && bool_not(_ctx.quickKill) && (_ctx.gate || _ctx.sustaining) && _ctx.loopy && _ctx.crossfade && (idx >= (_ctx.loopE + (- (256 / 2)))) && (idx <= (_ctx.loopE + (256 / 2)))){
               _ctx.state = 2;
               idx = (idx + (- _ctx.loopE) + (256 / 2));
               _ctx.posBase = idx;
               _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
            }
            else
            {
               if((_ctx.state == 1) && bool_not(_ctx.quickKill) && (_ctx.gate || _ctx.sustaining) && _ctx.loopy && (idx >= _ctx.loopE)){
                  idx = (_ctx.loopS + idx + (- _ctx.loopE));
                  _ctx.posBase = idx;
                  _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
               }
            }
            if((_ctx.state == 2) && (idx >= 255)){
               idx = (_ctx.loopS + idx + (- (256 / 2)));
               _ctx.posBase = idx;
               _ctx.pos = (_ctx.pos % 0x10000 /* 1.000000 */);
               if(_ctx.gate || _ctx.sustaining){
                  _ctx.state = 1;
               }
               else
               {
                  _ctx.state = 3;
               }
            }
            if(_ctx.quickKill){
               _ctx.level = (_ctx.level + (- _ctx.qkStep));
               if(_ctx.level < 0x0 /* 0.000000 */){
                  _ctx.level = 0x0 /* 0.000000 */;
               }
            }
            if(_ctx.state == 2){
               oBuffer[i] = fix_mul(_ctx.level,(_ctx.buffer_cross[idx] + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(_ctx.buffer_cross[(1 + idx)] + (- _ctx.buffer_cross[idx])))));
            }
            else
            {
               oBuffer[i] = fix_mul(_ctx.level,(synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample((1 + idx)) + (- synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample(idx))))));
            }
         }
         if(_ctx.quickKill && ((_ctx.level <= 0x0 /* 0.000000 */) || (_ctx.state <= 0))){
            _ctx.quickKill = false;
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
            _ctx.state = 1;
            synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(_ctx,_ctx.nextNote);
            synthSamplerJapaneseShakuhachiFlute_Sampler_setLevel(_ctx,synthSamplerJapaneseShakuhachiFlute_Util_velocityToLevel(_ctx.nextVelocity));
         }
      }
      else
      {
         oBuffer[i] = 0x0 /* 0.000000 */;
      }
      i = (1 + i);
   }
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_setSamplerate(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.fsRatio = fix_div(_ctx.sampleFs,_ctx.fs);
   }
   synthSamplerJapaneseShakuhachiFlute_Sampler_updateStep(_ctx);
   _ctx.qkStep = fix_div(0x10000 /* 1.000000 */,fix_mul(0x50000 /* 5.000000 */,_ctx.fs));
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_updateCrossFade(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx){
   if((_ctx.loopS > (256 / 2)) && ((_ctx.size + (- _ctx.loopE)) > (1 + (256 / 2)))){
      _ctx.crossfade = true;
      int i;
      i = 0;
      fix16_t k;
      k = 0x0 /* 0.000000 */;
      int idxS;
      idxS = (_ctx.loopS + (- (256 / 2)));
      int idxE;
      idxE = (_ctx.loopE + (- (256 / 2)));
      while(i < 256){
         k = fix_mul(0x101 /* 0.003922 */,int_to_fix(i));
         _ctx.buffer_cross[i] = (fix_mul(k,synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample((i + idxS))) + fix_mul(synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSample((i + idxE)),(0x10000 /* 1.000000 */ + (- k))));
         i = (1 + i);
      }
   }
   else
   {
      _ctx.crossfade = false;
   }
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_setSustain(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.sustain = flag;
   if(_ctx.gate && _ctx.sustain){
      _ctx.sustaining = true;
   }
   if(bool_not(_ctx.sustain)){
      _ctx.sustaining = false;
   }
}

uint8_t synthSamplerJapaneseShakuhachiFlute_Sampler_noteOn(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   uint8_t isNew;
   isNew = synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.playingnotes,note,velocity,channel);
   _ctx.gate = true;
   if(_ctx.sustain){
      _ctx.sustaining = true;
   }
   if(_ctx.state <= 0){
      _ctx.posBase = 0;
      _ctx.pos = 0x0 /* 0.000000 */;
      _ctx.state = 1;
      synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(_ctx,note);
      synthSamplerJapaneseShakuhachiFlute_Sampler_setLevel(_ctx,synthSamplerJapaneseShakuhachiFlute_Util_velocityToLevel(velocity));
   }
   else
   {
      _ctx.quickKill = true;
      _ctx.nextNote = note;
      _ctx.nextVelocity = velocity;
   }
   return isNew;
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_noteOff(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   if(synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.playingnotes,note,channel)){
      if(synthSamplerJapaneseShakuhachiFlute_Notes_nbNotes(_ctx.playingnotes) > 0){
         int last_played;
         last_played = synthSamplerJapaneseShakuhachiFlute_Notes_lastNote(_ctx.playingnotes);
         if((last_played > 0) && (last_played <= 128)){
            if(_ctx.quickKill){
               _ctx.nextNote = ((-1) + last_played);
            }
            else
            {
               synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(_ctx,((-1) + last_played));
            }
         }
      }
      else
      {
         _ctx.gate = false;
      }
   }
}

void synthSamplerJapaneseShakuhachiFlute_Sampler_default(synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0 &_ctx){
   _ctx.size = synthSamplerJapaneseShakuhachiFlute_SampleWrapper_getSampleSize();
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_cross);
   _ctx.crossfade = false;
   _ctx.sampleFs = 0x1e0000 /* 30.000000 */;
   _ctx.sampleNote = 60;
   if(false){
      int lS;
      lS = (-1);
      int lE;
      lE = (-1);
      if((lS >= 0) && (lE < _ctx.size) && (lE >= lS)){
         synthSamplerJapaneseShakuhachiFlute_Sampler_setLoop(_ctx,true);
         synthSamplerJapaneseShakuhachiFlute_Sampler_setLoopStart(_ctx,lS);
         synthSamplerJapaneseShakuhachiFlute_Sampler_setLoopEnd(_ctx,lE);
      }
   }
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_o);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setLevel(_ctx,0x10000 /* 1.000000 */);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setNote(_ctx,69);
   synthSamplerJapaneseShakuhachiFlute_Notes_default(_ctx.playingnotes);
   synthSamplerJapaneseShakuhachiFlute_Notes_setAllowDuplicates(_ctx.playingnotes,true);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setPoly(_ctx,false);
}

void synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0_init(synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0 &_output_){
   synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0 &_ctx = _output_;
   synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0_init(_ctx.voice3);
   synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0_init(_ctx.voice2);
   synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0_init(_ctx.voice1);
   synthSamplerJapaneseShakuhachiFlute_Sampler__ctx_type_0_init(_ctx.voice0);
   _ctx.should_leftovers = false;
   synthSamplerJapaneseShakuhachiFlute_Poly_default(_ctx);
   
   return ;
}

fix16_t synthSamplerJapaneseShakuhachiFlute_Poly_getSample(synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0 &_ctx, int voice){
   switch(voice) {
      case 0:
         return synthSamplerJapaneseShakuhachiFlute_Sampler_process(_ctx.voice0);
      break;
      case 1:
         return synthSamplerJapaneseShakuhachiFlute_Sampler_process(_ctx.voice1);
      break;
      case 2:
         return synthSamplerJapaneseShakuhachiFlute_Sampler_process(_ctx.voice2);
      break;
      case 3:
         return synthSamplerJapaneseShakuhachiFlute_Sampler_process(_ctx.voice3);
      break;
    
   }
   return 0x0 /* 0.000000 */;
}

void synthSamplerJapaneseShakuhachiFlute_Poly_default(synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0 &_ctx){
   _ctx.should_leftovers = false;
   synthSamplerJapaneseShakuhachiFlute_Sampler_default(_ctx.voice0);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setPoly(_ctx.voice0,true);
   synthSamplerJapaneseShakuhachiFlute_Sampler_default(_ctx.voice1);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setPoly(_ctx.voice1,true);
   synthSamplerJapaneseShakuhachiFlute_Sampler_default(_ctx.voice2);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setPoly(_ctx.voice2,true);
   synthSamplerJapaneseShakuhachiFlute_Sampler_default(_ctx.voice3);
   synthSamplerJapaneseShakuhachiFlute_Sampler_setPoly(_ctx.voice3,true);
}

void synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0_init(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_output_){
   synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx = _output_;
   synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0_init(_ctx.voicesinactive);
   synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0_init(_ctx.voicesactive);
   _ctx.voices_ratio = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.voices);
   synthSamplerJapaneseShakuhachiFlute_Notes__ctx_type_0_init(_ctx.voiceinsactive);
   _ctx.reuse = false;
   synthSamplerJapaneseShakuhachiFlute_Poly__ctx_type_0_init(_ctx.poly);
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
   synthSamplerJapaneseShakuhachiFlute_Voice_default(_ctx);
   
   return ;
}

fix16_t synthSamplerJapaneseShakuhachiFlute_Voice_process(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   while(i < _ctx.number_voices){
      _ctx.last_values[i] = synthSamplerJapaneseShakuhachiFlute_Poly_getSample(_ctx.poly,i);
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

void synthSamplerJapaneseShakuhachiFlute_Voice_process_bufferTo(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   int v;
   v = 0;
   int i;
   i = 0;
   if(v < _ctx.number_voices){
      synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
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
      synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
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

void synthSamplerJapaneseShakuhachiFlute_Voice_process_bufferTo_alt(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,0,nb,_ctx.buffer_v0);
   synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,1,nb,_ctx.buffer_v1);
   synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,2,nb,_ctx.buffer_v2);
   synthSamplerJapaneseShakuhachiFlute_Poly_runVoice(_ctx.poly,3,nb,_ctx.buffer_v3);
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

void synthSamplerJapaneseShakuhachiFlute_Voice_noteOff(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= 4)){
      if(synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesactive,((-1) + v),0)){
         synthSamplerJapaneseShakuhachiFlute_Poly_sendNoteOff(_ctx.poly,((-1) + v),note,channel);
         _ctx.notes[note] = (- v);
         _ctx.voices[((-1) + v)] = (- (1 + note));
         if(v <= _ctx.number_voices){
            synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0);
         }
      }
   }
}

void synthSamplerJapaneseShakuhachiFlute_Voice_noteOn(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   velocity = int_clip(velocity,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= _ctx.number_voices)){
      if(bool_not((synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesactive,((-1) + v),0) && synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0) && synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
         _ctx.notes[note] = 0;
         _ctx.voices[((-1) + v)] = 0;
         v = 0;
      }
   }
   else
   {
      if(_ctx.reuse && (v < 0) && ((- v) <= _ctx.number_voices) && (_ctx.voices[((-1) + (- v))] == (- (1 + note))) && (_ctx.notes[note] == v)){
         v = (- v);
         if(bool_not((synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
            _ctx.notes[note] = 0;
            _ctx.voices[((-1) + v)] = 0;
            v = 0;
         }
      }
      else
      {
         v = synthSamplerJapaneseShakuhachiFlute_Notes_firstNote(_ctx.voicesinactive);
         if((v <= 0) || (v > _ctx.number_voices)){
            int active_v;
            active_v = synthSamplerJapaneseShakuhachiFlute_Notes_firstNote(_ctx.voicesactive);
            if(active_v > 0){
               synthSamplerJapaneseShakuhachiFlute_Voice_noteOff(_ctx,_ctx.voices[((-1) + active_v)],0);
            }
         }
         v = synthSamplerJapaneseShakuhachiFlute_Notes_firstNote(_ctx.voicesinactive);
         if((v > 0) && (v <= _ctx.number_voices)){
            if(bool_not((synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)))){
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
      if(synthSamplerJapaneseShakuhachiFlute_Poly_shouldLeftOvers(_ctx.poly)){
         _ctx.leftovers = (_ctx.leftovers + _ctx.last_values[((-1) + v)]);
      }
      synthSamplerJapaneseShakuhachiFlute_Poly_sendNoteOn(_ctx.poly,((-1) + v),note,velocity,channel);
      _ctx.notes[note] = v;
      _ctx.voices[((-1) + v)] = note;
      _ctx.last_velocities[((-1) + v)] = velocity;
   }
}

void synthSamplerJapaneseShakuhachiFlute_Voice_setNbVoices(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, int nbvoices){
   nbvoices = int_clip(nbvoices,0,4);
   int i;
   i = synthSamplerJapaneseShakuhachiFlute_Notes_nbNotes(_ctx.voicesactive);
   while((i > nbvoices) && (i > 0)){
      synthSamplerJapaneseShakuhachiFlute_Voice_noteOff(_ctx,_ctx.voices[((-1) + i)],0);
      synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesinactive,((-1) + i),0);
      i = ((-1) + i);
   }
   i = synthSamplerJapaneseShakuhachiFlute_Notes_nbNotes(_ctx.voicesinactive);
   if(i < nbvoices){
      while(i < nbvoices){
         synthSamplerJapaneseShakuhachiFlute_Notes_noteOn(_ctx.voicesinactive,i,127,0);
         i = (1 + i);
      }
   }
   else
   {
      while(i >= nbvoices){
         synthSamplerJapaneseShakuhachiFlute_Notes_noteOff(_ctx.voicesinactive,i,0);
         i = ((-1) + i);
      }
   }
   _ctx.number_voices = nbvoices;
   if(_ctx.number_voices > 0){
      _ctx.voices_ratio = fix_div(0x10000 /* 1.000000 */,int_to_fix(_ctx.number_voices));
   }
}

void synthSamplerJapaneseShakuhachiFlute_Voice_setSamplerate(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   synthSamplerJapaneseShakuhachiFlute_Poly_setSamplerate(_ctx.poly,_ctx.fs);
   fix16_t log_base;
   log_base = 0x24d76 /* 2.302585 */;
   _ctx.leftovers_decay = fix_exp(fix_div(fix_mul(-0xc4 /* -0.003000 */,log_base),fix_mul(0x3333 /* 0.200000 */,_ctx.fs)));
}

void synthSamplerJapaneseShakuhachiFlute_Voice_default(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0 &_ctx){
   synthSamplerJapaneseShakuhachiFlute_Poly_default(_ctx.poly);
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_v0);
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_v1);
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_v2);
   synthSamplerJapaneseShakuhachiFlute_Buffer_buffer(_ctx.buffer_v3);
   if(_ctx.number_voices == 0){
      _ctx.number_voices = 4;
   }
   synthSamplerJapaneseShakuhachiFlute_Voice_setNbVoices(_ctx,_ctx.number_voices);
   synthSamplerJapaneseShakuhachiFlute_Notes_default(_ctx.voicesactive);
   synthSamplerJapaneseShakuhachiFlute_Notes_setPoly(_ctx.voicesactive,false);
   synthSamplerJapaneseShakuhachiFlute_Notes_setAllowDuplicates(_ctx.voicesactive,false);
   synthSamplerJapaneseShakuhachiFlute_Notes_default(_ctx.voicesinactive);
   synthSamplerJapaneseShakuhachiFlute_Notes_setPoly(_ctx.voicesinactive,false);
   synthSamplerJapaneseShakuhachiFlute_Notes_setAllowDuplicates(_ctx.voiceinsactive,false);
   synthSamplerJapaneseShakuhachiFlute_Voice_setNormalize(_ctx,true);
   synthSamplerJapaneseShakuhachiFlute_Voice_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   synthSamplerJapaneseShakuhachiFlute_Voice_setReuse(_ctx,false);
}

void synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_1_init(synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_1 &_output_){
   synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_1 &_ctx = _output_;
   synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0_init(_ctx._inst275);
   synthSamplerJapaneseShakuhachiFlute_Voice__ctx_type_0_init(_ctx._inst1b9);
   
   return ;
}


