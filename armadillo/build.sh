#!/bin/bash

# Armadillo is installed under /usr

basn=`basename $1 .cpp`

rm -vf $basn.x
g++ -Wall $1 -o $basn.x -larmadillo -lblas -llapack
echo "Executable: $basn.x"
