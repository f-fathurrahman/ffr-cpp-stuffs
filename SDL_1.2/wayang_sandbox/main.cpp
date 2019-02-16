#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <cfloat>
#include <climits>


#include "sprig/sprig.h"
#include "wayang/wayang.h"


#include "praktikum1.cpp"
#include "praktikum2.cpp"
#include "praktikum3.cpp"
#include "praktikum4.cpp"

int main()
{

  const int TPAUSE = 10000;

  about();

  kOpen(800, 600, "images/layar/kelir_01.jpg");

  lat1_2();
  dPause(TPAUSE);

  lat1_3();
  dPause(TPAUSE);

  lat1_4();
  dPause(TPAUSE);

  data_types();

  lat2_1();

  lat2_2();
  dPause(TPAUSE);

  lat2_3();
  dPause(TPAUSE);

  lat2_4();
  dPause(TPAUSE);

  lat3_1();
  dPause(TPAUSE);

  lat4_1();
  dPause(TPAUSE);

  kClose();

  return 0;
}
