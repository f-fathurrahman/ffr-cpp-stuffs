#!/bin/bash
basn=`basename $1 .cpp`

rm -vf $basn.x
g++ -std=c++11 -Wall $1 -o $basn.x -lSDL -lSDL_image
echo "Executable: $basn.x"
