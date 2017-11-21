#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "sprig/sprig.h"
#include "wayang/wayang.h"

hUkoro teks1, teks2, teks3, teks4, teks5;

void test1()
{
  kSetCaption("Menggunakan Ukoro");
  // permanant text
  hUkoro teks1 = uCreate("fonts/truetype/BaroqueScript.ttf", 20);
  uSetColor(teks1,BLACK);
  uPrintL(teks1, 0, 260, "Teks ditulis dengan uPrintL");
  uPrintC(teks1, 0, 220, "Teks ditulis dengan uPrintC");
  uPrintR(teks1, 0, 180, "Teks ditulis dengan uPrintR");
}

void test2()
{
  char str[]="FTI ITB Tahun 2012";
  
  hUkoro teks2 = uCreate("fonts/truetype/freefont/FreeSerif.ttf", 20);
  uSetColor(teks2, RED);
  
  uSetText(teks2, "%s dengan uSetText-LEFT", str);
  uJumpTo(teks2, 0, 130);
  uSetMode(teks2, MODE_LEFT + MODE_SHOW);
  dPause(1000);

  uJumpTo(teks2, 0, 230);
  uSetMode(teks2, MODE_LEFT + MODE_SHOW);
  dPause(1000);
  
  teks3 = uClone(teks2);
  uSetColor(teks3, YELLOW);
  uSetText(teks3, "%s dengan uSetText-CENTER", str);
  uJumpTo(teks3, 0, 100);
  uSetMode(teks3, MODE_CENTER + MODE_SHOW);
  dPause(1000);
  
  teks4 = uClone(teks2);
  uSetColor(teks4, BLUE);
  uSetText(teks4, "%s dengan uSetText-RIGHT", str);
  uJumpTo(teks4, 0, 70);
  uSetMode(teks4, MODE_RIGHT + MODE_SHOW);
  dPause(1000);
}

void test3()
{
  hUkoro teks5 = uCreate("fonts/truetype/freefont/FreeSerif.ttf", 20);
  uSetColor(teks5, BLACK);
  uSetText(teks5, "Running text");
  for(int j=410; j > -400; j=j-1) {
    uJumpTo(teks5,j,-250);
    uSetMode(teks5, MODE_RIGHT + MODE_SHOW);
    printf("j = %d\n", j);
  }
}

int main()
{
  kOpen(800, 600, "images/layar/infantis_246.jpg");

  //test1();
  //dPause(3000);

  //test2();
  //dPause(3000);
  
  test3();
  dPause(3000);

  kClose();

  return 0;
}

