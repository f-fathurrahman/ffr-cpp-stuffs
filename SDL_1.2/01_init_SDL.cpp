#include "SDL/SDL.h"
#include <stdio.h>

int main()
{
  printf("Initializing SDL.\n");

  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_VIDEO ) == -1 ) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(-1);
  }

  printf("SDL initialized.\n");
  printf("Quitting SDL.\n");

  SDL_Quit();

  return 0;
}


