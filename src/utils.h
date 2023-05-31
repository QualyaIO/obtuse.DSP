
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "utils.tables.h"

typedef struct utils__tuple___int_int_int__ {
   int field_0;
   int field_1;
   int field_2;
} utils__tuple___int_int_int__;

int utils_Gate_compareTimeFract(int time1S, fix16_t time1Fract, int time2S, fix16_t time2Fract);

typedef struct utils_Gate__ctx_type_1 {
   int values[128];
   int e;
   int b;
} utils_Gate__ctx_type_1;

typedef utils_Gate__ctx_type_1 utils_Gate_list_type;

void utils_Gate__ctx_type_1_init(utils_Gate__ctx_type_1 &_output_);

static_inline void utils_Gate_list_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

static_inline void utils_Gate_list(utils_Gate__ctx_type_1 &_ctx){
}

typedef utils_Gate__ctx_type_1 utils_Gate_getListSize_type;

static_inline void utils_Gate_getListSize_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

static_inline int utils_Gate_getListSize(utils_Gate__ctx_type_1 &_ctx){
   return ((128 + _ctx.e + (- _ctx.b)) % 128);
};

typedef utils_Gate__ctx_type_1 utils_Gate_getListMaxSize_type;

static_inline void utils_Gate_getListMaxSize_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

static_inline int utils_Gate_getListMaxSize(utils_Gate__ctx_type_1 &_ctx){
   return 128;
};

typedef utils_Gate__ctx_type_1 utils_Gate_getListSpace_type;

static_inline void utils_Gate_getListSpace_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

static_inline int utils_Gate_getListSpace(utils_Gate__ctx_type_1 &_ctx){
   return (128 + (- utils_Gate_getListSize(_ctx)));
};

typedef utils_Gate__ctx_type_1 utils_Gate_push_type;

static_inline void utils_Gate_push_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

uint8_t utils_Gate_push(utils_Gate__ctx_type_1 &_ctx, int v);

typedef utils_Gate__ctx_type_1 utils_Gate_pop_type;

static_inline void utils_Gate_pop_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

int utils_Gate_pop(utils_Gate__ctx_type_1 &_ctx);

typedef utils_Gate__ctx_type_1 utils_Gate_peek_type;

static_inline void utils_Gate_peek_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

int utils_Gate_peek(utils_Gate__ctx_type_1 &_ctx, int n);

typedef utils_Gate__ctx_type_1 utils_Gate_delete_type;

static_inline void utils_Gate_delete_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

int utils_Gate_delete(utils_Gate__ctx_type_1 &_ctx, int n);

typedef utils_Gate__ctx_type_1 utils_Gate_search_type;

static_inline void utils_Gate_search_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

int utils_Gate_search(utils_Gate__ctx_type_1 &_ctx, int value);

typedef utils_Gate__ctx_type_1 utils_Gate_deleteValue_type;

