#include <string>
#include <cstdio>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface* image = NULL;
SDL_Surface* screen = NULL;

SDL_Event event;

SDL_Surface *load_image( string filename )
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  //
  loadedImage = IMG_Load( filename.c_str() );
  if( loadedImage != NULL ) {
    optimizedImage = SDL_DisplayFormat( loadedImage );
    SDL_FreeSurface( loadedImage ); // immediately free the memory
  }
  //
  return optimizedImage;
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface( source, NULL, destination, &offset );
}


bool init()
{
  // everything init
  if( SDL_Init(SDL_INIT_EVERYTHING) == -1 ) {
    return false;
  }
  
  // screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  if( screen == NULL ) {
    return false;
  }
  
  // set window caption
  SDL_WM_SetCaption("Event test", NULL );
  
  // everything is OK, so return true
  return true;
}

bool load_files()
{
  // load image
  image = load_image("images/04/x.png");
  if( image == NULL ) {
    printf("ERROR in calling load_image\n");
    return false;
  }
  return true;
}


void clean_up()
{
  SDL_FreeSurface( image );
  SDL_Quit();
}


int main( int argc, char** argv )
{
  bool quit = false;

  if( init() == false ) {
    printf("ERROR in calling init()\n");
    return 1;
  }

  if( load_files() == false ) {
    printf("ERROR in calling load_files\n");
    return 1;
  }

  apply_surface( 0, 0, image, screen );

  // don't forget to update
  if( SDL_Flip( screen ) == -1 ) return 1;

  while( quit == false ) {
    while( SDL_PollEvent( &event ) ) {
      if( event.type == SDL_QUIT ) {
        printf("SDL_QUIT event is true\n");
        quit = true;
      }
    }
  }


  clean_up();
  return 0;
}

