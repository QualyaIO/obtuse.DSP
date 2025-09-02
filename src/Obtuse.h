
#ifndef OBTUSE_H
#define OBTUSE_H

// all headers in one place

// useful for float_to_fix and fix_to_float
#include "vultin.h"

// generate notes, triggers or gates
#include "utils.h"

// various versions of the effects, depending on buffer size
#include "effects.h"
#include "effectsL.h"
#include "effectsXL.h"

// two flavors of the FM synth, alternate fetch from wavetable on-the-fly, less memory, more CPU, to prefer is the wavetable should change during execution
#include "synthFM.h"
#include "synthFMalt.h"

// drummer kits
#include "synthDrummer.h"
#include "synthDrummerBbox.h"
#include "synthDrummerFoleyType.h"
#include "synthDrummerNes.h"
#include "synthDrummerTamaRockstar.h"

// sampler synths
#include "synthSampler.h"
#include "synthSamplerAmbientLead.h"
#include "synthSamplerAuthenticStrings.h"
#include "synthSamplerBoesendorferGrandPiano.h"
#include "synthSamplerCelesta.h"
#include "synthSamplerCello.h"
#include "synthSamplerClarinet.h"
#include "synthSamplerClassicSuitcaseMk1.h"
#include "synthSamplerCosmos.h"
#include "synthSamplerDreamVoice.h"
#include "synthSamplerDrivenSynthLead.h"
#include "synthSamplerGlassMarimbaSoft.h"
#include "synthSamplerIndianSitar.h"
#include "synthSamplerJapaneseShakuhachiFlute.h"
#include "synthSamplerKoto.h"
#include "synthSamplerMagnificentDrone.h"
#include "synthSamplerMysticVibes.h"
#include "synthSamplerPiano.h"
#include "synthSamplerPowerFifths.h"
#include "synthSamplerPulsingPatterns.h"
#include "synthSamplerShootingStar.h"
#include "synthSamplerSoftClarinet.h"
#include "synthSamplerTimeWarp.h"
#include "synthSamplerTranquility.h"
#include "synthSamplerVocalCluster.h"
#include "synthSamplerZenGarden.h"

#endif
