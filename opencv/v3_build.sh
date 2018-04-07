#!/bin/bash
basn=`basename $1 .cpp`

PRE=/home/efefer/mysoftwares/opencv-3.4.1
PRELIB=$PRE/lib
CORE=$PRELIB/libopencv_core.a

ITT=$PRE/share/OpenCV/3rdparty/lib/libittnotify.a

INC="-I$PRE/include"

LIBS="$CORE $ITT -lblas -llapack -lpthread -lz -ldl"

rm -vf $basn.x

g++ -Wall $INC $1 -o $basn.x $LIBS

echo "Executable: $basn.x"

