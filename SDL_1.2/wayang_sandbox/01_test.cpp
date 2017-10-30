#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "sprig/sprig.h"
#include "wayang/wayang.h"

int main()
{
  printf("LATIHAN SDL 2017\n");
  
  kOpen(800, 600, "images/layar/infantis_146.jpg");
  kSetCaption("Test");
  
  kSetCaption("ffr caption");
  dPause(5000);
  
  //program berhenti selama 10000 ms
  dPause(100000); //program berhenti selama 100000 ms
  
  kClose();
  
  //tutup layar
  return 0;
}


