#!/bin/bash
basn=`basename $1 .cpp`

LIBS=`pkg-config --libs opencv`

rm -vf $basn.x

g++ -Wall $1 -o $basn.x $LIBS

echo "Executable: $basn.x"

