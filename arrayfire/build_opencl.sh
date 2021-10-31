prefix=`basename $1 .cpp`
FLAGS="-std=c++11 -Wall" # need std=c++11 ?

ARRAYFIRE_HOME="/home/efefer/mysoftwares/arrayfire-3.7.3"

INCLUDE="-I${ARRAYFIRE_HOME}/include "

echo $INCLUDE

LIBS="-Wl,-rpath,${ARRAYFIRE_HOME}/lib/ -L${ARRAYFIRE_HOME}/lib -lafopencl -laf"

g++ $INCLUDE $FLAGS $1 -o "${prefix}_opencl.x" $LIBS
