#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "sprig/sprig.h"
#include "wayang/wayang.h"

int main()
{
  printf("test_kelir started ...\n");

  kOpen( 800, 600, (char*)"./images/wayang/kelir_01.jpg");
  kSetCaption("Caption pertama");
  dPause(10000);
  
  printf("After 1st caption: ticks = %d\n", dGetTicks());

  //kOpen( 800, 600, (char*)"./images/wayang/keraton.jpg" );
  kSetImage( (char*)"./images/wayang/keraton.jpg" );
  kSetCaption("Caption kedua");
  dPause(10000);
  
  printf("After 2nd caption: ticks = %d\n", dGetTicks());
  // dGetTicks will return error when there is no
  // instance of Kelir

  
  kSetRGB(150,150,150);
  kCircle(0,0,40);
  dPause(10000);

  printf("After 1st circle: ticks = %d\n", dGetTicks());

  kSetRGB(250,0,0);
  kFillCircle(50,50,40);
  dPause(10000);
  
  printf("After 2nd circle: ticks = %d\n", dGetTicks());
 
  kSetRGB(0,250,0);
  kFillCircle(-50,50,40);
  dPause(10000);
  
  printf("After 3rd circle: ticks = %d\n", dGetTicks());

  kSetRGB(0,0,250);
  kFillCircle(0,-50,40);
  dPause(10000);

  printf("After 4th circle: ticks = %d\n", dGetTicks());

  kClose();
  // Call this before the program ends to
  // avoid any segmentation faults.

  printf("test_kelir ended ...\n");
  return 0;
}
