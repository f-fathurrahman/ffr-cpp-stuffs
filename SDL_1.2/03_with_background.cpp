#include "SDL/SDL.h"
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32; // bits per pixel

SDL_Surface* load_image( string filename )
{
  SDL_Surface *loadedImage = NULL;
  SDL_Surface *optimizedImage = NULL;

  loadedImage = SDL_LoadBMP( filename.c_str() );

  // the bitmap is 24-bit, the screen is 32-bit
  // convert to optimized version

  if( loadedImage != NULL ) {
    // create an optimized image
    optimizedImage = SDL_DisplayFormat( loadedImage );
    SDL_FreeSurface( loadedImage );
  }

  return optimizedImage;
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
  // temporary rectangle to hold the offsets
  SDL_Rect offset;

  // give the offsets to the rectangle
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface( source, NULL, destination, &offset );
}


int main( int argc, char **argv )
{
  SDL_Surface* message = NULL;
  SDL_Surface* background = NULL;
  SDL_Surface* screen = NULL;

  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    return 1;
  }

  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

  if( screen == NULL ) {
    return 1;
  }

  // set window caption
  SDL_WM_SetCaption( "Hello World", NULL );

  // load the images
  message = load_image("images/02/hello.bmp");
  background = load_image("images/02/background.bmp");

  // apply the background to the screen
  apply_surface( 0, 0, background, screen );
  apply_surface( 320, 0, background, screen );
  apply_surface( 0, 240, background, screen );
  apply_surface( 320, 240, background, screen );
  apply_surface( 180, 140, message, screen );

  // update screen
  // needed, without this the screen will only display black background
  if( SDL_Flip(screen) == -1 ) {
    return 1;
  }

  SDL_Delay( 2000 );
  SDL_FreeSurface( message );
  SDL_FreeSurface( background );

  SDL_Quit();

  return 0;
}
