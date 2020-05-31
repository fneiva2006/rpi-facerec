# Author: Enrico Miraglia
# July 2016

#echo "$1"| text2wave -o temp.wav	#festival engine
espeak -ven+f2 -w temp.wav "$1"	#espeak engine - more customisation
#espeak -v "$2" -w temp.wav "$1"
sox temp.wav -c2 -r22050 speech.wav
aplay -Dplug:default speech.wav
rm speech.wav
rm temp.wav
