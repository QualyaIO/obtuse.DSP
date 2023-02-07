
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "utils.tables.h"

typedef struct utils_Trigg__ctx_type_0 {
   uint8_t triggers[128];
   int ticks;
   int shift;
   fix16_t ptriggers[128];
   int position;
   int n;
   fix16_t magnitude;
   int length;
   fix16_t evolve;
   int divider;
   uint8_t dirty;
   fix16_t density;
   fix16_t balance;
   uint8_t autolength;
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



#endif // UTILS_H
