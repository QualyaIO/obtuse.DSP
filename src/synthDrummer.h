
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef SYNTHDRUMMER_H
#define SYNTHDRUMMER_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "synthDrummer.tables.h"

static_inline fix16_t synthDrummer_Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

typedef struct synthDrummer_Util__ctx_type_1 {
   uint8_t pre;
} synthDrummer_Util__ctx_type_1;

typedef synthDrummer_Util__ctx_type_1 synthDrummer_Util_edge_type;

static_inline void synthDrummer_Util__ctx_type_1_init(synthDrummer_Util__ctx_type_1 &_output_){
   synthDrummer_Util__ctx_type_1 _ctx;
   _ctx.pre = false;
   _output_ = _ctx;
   return ;
}

static_inline void synthDrummer_Util_edge_init(synthDrummer_Util__ctx_type_1 &_output_){
   synthDrummer_Util__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t synthDrummer_Util_edge(synthDrummer_Util__ctx_type_1 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline fix16_t synthDrummer_Util_cubic_clipper(fix16_t x){
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

typedef struct synthDrummer_Util__ctx_type_3 {
   fix16_t pre_x;
} synthDrummer_Util__ctx_type_3;

typedef synthDrummer_Util__ctx_type_3 synthDrummer_Util_change_type;

static_inline void synthDrummer_Util__ctx_type_3_init(synthDrummer_Util__ctx_type_3 &_output_){
   synthDrummer_Util__ctx_type_3 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void synthDrummer_Util_change_init(synthDrummer_Util__ctx_type_3 &_output_){
   synthDrummer_Util__ctx_type_3_init(_output_);
   return ;
}

static_inline uint8_t synthDrummer_Util_change(synthDrummer_Util__ctx_type_3 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

typedef struct synthDrummer_Util__ctx_type_4 {
   fix16_t x;
} synthDrummer_Util__ctx_type_4;

typedef synthDrummer_Util__ctx_type_4 synthDrummer_Util_smooth_type;

static_inline void synthDrummer_Util__ctx_type_4_init(synthDrummer_Util__ctx_type_4 &_output_){
   synthDrummer_Util__ctx_type_4 _ctx;
   _ctx.x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void synthDrummer_Util_smooth_init(synthDrummer_Util__ctx_type_4 &_output_){
   synthDrummer_Util__ctx_type_4_init(_output_);
   return ;
}

static_inline fix16_t synthDrummer_Util_smooth(synthDrummer_Util__ctx_type_4 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t synthDrummer_Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

static_inline void synthDrummer_Buffer_buffer(fix16_t (&_output_)[256]){
   fix16_t buff[256];
   fix_copy_array(256,_output_,buff);
   return ;
}

static_inline void synthDrummer_Buffer_buffer_large(fix16_t (&_output_)[2048]){
   fix16_t buff[2048];
   fix_copy_array(2048,_output_,buff);
   return ;
}

static_inline int synthDrummer_Drummer_drumkit_samples(){
   return 107178;
};

static_inline fix16_t synthDrummer_Drummer_drumkit(int channel, int index){
   if(channel == 0){
      return fix_wrap_array(synthDrummer_Drummer_drumkit_chan_0)[(index % 107178)];
   }
   return 0x0 /* 0.000000 */;
}

typedef struct synthDrummer_Drummer__ctx_type_2 {
   fix16_t step;
   int slices_start[12];
   int slices_end[12];
   int slice;
   int size;
   fix16_t sampleFs;
   int posBase;
   fix16_t pos;
   fix16_t noteRatio;
   fix16_t level;
   fix16_t fsRatio;
   fix16_t fs;
   fix16_t buffer_o[256];
} synthDrummer_Drummer__ctx_type_2;

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_getSample_type;

void synthDrummer_Drummer__ctx_type_2_init(synthDrummer_Drummer__ctx_type_2 &_output_);

static_inline void synthDrummer_Drummer_getSample_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t synthDrummer_Drummer_getSample(synthDrummer_Drummer__ctx_type_2 &_ctx, int index){
   return synthDrummer_Drummer_drumkit(0,index);
};

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_process_type;

static_inline void synthDrummer_Drummer_process_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

fix16_t synthDrummer_Drummer_process(synthDrummer_Drummer__ctx_type_2 &_ctx);

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_process_bufferTo_type;

static_inline void synthDrummer_Drummer_process_bufferTo_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

void synthDrummer_Drummer_process_bufferTo(synthDrummer_Drummer__ctx_type_2 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_process_buffer_type;

static_inline void synthDrummer_Drummer_process_buffer_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthDrummer_Drummer_process_buffer(synthDrummer_Drummer__ctx_type_2 &_ctx, int nb){
   synthDrummer_Drummer_process_bufferTo(_ctx,nb,_ctx.buffer_o);
};

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_updateStep_type;

static_inline void synthDrummer_Drummer_updateStep_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthDrummer_Drummer_updateStep(synthDrummer_Drummer__ctx_type_2 &_ctx){
   _ctx.step = fix_mul(_ctx.fsRatio,_ctx.noteRatio);
};

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_setSlices_type;

static_inline void synthDrummer_Drummer_setSlices_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

void synthDrummer_Drummer_setSlices(synthDrummer_Drummer__ctx_type_2 &_ctx, int (&newSlicesStart)[12], int (&newSlicesEnd)[12]);

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_setSamplerate_type;

static_inline void synthDrummer_Drummer_setSamplerate_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

void synthDrummer_Drummer_setSamplerate(synthDrummer_Drummer__ctx_type_2 &_ctx, fix16_t newFs);

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_getSampleSize_type;

static_inline void synthDrummer_Drummer_getSampleSize_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline int synthDrummer_Drummer_getSampleSize(synthDrummer_Drummer__ctx_type_2 &_ctx){
   return _ctx.size;
};

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_setLevel_type;

static_inline void synthDrummer_Drummer_setLevel_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthDrummer_Drummer_setLevel(synthDrummer_Drummer__ctx_type_2 &_ctx, fix16_t newLevel){
   _ctx.level = newLevel;
};

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_noteOn_type;

static_inline void synthDrummer_Drummer_noteOn_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

void synthDrummer_Drummer_noteOn(synthDrummer_Drummer__ctx_type_2 &_ctx, int note, int velocity, int channel);

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_noteOff_type;

static_inline void synthDrummer_Drummer_noteOff_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthDrummer_Drummer_noteOff(synthDrummer_Drummer__ctx_type_2 &_ctx, int note, int channel){
}

typedef synthDrummer_Drummer__ctx_type_2 synthDrummer_Drummer_default_type;

static_inline void synthDrummer_Drummer_default_init(synthDrummer_Drummer__ctx_type_2 &_output_){
   synthDrummer_Drummer__ctx_type_2_init(_output_);
   return ;
}

void synthDrummer_Drummer_default(synthDrummer_Drummer__ctx_type_2 &_ctx);

typedef struct synthDrummer_Poly__ctx_type_0 {
   synthDrummer_Drummer__ctx_type_2 voice3;
   synthDrummer_Drummer__ctx_type_2 voice2;
   synthDrummer_Drummer__ctx_type_2 voice1;
   synthDrummer_Drummer__ctx_type_2 voice0;
   uint8_t should_leftovers;
} synthDrummer_Poly__ctx_type_0;

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_getSample_type;

void synthDrummer_Poly__ctx_type_0_init(synthDrummer_Poly__ctx_type_0 &_output_);

static_inline void synthDrummer_Poly_getSample_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

fix16_t synthDrummer_Poly_getSample(synthDrummer_Poly__ctx_type_0 &_ctx, int voice);

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_runVoice_type;

static_inline void synthDrummer_Poly_runVoice_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_runVoice(synthDrummer_Poly__ctx_type_0 &_ctx, int voice, int nb, fix16_t (&buff)[256]){
   switch(voice) {
      case 0:
         synthDrummer_Drummer_process_bufferTo(_ctx.voice0,nb,buff);
      break;
      case 1:
         synthDrummer_Drummer_process_bufferTo(_ctx.voice1,nb,buff);
      break;
      case 2:
         synthDrummer_Drummer_process_bufferTo(_ctx.voice2,nb,buff);
      break;
      case 3:
         synthDrummer_Drummer_process_bufferTo(_ctx.voice3,nb,buff);
      break;
    
   }
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_sendNoteOn_type;

static_inline void synthDrummer_Poly_sendNoteOn_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_sendNoteOn(synthDrummer_Poly__ctx_type_0 &_ctx, int voice, int note, int velocity, int channel){
   switch(voice) {
      case 0:
         synthDrummer_Drummer_noteOn(_ctx.voice0,note,velocity,channel);
      break;
      case 1:
         synthDrummer_Drummer_noteOn(_ctx.voice1,note,velocity,channel);
      break;
      case 2:
         synthDrummer_Drummer_noteOn(_ctx.voice2,note,velocity,channel);
      break;
      case 3:
         synthDrummer_Drummer_noteOn(_ctx.voice3,note,velocity,channel);
      break;
    
   }
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_sendNoteOff_type;

static_inline void synthDrummer_Poly_sendNoteOff_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_sendNoteOff(synthDrummer_Poly__ctx_type_0 &_ctx, int voice, int note, int channel){
   switch(voice) {
      case 0:
         synthDrummer_Drummer_noteOff(_ctx.voice0,note,channel);
      break;
      case 1:
         synthDrummer_Drummer_noteOff(_ctx.voice1,note,channel);
      break;
      case 2:
         synthDrummer_Drummer_noteOff(_ctx.voice2,note,channel);
      break;
      case 3:
         synthDrummer_Drummer_noteOff(_ctx.voice3,note,channel);
      break;
    
   }
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_setSamplerate_type;

static_inline void synthDrummer_Poly_setSamplerate_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_setSamplerate(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t fs){
   synthDrummer_Drummer_setSamplerate(_ctx.voice0,fs);
   synthDrummer_Drummer_setSamplerate(_ctx.voice1,fs);
   synthDrummer_Drummer_setSamplerate(_ctx.voice2,fs);
   synthDrummer_Drummer_setSamplerate(_ctx.voice3,fs);
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetLoop_type;

static_inline void synthDrummer_Poly_synthSetLoop_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetLoop(synthDrummer_Poly__ctx_type_0 &_ctx, uint8_t flag){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetLoopStart_type;

static_inline void synthDrummer_Poly_synthSetLoopStart_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetLoopStart(synthDrummer_Poly__ctx_type_0 &_ctx, int value){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetLoopEnd_type;

static_inline void synthDrummer_Poly_synthSetLoopEnd_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetLoopEnd(synthDrummer_Poly__ctx_type_0 &_ctx, int value){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthGetSize_type;

static_inline void synthDrummer_Poly_synthGetSize_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthDrummer_Poly_synthGetSize(synthDrummer_Poly__ctx_type_0 &_ctx){
   return 0;
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthGetNbWavetables_type;

static_inline void synthDrummer_Poly_synthGetNbWavetables_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthDrummer_Poly_synthGetNbWavetables(synthDrummer_Poly__ctx_type_0 &_ctx){
   return 0;
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorWavetable_type;

static_inline void synthDrummer_Poly_synthSetModulatorWavetable_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorWavetable(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t wavetableIdx){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorWavetablePhase_type;

static_inline void synthDrummer_Poly_synthSetModulatorWavetablePhase_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorWavetablePhase(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t phaseIdx){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetCarrierWavetable_type;

static_inline void synthDrummer_Poly_synthSetCarrierWavetable_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetCarrierWavetable(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t wavetableIdx){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetCarrierWavetablePhase_type;

static_inline void synthDrummer_Poly_synthSetCarrierWavetablePhase_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetCarrierWavetablePhase(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t phaseIdx){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorRatio_type;

static_inline void synthDrummer_Poly_synthSetModulatorRatio_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorRatio(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetCarrierRatio_type;

static_inline void synthDrummer_Poly_synthSetCarrierRatio_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetCarrierRatio(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorLevel_type;

static_inline void synthDrummer_Poly_synthSetModulatorLevel_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorLevel(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t level){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorTargetLevel_type;

static_inline void synthDrummer_Poly_synthSetModulatorTargetLevel_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorTargetLevel(synthDrummer_Poly__ctx_type_0 &_ctx, uint8_t targetLevel){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorPhaseShift_type;

static_inline void synthDrummer_Poly_synthSetModulatorPhaseShift_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorPhaseShift(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorFeedback_type;

static_inline void synthDrummer_Poly_synthSetModulatorFeedback_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorFeedback(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetModulatorADSR_type;

static_inline void synthDrummer_Poly_synthSetModulatorADSR_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetModulatorADSR(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_synthSetCarrierADSR_type;

static_inline void synthDrummer_Poly_synthSetCarrierADSR_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Poly_synthSetCarrierADSR(synthDrummer_Poly__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
}

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_shouldLeftOvers_type;

static_inline void synthDrummer_Poly_shouldLeftOvers_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline uint8_t synthDrummer_Poly_shouldLeftOvers(synthDrummer_Poly__ctx_type_0 &_ctx){
   return _ctx.should_leftovers;
};

typedef synthDrummer_Poly__ctx_type_0 synthDrummer_Poly_default_type;

static_inline void synthDrummer_Poly_default_init(synthDrummer_Poly__ctx_type_0 &_output_){
   synthDrummer_Poly__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Poly_default(synthDrummer_Poly__ctx_type_0 &_ctx);

typedef struct synthDrummer_Notes__ctx_type_0 {
   uint8_t poly;
   int notes[128];
   int nb_notes;
   int last_notes[128];
} synthDrummer_Notes__ctx_type_0;

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_setPoly_type;

void synthDrummer_Notes__ctx_type_0_init(synthDrummer_Notes__ctx_type_0 &_output_);

static_inline void synthDrummer_Notes_setPoly_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Notes_setPoly(synthDrummer_Notes__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.poly = flag;
};

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_default_type;

static_inline void synthDrummer_Notes_default_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Notes_default(synthDrummer_Notes__ctx_type_0 &_ctx){
   synthDrummer_Notes_setPoly(_ctx,false);
};

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_nbNotes_type;

static_inline void synthDrummer_Notes_nbNotes_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthDrummer_Notes_nbNotes(synthDrummer_Notes__ctx_type_0 &_ctx){
   return _ctx.nb_notes;
};

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_firstNote_type;

static_inline void synthDrummer_Notes_firstNote_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

int synthDrummer_Notes_firstNote(synthDrummer_Notes__ctx_type_0 &_ctx);

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_lastNote_type;

static_inline void synthDrummer_Notes_lastNote_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

int synthDrummer_Notes_lastNote(synthDrummer_Notes__ctx_type_0 &_ctx);

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_noteOn_type;

static_inline void synthDrummer_Notes_noteOn_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t synthDrummer_Notes_noteOn(synthDrummer_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef synthDrummer_Notes__ctx_type_0 synthDrummer_Notes_noteOff_type;

static_inline void synthDrummer_Notes_noteOff_init(synthDrummer_Notes__ctx_type_0 &_output_){
   synthDrummer_Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t synthDrummer_Notes_noteOff(synthDrummer_Notes__ctx_type_0 &_ctx, int note, int channel);

typedef struct synthDrummer_Voice__ctx_type_0 {
   synthDrummer_Notes__ctx_type_0 voicesinactive;
   synthDrummer_Notes__ctx_type_0 voicesactive;
   fix16_t voices_ratio;
   int voices[4];
   synthDrummer_Poly__ctx_type_0 poly;
   int number_voices;
   int notes[128];
   uint8_t normalize;
   fix16_t leftovers_decay;
   fix16_t leftovers;
   int last_velocities[4];
   fix16_t last_values[4];
   fix16_t fs;
   fix16_t buffer_v3[256];
   fix16_t buffer_v2[256];
   fix16_t buffer_v1[256];
   fix16_t buffer_v0[256];
} synthDrummer_Voice__ctx_type_0;

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_process_type;

void synthDrummer_Voice__ctx_type_0_init(synthDrummer_Voice__ctx_type_0 &_output_);

static_inline void synthDrummer_Voice_process_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

fix16_t synthDrummer_Voice_process(synthDrummer_Voice__ctx_type_0 &_ctx);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_process_bufferTo_type;

static_inline void synthDrummer_Voice_process_bufferTo_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_process_bufferTo(synthDrummer_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_process_bufferTo_alt_type;

static_inline void synthDrummer_Voice_process_bufferTo_alt_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_process_bufferTo_alt(synthDrummer_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_noteOff_type;

static_inline void synthDrummer_Voice_noteOff_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_noteOff(synthDrummer_Voice__ctx_type_0 &_ctx, int note, int channel);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_noteOn_type;

static_inline void synthDrummer_Voice_noteOn_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_noteOn(synthDrummer_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_setNbVoices_type;

static_inline void synthDrummer_Voice_setNbVoices_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_setNbVoices(synthDrummer_Voice__ctx_type_0 &_ctx, int nbvoices);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_setNormalize_type;

static_inline void synthDrummer_Voice_setNormalize_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_setNormalize(synthDrummer_Voice__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.normalize = flag;
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_setSamplerate_type;

static_inline void synthDrummer_Voice_setSamplerate_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_setSamplerate(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t newFs);

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetLoop_type;

static_inline void synthDrummer_Voice_synthSetLoop_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetLoop(synthDrummer_Voice__ctx_type_0 &_ctx, uint8_t flag){
   synthDrummer_Poly_synthSetLoop(_ctx.poly,flag);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetLoopStart_type;

static_inline void synthDrummer_Voice_synthSetLoopStart_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetLoopStart(synthDrummer_Voice__ctx_type_0 &_ctx, int value){
   synthDrummer_Poly_synthSetLoopStart(_ctx.poly,value);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetLoopEnd_type;

static_inline void synthDrummer_Voice_synthSetLoopEnd_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetLoopEnd(synthDrummer_Voice__ctx_type_0 &_ctx, int value){
   synthDrummer_Poly_synthSetLoopEnd(_ctx.poly,value);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthGetSize_type;

static_inline void synthDrummer_Voice_synthGetSize_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthDrummer_Voice_synthGetSize(synthDrummer_Voice__ctx_type_0 &_ctx){
   return synthDrummer_Poly_synthGetSize(_ctx.poly);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthGetNbWavetables_type;

static_inline void synthDrummer_Voice_synthGetNbWavetables_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthDrummer_Voice_synthGetNbWavetables(synthDrummer_Voice__ctx_type_0 &_ctx){
   return synthDrummer_Poly_synthGetNbWavetables(_ctx.poly);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorWavetable_type;

static_inline void synthDrummer_Voice_synthSetModulatorWavetable_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorWavetable(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t wavetableIdx){
   synthDrummer_Poly_synthSetModulatorWavetable(_ctx.poly,wavetableIdx);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorWavetablePhase_type;

static_inline void synthDrummer_Voice_synthSetModulatorWavetablePhase_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorWavetablePhase(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t phaseIdx){
   synthDrummer_Poly_synthSetModulatorWavetablePhase(_ctx.poly,phaseIdx);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetCarrierWavetable_type;

static_inline void synthDrummer_Voice_synthSetCarrierWavetable_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetCarrierWavetable(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t wavetableIdx){
   synthDrummer_Poly_synthSetCarrierWavetable(_ctx.poly,wavetableIdx);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetCarrierWavetablePhase_type;

static_inline void synthDrummer_Voice_synthSetCarrierWavetablePhase_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetCarrierWavetablePhase(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t phaseIdx){
   synthDrummer_Poly_synthSetCarrierWavetablePhase(_ctx.poly,phaseIdx);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorRatio_type;

static_inline void synthDrummer_Voice_synthSetModulatorRatio_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorRatio(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthDrummer_Poly_synthSetModulatorRatio(_ctx.poly,ratio);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetCarrierRatio_type;

static_inline void synthDrummer_Voice_synthSetCarrierRatio_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetCarrierRatio(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthDrummer_Poly_synthSetCarrierRatio(_ctx.poly,ratio);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorLevel_type;

static_inline void synthDrummer_Voice_synthSetModulatorLevel_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorLevel(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t level){
   synthDrummer_Poly_synthSetModulatorLevel(_ctx.poly,level);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorTargetLevel_type;

static_inline void synthDrummer_Voice_synthSetModulatorTargetLevel_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorTargetLevel(synthDrummer_Voice__ctx_type_0 &_ctx, uint8_t targetLevel){
   synthDrummer_Poly_synthSetModulatorTargetLevel(_ctx.poly,targetLevel);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorPhaseShift_type;

static_inline void synthDrummer_Voice_synthSetModulatorPhaseShift_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorPhaseShift(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthDrummer_Poly_synthSetModulatorPhaseShift(_ctx.poly,ratio);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorFeedback_type;

static_inline void synthDrummer_Voice_synthSetModulatorFeedback_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorFeedback(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthDrummer_Poly_synthSetModulatorFeedback(_ctx.poly,ratio);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetModulatorADSR_type;

static_inline void synthDrummer_Voice_synthSetModulatorADSR_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetModulatorADSR(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
   synthDrummer_Poly_synthSetModulatorADSR(_ctx.poly,a,d,s,r);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_synthSetCarrierADSR_type;

static_inline void synthDrummer_Voice_synthSetCarrierADSR_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthDrummer_Voice_synthSetCarrierADSR(synthDrummer_Voice__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
   synthDrummer_Poly_synthSetCarrierADSR(_ctx.poly,a,d,s,r);
};

typedef synthDrummer_Voice__ctx_type_0 synthDrummer_Voice_default_type;

static_inline void synthDrummer_Voice_default_init(synthDrummer_Voice__ctx_type_0 &_output_){
   synthDrummer_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthDrummer_Voice_default(synthDrummer_Voice__ctx_type_0 &_ctx);



#endif // SYNTHDRUMMER_H
