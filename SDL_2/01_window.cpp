#include <SDL2/SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main()
{
  // initialize SDL
  if( SDL_Init(SDL_INIT_EVERYTHING) >= 0 ) {
    g_pWindow = SDL_CreateWindow("Setting up SDL",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                640, 480, SDL_WINDOW_SHOWN);
    // initialize renderer if
    if(g_pWindow != 0) {
      g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    }
  }
  else {
    // error
    printf("ERROR: Could not initialize SDL\n");
    return -1;
  }

  // set to black RGB 0 0 0
  SDL_SetRenderDrawColor(g_pRenderer, 100, 0, 0, 255);

  // clear the window to black
  SDL_RenderClear(g_pRenderer);

  // show to window
  SDL_RenderPresent(g_pRenderer);

  // set a delay before quitting
  SDL_Delay(5000);
  
  // clean up SDL
  SDL_Quit();

  return 0;
}

