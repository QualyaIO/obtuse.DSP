#!/bin/bash

echo "Generate FM synth"
vultc -ccode voice.vult -real fixed -i synth_FM -o synthFM -output-prefix synthFM_

echo "Generate Sampler synth"
vultc -ccode voice.vult -real fixed -i synth_sampler -o synthSampler -output-prefix synthSampler_

echo "Generate Drummer synth"
vultc -ccode voice.vult -real fixed -i synth_drummer -o synthDrummer -output-prefix synthDrummer_

echo "Generate Effects"
vultc -ccode reverb.vult ladder.vult SVF.vult -real fixed -o effects -output-prefix effects_
