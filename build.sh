#!/bin/bash
basn=`basename $1 .cpp`

rm -vf $basn.x
g++ -std=c++11 -Wall $1 -o $basn.x
echo "Executable: $basn.x"
