prefix=`basename $1 .cpp`

#FLAGS="-Wall -O0 -g -ftemplate-depth-512 -std=c++0x"

FLAGS=""

INCLUDE="-I/opt/dealii-9.1.1_gcc_openmpi/include"

#LIBS="libjdftx.a -lgsl -lfftw3_threads -lfftw3 -lcblas -lopenblas -lpthread"
#LIBS="-L ./ -ljdftx -lgsl -lfftw3_threads -lfftw3 -lcblas -lopenblas -lpthread"

LIBS="-Wl,-rpath,/opt/dealii-9.1.1_gcc_openmpi/lib/ -L/opt/dealii-9.1.1_gcc_openmpi/lib/ -ldeal_II"

mpic++ $INCLUDE $FLAGS $1 -o $prefix.x $LIBS
