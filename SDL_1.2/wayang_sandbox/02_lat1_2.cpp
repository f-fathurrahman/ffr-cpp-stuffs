#include "sprig/sprig.h"
#include "wayang/wayang.h"

void lat1_2()
{
  kSetCaption("Praktikum 1.2");

  kSetColor(YELLOW);
  kFillArc(0, 210, 50, -60, 240);
}

int main()
{

  kOpen(800, 600, "images/alam/kelir_01.jpg");
  lat1_2();

  dPause(10000);

  return 0;
}
