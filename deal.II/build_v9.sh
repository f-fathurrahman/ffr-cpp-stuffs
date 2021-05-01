prefix=`basename $1 .cpp`
FLAGS="-std=c++1z -Wall"

DEALII_HOME="/opt/dealii-9.2.0_gcc_openmpi"

INCLUDE="-I${DEALII_HOME}/include \
-I/usr/include/trilinos
"

echo $INCLUDE

LIBS="-Wl,-rpath,${DEALII_HOME}/lib/ -L${DEALII_HOME}/lib -ldeal_II \
-ltrilinos_teuchoscomm -ltrilinos_teuchoscore"

mpic++ $INCLUDE $FLAGS $1 -o $prefix.x $LIBS
