#!/bin/bash
basn=`basename $1 .cpp`

rm -vf $basn.x

# Tested for Ubuntu 18.04
# Also include trilinos because it is not included in the INCLUDE path.
mpic++ -std=c++11 -I/usr/include/trilinos -Wall $1 -o $basn.x -ldeal.ii

echo "Executable: $basn.x"
