#!/bin/bash
basn=`basename $1 .cpp`

rm -vf $basn.x

g++ -I/usr/include/SDL -Wall $1 -o $basn.x libmain.a -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

echo "Executable: $basn.x"
