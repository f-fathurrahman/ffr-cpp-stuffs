#!/bin/bash
basn=`basename $1 .cpp`

rm -vf $basn.x
mpic++ -I/usr/include/trilinos -Wall $1 -o $basn.x -ldeal.ii
echo "Executable: $basn.x"
