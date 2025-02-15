#!/bin/bash

echo "Generate FM synth with on-the-fly wavetable"
vultc -ccode vult/voice.vult -template arduino -real fixed -i vult/wavetable_small -i vult/synth_FMalt -i vult/buffer_small -o src/synthFMalt -output-prefix synthFMalt_


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

# fix progmem-related code to work with the 32bit variables we have
echo "Hack pgm_read_word to pgm_read_dword"
sed -i 's/pgm_read_word/pgm_read_dword/g' src/*

echo "FIXME: actually some more hack are involved, as the "arduino" template wrongly put pgm_read_word for *all* arrays. Actually as it happens (and it might change upon code revision) only the .h files should be generated with the arduino template, the cpp should be generated without this template.".
