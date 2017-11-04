#include "SDL/SDL.h"

int main()
{
  // declare two images that we will use
  SDL_Surface* hello = NULL;
  SDL_Surface* screen = NULL;

  // start SDL
  SDL_Init( SDL_INIT_EVERYTHING );

  // screen
  screen = SDL_SetVideoMode( 320, 240, 32, SDL_SWSURFACE );
  // SDL_SWSURFACE: create video surface in system memory

  // load image
  hello = SDL_LoadBMP( "images/hello.bmp" );

  // apply image to the screen
  SDL_BlitSurface( hello, NULL, screen, NULL );

  // update screen
  SDL_Flip( screen );

  // pause
  SDL_Delay( 2000 );

  // free memory 
  SDL_FreeSurface( hello );

  // quit SDL
  // also delete memory for screen
  SDL_Quit();

  return 0;
}

