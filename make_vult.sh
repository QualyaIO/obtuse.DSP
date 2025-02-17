#!/bin/bash

echo "Generate FM synth"
vultc -ccode vult/voice.vult -real fixed -i vult/wavetable_medium -i vult/synth_FM -i vult/buffer_medium -o src/synthFM -output-prefix synthFM_

echo "Generate FM synth with on-the-fly wavetable"
vultc -ccode vult/voice.vult -real fixed -i vult/wavetable_medium -i vult/synth_FMalt -i vult/buffer_medium -o src/synthFMalt -output-prefix synthFMalt_

# With FMalt it could be interesting to force wavetables to RAM rather than flash on some platformes, e.g. for RP2040:
#echo "(setting wavetables to RAM)"
#sed -i 's/static const fix16_t/static const fix16_t __not_in_flash("vult")/g' src/synthFMalt.tables.h

# loop all instruments in the sampler, retrieve id
for i in `ls -d ./vult/synth_sampler/*/ | cut -f4 -d'/'`; do
    echo "Generate Sampler synth $i"
    # uppercase first letter of id 
    # WARNING: only works with bash >= 4
    PREFIX="synthSampler${i^}"
    # special treatment for default instrument
    if [ $i == "ocarina" ] ; then
	PREFIX="synthSampler"
    fi
    vultc -ccode vult/voice.vult -real fixed -i vult/synth_sampler -i vult/synth_sampler/$i -i vult/buffer_medium -o src/${PREFIX} -output-prefix ${PREFIX}_
done

# same for drummer
for i in `ls -d ./vult/synth_drummer/*/ | cut -f4 -d'/'`; do
    echo "Generate Drummer synth $i"
    # uppercase first letter of id 
    # WARNING: only works with bash >= 4
    PREFIX="synthDrummer${i^}"
    # special treatment for default instrument
    if [ $i == "808" ] ; then
	PREFIX="synthDrummer"
    fi
    vultc -ccode vult/voice.vult -real fixed -i vult/synth_drummer -i vult/synth_drummer/$i -i vult/buffer_medium -o src/${PREFIX} -output-prefix ${PREFIX}_
done

echo "Generate Effects"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult vult/saturator.vult -i vult/buffer_medium -real fixed -o src/effects -output-prefix effects_

# actually sequencing
echo "Generate Utils"
vultc -ccode vult/trigg.vult vult/clock.vult vult/chord.vult vult/arp.vult vult/gate.vult -i vult/buffer_medium -real fixed -o src/utils -output-prefix utils_

echo "Generate Effects with large buffer"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult vult/saturator.vult -i vult/buffer_large -real fixed -o src/effectsL -output-prefix effectsL_

echo "Generate Effects with extra large buffer"
vultc -ccode vult/reverb.vult vult/ladder.vult vult/SVF.vult vult/combFB.vult vult/allpass.vult vult/combFF.vult vult/saturator.vult -i vult/buffer_extra_large -real fixed -o src/effectsXL -output-prefix effectsXL_

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
