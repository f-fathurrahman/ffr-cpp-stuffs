prefix=`basename $1 .cpp`
FLAGS="-std=c++1z -Wall"
INCLUDE="-I/opt/dealii-9.1.1_gcc_openmpi/include"
LIBS="-Wl,-rpath,/opt/dealii-9.1.1_gcc_openmpi/lib/ -L/opt/dealii-9.1.1_gcc_openmpi/lib/ -ldeal_II"

mpic++ $INCLUDE $FLAGS $1 -o $prefix.x $LIBS
