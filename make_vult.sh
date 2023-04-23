#!/bin/bash

echo "Generate FM synth"
vultc -ccode vult/voice.vult -real fixed -i vult/synth_FM -i vult/buffer_medium -o src/synthFM -output-prefix synthFM_

# not needed anymore nor desirable since the morphed wavetables will be in RAM anyway
#echo "(setting wavetables to RAM)"
#sed -i 's/static const fix16_t/static const fix16_t __not_in_flash("vult")/g' synthFM.tables.h


echo "Generate Sampler synth ocarina"
# this is the default sampler
vultc -ccode vult/voice.vult -real fixed -i vult/synth_sampler -i vult/synth_sampler/ocarina -i vult/buffer_medium -o src/synthSampler -output-prefix synthSampler_

echo "Generate Sampler synth celesta"
# this is the default sampler
vultc -ccode vult/voice.vult -real fixed -i vult/synth_sampler -i vult/synth_sampler/celesta -i vult/buffer_medium -o src/synthSamplerCelesta -output-prefix synthSamplerCelesta_

echo "Generate Drummer synth"
vultc -ccode vult/voice.vult -real fixed -i vult/synth_drummer -i vult/buffer_medium -o src/synthDrummer -output-prefix synthDrummer_

echo "Generate Effects"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult -i vult/buffer_medium -real fixed -o src/effects -output-prefix effects_

# actually sequencing
echo "Generate Utils"
vultc -ccode vult/trigg.vult vult/clock.vult vult/tonnetz.vult vult/arp.vult vult/gate.vult -i vult/buffer_medium -real fixed -o src/utils -output-prefix utils_

echo "Generate Effects with large buffer"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult -i vult/buffer_large -real fixed -o src/effectsL -output-prefix effectsL_

echo "Generate Effects with extra large buffer"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult -i vult/buffer_extra_large -real fixed -o src/effectsXL -output-prefix effectsXL_

echo "Hack init"
# check at best as we can that we will replace the correct pieces
INIT_STRUCT_COUNT=`grep ".*_ctx_type_.* _ctx;" src/* | wc -l`
INIT_SET_COUNT=`grep "_output_ = _ctx;" src/* | wc -l`

if [ "$INIT_STRUCT_COUNT" = "$INIT_SET_COUNT" ] ; then
    echo "Will replace $INIT_STRUCT_COUNT occurrences"
    # he wave to go through each file to prevent sed to update file even without any match
    # FIXME: actually useless because vult will next time override due to changes.
    # So we could also check for `grep "void .*__ctx_type_.*_init(.*__ctx_type.* &_output_){" src/* | wc -l` ?
    for FILE in src/*
    do
	INIT_NB=`grep ".*_ctx_type_.* _ctx;" $FILE | wc -l`;
	if [ $((INIT_NB))  -gt 0 ] ; then
	    sed -i "s/\(.*\)_ctx_type_\(.*\) _ctx;/\1_ctx_type_\2 \&_ctx = _output_;/" $FILE
	    sed -i "s/_output_ = _ctx;//" $FILE
	fi
    done
else
    echo "ABORT: mismatch between struct ($INIT_STRUCT_COUNT) and affectation ($INIT_SET_COUNT) count."
fi
