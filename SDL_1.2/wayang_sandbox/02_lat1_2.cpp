#include "sprig/sprig.h"
#include "wayang/wayang.h"

char* AUTHOR_NAME = "Fadjar Fathurrahman";
int   AUTHOR_NIM  = 13306023;
 
void about()
{
  printf("Oleh : %s\n", AUTHOR_NAME);
  printf("NIM  : %d\n", AUTHOR_NIM);
}


void lat1_2()
{
  kSetCaption("Praktikum 1.2");

  kSetColor(YELLOW);
  kFillArc(0, 210, 50, -60, 240);
  kSetOpaque(40);
  kFillCircle(0, 210, 100);

  kSetOpaque(150);
  kFillRectangle(-400, -260, 800, 120);

  kSetColor(WHITE);
  kSetOpaque(50);
  kSetThickness(10);
  kRectangle(-380, -240, 760, 80);
}

int main()
{

  printf("Praktikum Pemrograman C\n");
  about();

  kOpen(800, 600, "images/alam/kelir_01.jpg");

  lat1_2();

  dPause(10000);

  kClose();

  return 0;
}
