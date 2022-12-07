#!/bin/bash

echo "Generate FM synth"
vultc -ccode voice.vult -real fixed -i synth_FM -o synthFM -output-prefix synthFM_

# not needed anymore nor desirable since the morphed wavetables will be in RAM anyway
#echo "(setting wavetables to RAM)"
#sed -i 's/static const fix16_t/static const fix16_t __not_in_flash("vult")/g' synthFM.tables.h


echo "Generate Sampler synth"
vultc -ccode voice.vult -real fixed -i synth_sampler -o synthSampler -output-prefix synthSampler_

echo "Generate Drummer synth"
vultc -ccode voice.vult -real fixed -i synth_drummer -o synthDrummer -output-prefix synthDrummer_

echo "Generate Effects"
vultc -ccode reverb.vult ladder.vult SVF.vult -real fixed -o effects -output-prefix effects_