static_inline void utils_Gate_deleteValue_init(utils_Gate__ctx_type_1 &_output_){
   utils_Gate__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t utils_Gate_deleteValue(utils_Gate__ctx_type_1 &_ctx, int value){
   int n;
   n = utils_Gate_search(_ctx,value);
   return (utils_Gate_delete(_ctx,n) == value);
}

typedef struct utils_Gate__ctx_type_2 {
   int timeS;
   fix16_t timeFract;
   int notesS[128];
   utils_Gate__ctx_type_1 notesOn;
   utils_Gate__ctx_type_1 notesOff;
   fix16_t notesFract[128];
   utils_Gate__ctx_type_1 notesActive;
   fix16_t gateDuration;
} utils_Gate__ctx_type_2;

typedef utils_Gate__ctx_type_2 utils_Gate_process_type;

void utils_Gate__ctx_type_2_init(utils_Gate__ctx_type_2 &_output_);

static_inline void utils_Gate_process_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

void utils_Gate_process(utils_Gate__ctx_type_2 &_ctx);

typedef utils_Gate__ctx_type_2 utils_Gate_setTime_type;

static_inline void utils_Gate_setTime_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline void utils_Gate_setTime(utils_Gate__ctx_type_2 &_ctx, int newTimeS, fix16_t newTimeFract){
   _ctx.timeS = newTimeS;
   _ctx.timeFract = newTimeFract;
}

typedef utils_Gate__ctx_type_2 utils_Gate_noteOn_type;

static_inline void utils_Gate_noteOn_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

uint8_t utils_Gate_noteOn(utils_Gate__ctx_type_2 &_ctx, int note, int velocity, int channel);

typedef utils_Gate__ctx_type_2 utils_Gate_noteKill_type;

static_inline void utils_Gate_noteKill_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline void utils_Gate_noteKill(utils_Gate__ctx_type_2 &_ctx, int note){
   note = int_clip(note,0,127);
   utils_Gate_deleteValue(_ctx.notesActive,note);
   _ctx.notesS[note] = 0;
   _ctx.notesFract[note] = 0x0 /* 0.000000 */;
}

typedef utils_Gate__ctx_type_2 utils_Gate_getNoteOff_type;

static_inline void utils_Gate_getNoteOff_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline int utils_Gate_getNoteOff(utils_Gate__ctx_type_2 &_ctx){
   return utils_Gate_pop(_ctx.notesOff);
};

typedef utils_Gate__ctx_type_2 utils_Gate_getNoteOn_type;

static_inline void utils_Gate_getNoteOn_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline int utils_Gate_getNoteOn(utils_Gate__ctx_type_2 &_ctx){
   return utils_Gate_pop(_ctx.notesOn);
};

typedef utils_Gate__ctx_type_2 utils_Gate_setDuration_type;

static_inline void utils_Gate_setDuration_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline void utils_Gate_setDuration(utils_Gate__ctx_type_2 &_ctx, fix16_t duration){
   _ctx.gateDuration = fix_clip(duration,0x41 /* 0.001000 */,duration);
};

typedef utils_Gate__ctx_type_2 utils_Gate_default_type;

static_inline void utils_Gate_default_init(utils_Gate__ctx_type_2 &_output_){
   utils_Gate__ctx_type_2_init(_output_);
   return ;
}

static_inline void utils_Gate_default(utils_Gate__ctx_type_2 &_ctx){
   utils_Gate_setDuration(_ctx,0x3333 /* 0.200000 */);
};

static_inline fix16_t utils_Tonnetz_logBase_raw_c0(int index){
   return utils_Tonnetz_logBase_c0[index];
};

static_inline fix16_t utils_Tonnetz_logBase_raw_c1(int index){
   return utils_Tonnetz_logBase_c1[index];
};

static_inline fix16_t utils_Tonnetz_logBase_raw_c2(int index){
   return utils_Tonnetz_logBase_c2[index];
};

static_inline fix16_t utils_Tonnetz_logBase(fix16_t x){
   int index;
   index = int_clip(fix_to_int(fix_mul(0x21ec5 /* 2.120200 */,(-0x1999 /* -0.100000 */ + x))),0,127);
   return (fix_wrap_array(utils_Tonnetz_logBase_c0)[index] + fix_mul(x,(fix_wrap_array(utils_Tonnetz_logBase_c1)[index] + fix_mul(x,fix_wrap_array(utils_Tonnetz_logBase_c2)[index]))));
}

static_inline fix16_t utils_Tonnetz_spow(fix16_t base, fix16_t x){
   return fix_exp(fix_mul(x,utils_Tonnetz_logBase(base)));
};

static_inline fix16_t utils_Tonnetz_beta(fix16_t x, fix16_t b){
   return fix_clip((0x10000 /* 1.000000 */ + (- utils_Tonnetz_spow((0x10000 /* 1.000000 */ + (- x)),b))),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

void utils_Tonnetz_getScale(int id, uint8_t (&_output_)[12]);

void utils_Tonnetz_getChord(int chord, int (&_output_)[3]);

void utils_Tonnetz_getChordInversion(int chord, int inversion, int (&_output_)[3]);

typedef struct utils_Tonnetz__ctx_type_8 {
   int shifts[11];
   int shift;
   int scaleId;
   uint8_t scale[12];
   int root;
   int process_ret_2;
   int process_ret_1;
   int process_ret_0;
   fix16_t pJump;
   fix16_t inversions[3];
   fix16_t inversionSpread;
   fix16_t chords[6];
   fix16_t chordSpread;
   int chord;
} utils_Tonnetz__ctx_type_8;

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_isChordInShift_type;

void utils_Tonnetz__ctx_type_8_init(utils_Tonnetz__ctx_type_8 &_output_);

static_inline void utils_Tonnetz_isChordInShift_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

uint8_t utils_Tonnetz_isChordInShift(utils_Tonnetz__ctx_type_8 &_ctx, int checkChord, int checkShift);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_drawChord_type;

static_inline void utils_Tonnetz_drawChord_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

int utils_Tonnetz_drawChord(utils_Tonnetz__ctx_type_8 &_ctx, uint8_t lookAround);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_drawInversion_type;

static_inline void utils_Tonnetz_drawInversion_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

int utils_Tonnetz_drawInversion(utils_Tonnetz__ctx_type_8 &_ctx);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_process_type;

static_inline void utils_Tonnetz_process_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_process(utils_Tonnetz__ctx_type_8 &_ctx);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_process_ret_0_type;

static_inline void utils_Tonnetz_process_ret_0_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_process_ret_0(utils_Tonnetz__ctx_type_8 &_ctx){
   return _ctx.process_ret_0;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_process_ret_1_type;

static_inline void utils_Tonnetz_process_ret_1_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_process_ret_1(utils_Tonnetz__ctx_type_8 &_ctx){
   return _ctx.process_ret_1;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_process_ret_2_type;

static_inline void utils_Tonnetz_process_ret_2_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_process_ret_2(utils_Tonnetz__ctx_type_8 &_ctx){
   return _ctx.process_ret_2;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_reset_type;

static_inline void utils_Tonnetz_reset_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_reset(utils_Tonnetz__ctx_type_8 &_ctx);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setScale_type;

static_inline void utils_Tonnetz_setScale_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_setScale(utils_Tonnetz__ctx_type_8 &_ctx, int id);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setRoot_type;

static_inline void utils_Tonnetz_setRoot_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline void utils_Tonnetz_setRoot(utils_Tonnetz__ctx_type_8 &_ctx, int note){
   note = int_clip(note,0,127);
   if(_ctx.root != note){
      _ctx.root = note;
   }
}

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz__updateChords_type;

static_inline void utils_Tonnetz__updateChords_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz__updateChords(utils_Tonnetz__ctx_type_8 &_ctx, fix16_t bParam);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz__updateInversions_type;

static_inline void utils_Tonnetz__updateInversions_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz__updateInversions(utils_Tonnetz__ctx_type_8 &_ctx, fix16_t bParam);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setChord_type;

static_inline void utils_Tonnetz_setChord_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline void utils_Tonnetz_setChord(utils_Tonnetz__ctx_type_8 &_ctx, int newChord){
   _ctx.chord = int_clip(newChord,0,5);
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setChordSpread_type;

static_inline void utils_Tonnetz_setChordSpread_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_setChordSpread(utils_Tonnetz__ctx_type_8 &_ctx, fix16_t newSpread);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setInversionSpread_type;

static_inline void utils_Tonnetz_setInversionSpread_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_setInversionSpread(utils_Tonnetz__ctx_type_8 &_ctx, fix16_t newSpread);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_getChordP_type;

static_inline void utils_Tonnetz_getChordP_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

fix16_t utils_Tonnetz_getChordP(utils_Tonnetz__ctx_type_8 &_ctx, int chordId);

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_getNbChords_type;

static_inline void utils_Tonnetz_getNbChords_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_getNbChords(utils_Tonnetz__ctx_type_8 &_ctx){
   return 6;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_getScaleId_type;

static_inline void utils_Tonnetz_getScaleId_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_getScaleId(utils_Tonnetz__ctx_type_8 &_ctx){
   return _ctx.scaleId;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_getNbScales_type;

static_inline void utils_Tonnetz_getNbScales_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_getNbScales(utils_Tonnetz__ctx_type_8 &_ctx){
   return 20;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_getRoot_type;

static_inline void utils_Tonnetz_getRoot_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline int utils_Tonnetz_getRoot(utils_Tonnetz__ctx_type_8 &_ctx){
   return _ctx.root;
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_setJump_type;

static_inline void utils_Tonnetz_setJump_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

static_inline void utils_Tonnetz_setJump(utils_Tonnetz__ctx_type_8 &_ctx, fix16_t p){
   _ctx.pJump = fix_clip(p,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef utils_Tonnetz__ctx_type_8 utils_Tonnetz_default_type;

static_inline void utils_Tonnetz_default_init(utils_Tonnetz__ctx_type_8 &_output_){
   utils_Tonnetz__ctx_type_8_init(_output_);
   return ;
}

void utils_Tonnetz_default(utils_Tonnetz__ctx_type_8 &_ctx);

typedef struct utils_Arp__ctx_type_0 {
   int step;
   int sequenceSize;
   int sequence[32];
   int playSequence[32];
   fix16_t pRandomize;
   fix16_t pRandomNotes;
   int notes[16];
   int nbNotes;
   int mode;
   uint8_t dirty;
} utils_Arp__ctx_type_0;

typedef utils_Arp__ctx_type_0 utils_Arp_reset_type;

void utils_Arp__ctx_type_0_init(utils_Arp__ctx_type_0 &_output_);

static_inline void utils_Arp_reset_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

void utils_Arp_reset(utils_Arp__ctx_type_0 &_ctx);

typedef utils_Arp__ctx_type_0 utils_Arp_process_type;

static_inline void utils_Arp_process_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

int utils_Arp_process(utils_Arp__ctx_type_0 &_ctx);

typedef utils_Arp__ctx_type_0 utils_Arp__updateSequence_type;

static_inline void utils_Arp__updateSequence_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

void utils_Arp__updateSequence(utils_Arp__ctx_type_0 &_ctx);

typedef utils_Arp__ctx_type_0 utils_Arp_setNotes_type;

static_inline void utils_Arp_setNotes_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

void utils_Arp_setNotes(utils_Arp__ctx_type_0 &_ctx, int (&newNotes)[16]);

typedef utils_Arp__ctx_type_0 utils_Arp_setMode_type;

static_inline void utils_Arp_setMode_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

void utils_Arp_setMode(utils_Arp__ctx_type_0 &_ctx, int newMode);

typedef utils_Arp__ctx_type_0 utils_Arp_setPRandomNotes_type;

static_inline void utils_Arp_setPRandomNotes_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

void utils_Arp_setPRandomNotes(utils_Arp__ctx_type_0 &_ctx, fix16_t p);

typedef utils_Arp__ctx_type_0 utils_Arp_setPRandomize_type;

static_inline void utils_Arp_setPRandomize_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Arp_setPRandomize(utils_Arp__ctx_type_0 &_ctx, fix16_t p){
   _ctx.pRandomize = fix_clip(p,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef utils_Arp__ctx_type_0 utils_Arp_getNbModes_type;

static_inline void utils_Arp_getNbModes_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

static_inline int utils_Arp_getNbModes(utils_Arp__ctx_type_0 &_ctx){
   return 6;
};

typedef utils_Arp__ctx_type_0 utils_Arp_getNbNotes_type;

static_inline void utils_Arp_getNbNotes_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

static_inline int utils_Arp_getNbNotes(utils_Arp__ctx_type_0 &_ctx){
   return _ctx.nbNotes;
};

typedef utils_Arp__ctx_type_0 utils_Arp_getMaxNbNotes_type;

static_inline void utils_Arp_getMaxNbNotes_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

static_inline int utils_Arp_getMaxNbNotes(utils_Arp__ctx_type_0 &_ctx){
   return 16;
};

typedef utils_Arp__ctx_type_0 utils_Arp_getSequenceSize_type;

static_inline void utils_Arp_getSequenceSize_init(utils_Arp__ctx_type_0 &_output_){
   utils_Arp__ctx_type_0_init(_output_);
   return ;
}

static_inline int utils_Arp_getSequenceSize(utils_Arp__ctx_type_0 &_ctx){
   return _ctx.sequenceSize;
};

typedef struct utils_Trigg__ctx_type_0 {
   uint8_t triggers[128];
   int ticks;
   int shift;
   fix16_t ptriggers[128];
   int position;
   int n;
   fix16_t magnitude;
   int length;
   uint8_t isautolength;
   fix16_t evolve;
   int divider;
   uint8_t dirty;
   fix16_t density;
   fix16_t balance;
} utils_Trigg__ctx_type_0;

typedef utils_Trigg__ctx_type_0 utils_Trigg__refresh_type;

void utils_Trigg__ctx_type_0_init(utils_Trigg__ctx_type_0 &_output_);

static_inline void utils_Trigg__refresh_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg__refresh(utils_Trigg__ctx_type_0 &_ctx);

typedef utils_Trigg__ctx_type_0 utils_Trigg_process_type;

static_inline void utils_Trigg_process_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

int utils_Trigg_process(utils_Trigg__ctx_type_0 &_ctx);

typedef utils_Trigg__ctx_type_0 utils_Trigg_restartLoop_type;

static_inline void utils_Trigg_restartLoop_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_restartLoop(utils_Trigg__ctx_type_0 &_ctx){
   _ctx.n = 0;
   utils_Trigg__refresh(_ctx);
}

typedef utils_Trigg__ctx_type_0 utils_Trigg_reset_type;

static_inline void utils_Trigg_reset_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_reset(utils_Trigg__ctx_type_0 &_ctx){
   _ctx.ticks = 0;
   utils_Trigg_restartLoop(_ctx);
}

typedef utils_Trigg__ctx_type_0 utils_Trigg__recompute_type;

static_inline void utils_Trigg__recompute_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg__recompute(utils_Trigg__ctx_type_0 &_ctx);

typedef utils_Trigg__ctx_type_0 utils_Trigg__getAutolength_type;

static_inline void utils_Trigg__getAutolength_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

int utils_Trigg__getAutolength(utils_Trigg__ctx_type_0 &_ctx);

typedef utils_Trigg__ctx_type_0 utils_Trigg__applyLength_type;

static_inline void utils_Trigg__applyLength_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

uint8_t utils_Trigg__applyLength(utils_Trigg__ctx_type_0 &_ctx, int newLength);

typedef utils_Trigg__ctx_type_0 utils_Trigg_setLength_type;

static_inline void utils_Trigg_setLength_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg_setLength(utils_Trigg__ctx_type_0 &_ctx, int newLength);

typedef utils_Trigg__ctx_type_0 utils_Trigg_getLength_type;

static_inline void utils_Trigg_getLength_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline int utils_Trigg_getLength(utils_Trigg__ctx_type_0 &_ctx){
   return _ctx.length;
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_setDivider_type;

static_inline void utils_Trigg_setDivider_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_setDivider(utils_Trigg__ctx_type_0 &_ctx, int newDivider){
   _ctx.divider = int_clip(newDivider,1,newDivider);
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_setShift_type;

static_inline void utils_Trigg_setShift_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_setShift(utils_Trigg__ctx_type_0 &_ctx, int newShift){
   _ctx.shift = int_clip(newShift,0,newShift);
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_setEvolve_type;

static_inline void utils_Trigg_setEvolve_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_setEvolve(utils_Trigg__ctx_type_0 &_ctx, fix16_t newEvolve){
   _ctx.evolve = fix_clip(newEvolve,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_setMagnitude_type;

static_inline void utils_Trigg_setMagnitude_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_setMagnitude(utils_Trigg__ctx_type_0 &_ctx, fix16_t newMagnitude){
   _ctx.magnitude = fix_clip(newMagnitude,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_setBalance_type;

static_inline void utils_Trigg_setBalance_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg_setBalance(utils_Trigg__ctx_type_0 &_ctx, fix16_t newBalance);

typedef utils_Trigg__ctx_type_0 utils_Trigg_setDensity_type;

static_inline void utils_Trigg_setDensity_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg_setDensity(utils_Trigg__ctx_type_0 &_ctx, fix16_t newDensity);

typedef utils_Trigg__ctx_type_0 utils_Trigg_setPosition_type;

static_inline void utils_Trigg_setPosition_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void utils_Trigg_setPosition(utils_Trigg__ctx_type_0 &_ctx, int newPosition){
   _ctx.position = int_clip(newPosition,0,128);
};

typedef utils_Trigg__ctx_type_0 utils_Trigg_default_type;

static_inline void utils_Trigg_default_init(utils_Trigg__ctx_type_0 &_output_){
   utils_Trigg__ctx_type_0_init(_output_);
   return ;
}

void utils_Trigg_default(utils_Trigg__ctx_type_0 &_ctx);

static_inline int utils_Clock_getMinGroupSize(){
   return 2;
};

static_inline int utils_Clock_getMaxGroupSize(){
   return 128;
};

static_inline fix16_t utils_Clock_getMinBPM(){
   return 0x4189 /* 0.256000 */;
};

static_inline fix16_t utils_Clock_getMaxBPM(){
   return 0x75300000 /* 30000.000000 */;
};

static_inline int utils_Clock_getMinTicks(){
   return 1;
};

static_inline int utils_Clock_getMaxTicks(){
   return 32765;
};

int utils_Clock_compareTimeFract(int time1S, fix16_t time1Fract, int time2S, fix16_t time2Fract);

typedef struct utils_Clock__ctx_type_7 {
   int timeS;
   fix16_t timeFract;
   int ticks;
   fix16_t swing;
   int subSize;
   int pos;
   int pendingTicks;
   uint8_t orderMix;
   int lastTimeS;
   fix16_t lastTimeFract;
   int lastTicks;
   int lastBeatS;
   fix16_t lastBeatFract;
   uint8_t init;
   fix16_t ibiB;
   fix16_t ibiA;
   fix16_t ibi;
   int groupSize;
   fix16_t groupRatio;
   fix16_t bpm;
} utils_Clock__ctx_type_7;

typedef utils_Clock__ctx_type_7 utils_Clock_process_type;

void utils_Clock__ctx_type_7_init(utils_Clock__ctx_type_7 &_output_);

static_inline void utils_Clock_process_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

int utils_Clock_process(utils_Clock__ctx_type_7 &_ctx);

typedef utils_Clock__ctx_type_7 utils_Clock_setTime_type;

static_inline void utils_Clock_setTime_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setTime(utils_Clock__ctx_type_7 &_ctx, int newTimeS, fix16_t newTimeFract);

typedef utils_Clock__ctx_type_7 utils_Clock_reset_type;

static_inline void utils_Clock_reset_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

static_inline void utils_Clock_reset(utils_Clock__ctx_type_7 &_ctx){
   _ctx.init = false;
};

typedef utils_Clock__ctx_type_7 utils_Clock__recompute_type;

static_inline void utils_Clock__recompute_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock__recompute(utils_Clock__ctx_type_7 &_ctx);

typedef utils_Clock__ctx_type_7 utils_Clock_setGroupSize_type;

static_inline void utils_Clock_setGroupSize_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setGroupSize(utils_Clock__ctx_type_7 &_ctx, int newGroupSize);

typedef utils_Clock__ctx_type_7 utils_Clock_setGroupRatio_type;

static_inline void utils_Clock_setGroupRatio_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setGroupRatio(utils_Clock__ctx_type_7 &_ctx, fix16_t newGroupRatio);

typedef utils_Clock__ctx_type_7 utils_Clock_setSwing_type;

static_inline void utils_Clock_setSwing_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setSwing(utils_Clock__ctx_type_7 &_ctx, fix16_t newSwing);

typedef utils_Clock__ctx_type_7 utils_Clock_setOrderMix_type;

static_inline void utils_Clock_setOrderMix_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

static_inline void utils_Clock_setOrderMix(utils_Clock__ctx_type_7 &_ctx, uint8_t flag){
   _ctx.orderMix = flag;
};

typedef utils_Clock__ctx_type_7 utils_Clock_getNbTicks_type;

static_inline void utils_Clock_getNbTicks_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

static_inline int utils_Clock_getNbTicks(utils_Clock__ctx_type_7 &_ctx){
   return _ctx.ticks;
};

typedef utils_Clock__ctx_type_7 utils_Clock_getTicks_type;

static_inline void utils_Clock_getTicks_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

int utils_Clock_getTicks(utils_Clock__ctx_type_7 &_ctx);

typedef utils_Clock__ctx_type_7 utils_Clock_getNbNewTicks_type;

static_inline void utils_Clock_getNbNewTicks_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

int utils_Clock_getNbNewTicks(utils_Clock__ctx_type_7 &_ctx);

typedef utils_Clock__ctx_type_7 utils_Clock_setNbTicks_type;

static_inline void utils_Clock_setNbTicks_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setNbTicks(utils_Clock__ctx_type_7 &_ctx, int newTicks);

typedef utils_Clock__ctx_type_7 utils_Clock_setBPM_type;

static_inline void utils_Clock_setBPM_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_setBPM(utils_Clock__ctx_type_7 &_ctx, fix16_t newBPM);

typedef utils_Clock__ctx_type_7 utils_Clock_default_type;

static_inline void utils_Clock_default_init(utils_Clock__ctx_type_7 &_output_){
   utils_Clock__ctx_type_7_init(_output_);
   return ;
}

void utils_Clock_default(utils_Clock__ctx_type_7 &_ctx);



#endif // UTILS_H
