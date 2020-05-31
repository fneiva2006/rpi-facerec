#!/bin/bash

echo "bash script unleashed"
cd bin
./Record_from_Headset.sh -q		#for STT
./Playback_to_Lineout.sh -q			#for TTS
cd /home/pi/pocketsphinx-0.8/src/programs	#go to correct directory
export LD_LIBRARY_PATH=/usr/local/lib		#set shared library paths
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
#run continuous program and save log and transcript files
pocketsphinx_continuous -lm "$1".lm -dict "$1".dic -samprate 48000 -nfft 2048 -adcdev sysdefault |tee olog.log |grep --line-buffered '^0' > /home/pi/Documents/codeblocks/v10_speech/stt.txt

#8661