#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../sprig/sprig.h"
#include "wayang.h"

#define between(v,a,b) ((v>a) && (v<b))
#define outside(v,a,b) ((v<a) || (v>b))

#define kX(x) (kelir.xs + (x))
#define kY(y) (kelir.ys - (y))

#define kDX(x) (kelir.xd + (x))
#define kDY(y) (kelir.yd - (y))

#define wX(w) (w->x)
#define wY(w) (w->y)

char* font_path = "fonts/truetype/";
char* image_path = "images/";
char* sound_path = "sounds/";

Kelir kelir;
Dalang dalang;

int sStart();
void sFinish();

char print_buffer[PRINT_MAX+1];

bool enable_log = false;

void logPrintf(char* fmt, ...) {
    if (enable_log) {
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

SDL_Surface* cLoadImage(char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL) {
        strncpy(print_buffer, image_path, PRINT_MAX);
        strncat(print_buffer, filename, PRINT_MAX);
        image = IMG_Load(print_buffer);
        if (image == NULL) {
            logPrintf("IMG_Load: %s\n", IMG_GetError());
            return NULL;
        }
    }
    return image;
}

Citra* cvLoad(int max, va_list ap) {
    Citra* t1;
    t1 = (Citra*) malloc(sizeof(Citra)+max*sizeof(SDL_Surface*));
    if (t1 == NULL) {
        logPrintf("gGambarLoad: not enough memory\n");
        return NULL;
    }
    t1->max = max;
    int i;
    for (i=0; i<max; i++) {
        t1->images[i]=cLoadImage(va_arg( ap, char* ));
    }
    t1->images[i]=NULL; // MARK
    t1->count = 0;
    logPrintf("Citra loaded (%d)\n", max);
    return t1;
}

Citra* csLoad(int max, char* fname) {
    Citra* t1;
    char str[255];
    t1 = (Citra*) malloc(sizeof(Citra)+max*sizeof(SDL_Surface*));
    if (t1 == NULL) {
        logPrintf("gGambarLoad: not enough memory\n");
        return NULL;
    }
    t1->max = max;
    int i;
    for (i=0; i<max; i++) {
        sprintf(str, "%s%04d.png", fname, i+1);
        t1->images[i]=cLoadImage(str);
    }
    t1->images[i]=NULL; // MARK
    t1->count = 0;
    logPrintf("Citra loaded (%d)\n", max);
    return t1;
}


Citra* cLoad(int num, ...) {
    Citra* g;
    va_list ap;
    va_start(ap, num);
    g = cvLoad(num, ap);
    va_end(ap);
    return g;
}

Citra* cUse(Citra* c) {
    if (c!=NULL) {
        c->count++;
        return c;
    }
    return NULL;
}

void cFree(Citra *g) {
    g->count--;
    if (g->count <= 0) {
        int i;
        for (i=0; i<g->max; i++) {
            if (g->images[i]) SDL_FreeSurface(g->images[i]);
        }
        free(g);
        logPrintf("Citra deleted\n");
    }
    else {
        logPrintf("Citra deleted\n");
    }
}

TTF_Font* aLoadFont(char* filename, int size) {
    TTF_Font* font = TTF_OpenFont(filename, size);
    if (font == NULL) {
        strncpy(print_buffer, font_path, PRINT_MAX);
        strncat(print_buffer, filename, PRINT_MAX);
        font = TTF_OpenFont(print_buffer, size);
        if (font == NULL) {
            logPrintf("TTF_OpenFont: %s\n", TTF_GetError());
            return NULL;
        }
    }
    return font;
}

Aksara* aLoad(char *filename, int size) {
    Aksara* t1;
    t1 = (Aksara*) malloc(sizeof(Aksara));
    if (t1 == NULL) {
        printf("AksaraLoad: not enough memory\n");
        return NULL;
    }
    t1->font = aLoadFont(filename, size);
    if (t1->font == NULL) {
        free(t1);
        return NULL;
    }
    t1->count = 0;
    logPrintf("Aksara %s loaded\n", filename);
    return t1;
}

Aksara* aUse(Aksara* i) {
    if (i!=NULL) {
        i->count++;
        return i;
    }
    return NULL;
}

void aFree(Aksara* i) {
    i->count--;
    if (i->count <= 0) {
        TTF_CloseFont(i->font);
        free(i);
        logPrintf("Aksara deleted\n");
    }
    else logPrintf("Aksara released\n");
}

Mix_Chunk* gLoadSound(char* filename) {
    Mix_Chunk* sound = Mix_LoadWAV(filename);
    if (sound == NULL) {
        strncpy(print_buffer, sound_path, PRINT_MAX);
        strncat(print_buffer, filename, PRINT_MAX);
        sound = Mix_LoadWAV(print_buffer);
        if (sound == NULL) {
            logPrintf("Mix_LoadWAV: %s\n", Mix_GetError());
            return NULL;
        }
    }
    return sound;
}

Gending* gvLoad(int max, va_list ap) {
    Gending* t1;
    t1 = (Gending*) malloc(sizeof(Gending)+max*sizeof(Mix_Chunk*));
    if (t1 == NULL) {
        logPrintf("GendingLoad: not enough memory\n");
        return NULL;
    }
    int i;
    for (i=0; i<max; i++) {
        t1->chunks[i]=gLoadSound(va_arg( ap, char* ));
    }
    t1->chunks[i]=NULL; // MARK
    t1->max = max;
    t1->count = 0;
    logPrintf("Gending loaded (%d)\n", max);
    return t1;
}

Gending* gLoad(int max, ...) {
    Gending* g;
    va_list ap;
    va_start(ap, max);
    g = gvLoad(max, ap);
    va_end(ap);
    return g;
}

Gending* gUse(Gending* i) {
    if (i!=NULL) {
        i->count++;
        return i;
    }
    return NULL;
}

void gFree(Gending *g) {
    g->count--;
    if (g->count <= 0) {
        int i;
        for (i=0; i<g->max; i++) {
            if (g->chunks[i]) Mix_FreeChunk(g->chunks[i]);
        }
        free(g);
        logPrintf("Gending deleted\n");
    }
    else {
        logPrintf("Gending released\n");
    }
}


//======================================================================
int kOpen(int width, int height, char *filename, Uint16 mode) {
    logPrintf("Kelir is opening\n");

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf( "SDL_Init: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    kelir.device = SDL_SetVideoMode(width, height, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !kelir.device ) {
        printf("SDL_SetVideoMode: %s\n", SDL_GetError());
        return 2;
    }

    if(TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 3;
    }
    else {
        atexit(TTF_Quit);
    }

    if ( Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
        printf("Mix_OpenAudio: %s\n", SDL_GetError());
        return 4;
    }

    kSetImage(filename, mode);
    if (kelir.screen == NULL) {
        printf("KOpen: Failed to set image %s\n", filename);
        return 5;
    }

    kelir.autoRefresh = true;
    kelir.alpha = 255;
    kelir.fcolor = SDL_MapRGB(kelir.device->format, 0,0,0);
    kelir.bcolor = SDL_MapRGB(kelir.device->format, 255,255,255);
    kelir.thickness = 1;
    SPG_PushThickness(kelir.thickness);

    lInit(&kelir.wList);
    lInit(&kelir.uList);
    lInit(&kelir.gList);
    kAutoRefresh();
    return 0;
}

void kClose() {
    kelir.autoRefresh = false;
    logPrintf("Kelir is closing ...\n");

    while(kelir.gList.first != NULL) {
        gDelete((Gamelan*)kelir.gList.first);
    }

    while( kelir.wList.first != NULL ) {
        wDelete((Wayang*)kelir.wList.first);
    }

    while( kelir.uList.first != NULL) {
        uDelete((Ukoro*) kelir.uList.first);
    }
    TTF_Quit();

    if (kelir.screen != NULL) {
        logPrintf("Kelir free citra\n");
        SDL_FreeSurface(kelir.screen);
    }

    SDL_Quit();
    logPrintf("Kelir finished\n");
}

void kSetCaption(const char* caption) {
    SDL_WM_SetCaption( caption, NULL );
    printf("\n%s\n", caption);
}

void kSetImage(char *filename, Uint16 mode) {
    SDL_Surface *temp1 = NULL;
    if (filename != NULL) {
        temp1 = cLoadImage(filename);
        /*
        if ((temp1->h != kelir.device->h) || (temp1->w != kelir.device->w)) {
            double scaleX = ((double) kelir.device->w) / ((double) temp1->w);
            double scaleY = ((double) kelir.device->h) / ((double) temp1->h);
            SDL_Surface *temp2 = SPG_Transform(temp1,
                0x000000, 0, scaleX, scaleY, SPG_TAA);
            if (temp2 != NULL) {
                SDL_FreeSurface(temp1);
                temp1 = temp2;
            }
        }
        */
    }
    if (temp1 == NULL) {
        temp1 = SPG_CreateSurface32(0, kelir.device->w, kelir.device->h);
        if (temp1 == NULL) {
            logPrintf("gSetImage: Error creating image\n");
            return;
        }
    }
    if (kelir.screen != NULL) {
        SDL_FreeSurface(kelir.screen);
    }
    kelir.screen = temp1;

    if (mode & MODE_BOTTOM) {
        kelir.ys = kelir.screen->h;
    }
    else if (mode & MODE_TOP) {
        kelir.ys = 0;
    }
    else {
        kelir.ys = kelir.screen->h / 2;
    }

    if (mode & MODE_LEFT) {
        kelir.xs = 0;
    }
    else if (mode & MODE_RIGHT) {
        kelir.xs = kelir.screen->w;
    }
    else {
        kelir.xs = kelir.screen->w/2;
    }
    logPrintf("Kelir world : %d,%d\n", kelir.screen->w, kelir.screen->h);
    logPrintf("Kelir offset: %d,%d (%04X)\n", kelir.xs, kelir.ys, mode);
    kSetScroll(mode);

    kAutoRefresh();
    return;
}

void kSetScroll(Uint16 mode) {
    if (mode & MODE_BOTTOM) {
        kelir.yd = kelir.device->h;
    }
    else if (mode & MODE_TOP) {
        kelir.yd = 0;
    }
    else {
        kelir.yd = (kelir.device->h) / 2;
    }
    if (mode & MODE_LEFT) {
        kelir.xd = 0;
    }
    else if (mode & MODE_RIGHT) {
        kelir.xd = kelir.screen->w - kelir.device->w;
    }
    else {
        kelir.xd = (kelir.device->w)/2;
    }
    logPrintf("Device offset: %d,%d\n", kelir.xd, kelir.yd);
}


int kGetHeight() {
    return kelir.device->h;
}

int kGetWidth() {
    return kelir.device->w;
}

int kMinX() {
    return -kelir.xd;
}

int kMinY() {
    return -kelir.yd+1;
}

int kMaxX() {
    return kelir.device->w-kelir.xd-1;
}

int kMaxY() {
    return kelir.device->h-kelir.yd;
}

int kWorldMinX() {
    return -kelir.xs;
}

int kWorldMinY() {
    return -kelir.ys+1;
}

int kWorldMaxX() {
    return kelir.screen->w - kelir.xs-1;
}

int kWorldMaxY() {
    return kelir.screen->h - kelir.ys;
}

void kScrollX(int x) {
    kelir.xd = kelir.xd - x;
    int min = kGetWidth()-kWorldMaxX();
    if (kelir.xd < min) {
        kelir.xd = min;
    }
    else {
        int max = -kWorldMinX();
        if (kelir.xd > max) kelir.xd = max;
    }
    kAutoRefresh();
}

void kScrollY(int y) {
    kelir.yd = kelir.yd - y;
    if (kelir.yd < 0) {
        kelir.yd = 0;
    }
    else {
        int max = kelir.screen->h - kGetHeight();
        if (kelir.yd > max) kelir.yd = max;
    }
    kAutoRefresh();
}

void kScroll(int dx, int dy) {
    if (dx != 0) kScrollX(dx);
    if (dy != 0) kScrollY(dy);
}


int kGetScrollX() {
    return kelir.xd;
}

int kGetScrollY() {
    return kGetHeight() - kelir.yd;
}

void kSetRefresh(bool r) {
    kelir.autoRefresh = r;
}

// These are internal functions. DO NOT call them from application program
void wDraw(Wayang* w, Sint16 x, Sint16 y, SDL_Surface* s);
void uDraw(Ukoro* u, Sint16 x, Sint16 y, SDL_Surface* s);

void kBlit(Sint16 x, Sint16 y, SDL_Surface* img, SDL_Surface* dest) {
    SDL_Rect r2;
    r2.w = img->w;
    r2.h = img->h;
    r2.x = x;
    r2.y = y;
    logPrintf("Blit: %d,%d %d,%d\n", r2.x, r2.y, r2.w, r2.h);
    SDL_BlitSurface(img, NULL, dest, &r2);
}

static inline void kBlitC(Sint16 x, Sint16 y, SDL_Surface* img, SDL_Surface* dest) {
    kBlit(x-img->w/2, y-img->h/2, img, dest);
}

static inline void kBlitL(Sint16 x, Sint16 y, SDL_Surface* img,  SDL_Surface* dest) {
    kBlit(x, y-img->h/2,img, dest);
}

static inline void kBlitR(Sint16 x, Sint16 y, SDL_Surface* img, SDL_Surface* dest) {
    kBlit(x-img->w, y-img->h/2,img, dest);
}

/*
#define kDX(x) ((x) - kelir.xs + kelir.xd)
#define kDY(y) (kelir.yd - (y))
*/

void kRefresh() {
    hWayang w;
    hUkoro u;
    if (kelir.screen != NULL) {
        SDL_Rect rect = {kelir.xs-kelir.xd, kelir.ys-kelir.yd,
            kGetWidth(), kGetHeight()};
        logPrintf("kRefresh %d,%d %d,%d \n", rect.x, rect.y, rect.w, rect.h);
        SDL_BlitSurface(kelir.screen, &rect, kelir.device, NULL);
    }
    else {
        SDL_FillRect( kelir.device, &kelir.device->clip_rect, kelir.bcolor );
    }
    u = (Ukoro*)kelir.uList.first;
    while(u != NULL) {
        //logPrintf("U %p %p \n", u, u->cache);
        if (uIsVisible(u)) {
            logPrintf("uDraw %lf,%lf %lf,%lf  \n", u->x, u->y, kDX(u->x), kDY(u->y));
            uDraw(u, kDX(u->x), kDY(u->y), kelir.device);
        }
        u = (Ukoro*) u->item.next;
    }
    w = (Wayang*)kelir.wList.first;
    while(w != NULL) {
        if (wIsVisible(w)) {
            //logPrintf("wDraw %lf,%lf %lf,%lf \n",
            //    w->x, w->y, kDX(w->x), kDY(w->y));
            wDraw(w, kDX(w->x), kDY(w->y), kelir.device);
        }
        w = (Wayang*) w->item.next;
    }
    SDL_Flip(kelir.device);
}

void kAutoRefresh() {
    if (kelir.screen == kelir.device) return;
    if (!kelir.autoRefresh) return;
    kRefresh();
}


void kSetThickness(Uint16 t) {
    SPG_PopThickness();
    SPG_PushThickness(t);
}

void kSetOpaque(Uint8 a) {
    kelir.alpha = a;
}

Uint32 kGetColor() {
    Uint8 r, g, b;
    Uint32 color;
    SDL_GetRGB(kelir.fcolor, kelir.screen->format, &r, &g, &b);
    color = b;
    color = (color << 8) | g;
    color = (color << 8) | r;
    return color;
}

void kSetColor(Uint32 color) {
    Uint8 r, g, b;
    r = color & 0xFF;
    color >>=8;
    g = (color) & 0xFF;
    color >>=8;
    b = (color) & 0xFF;
    kelir.fcolor = SDL_MapRGB(kelir.screen->format, r,g,b);
}

void kSetRGB(Uint8 r, Uint8 g, Uint8 b) {
    kelir.fcolor = SDL_MapRGB(kelir.screen->format, r,g,b);
}

void kSetBackground(Uint32 color) {
    Uint8 r, g, b;
    r = color & 0xFF;
    color >>=8;
    g = (color) & 0xFF;
    color >>=8;
    b = (color) & 0xFF;
    kelir.bcolor = SDL_MapRGB(kelir.screen->format, r,g,b);
}

void kSetBackRGB(Uint8 r, Uint8 g, Uint8 b) {
    kelir.bcolor = SDL_MapRGB(kelir.screen->format, r,g,b);
}

// Draw a point at the current position
Uint32 kGetPixel(Sint16 x, Sint16 y) {
    Uint8 r, g, b;
    Uint32 color;
    color = SPG_GetPixel(kelir.screen, kX(x), kY(y));
    SDL_GetRGB(color, kelir.screen->format, &r, &g, &b);
    color = b;
    color = (color << 8) | g;
    color = (color << 8) | r;
    return color;
}

// Fast Replace a pixel with RGB value
// Without checking, you'll get segmentation fault if x or y
// is outside the range
void kSetPixelRGB(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b) {
    /*
    if ((x < kMinX()) || (x >= kMaxX()) return;
    if ((y < kMinY()) || (y >= kMaxY()) return;
    */
    Uint32 color = SDL_MapRGB(kelir.screen->format, r, g, b);
    x=kX(x); y=kY(y);
	switch (kelir.screen->format->BytesPerPixel) {
			case 4: { /* Probably 32-bpp */
				*((Uint32 *)kelir.screen->pixels + y*kelir.screen->pitch/4 + x) = color;
			}
			break;
			case 3: { /* Slow 24-bpp mode, usually not used */
				Uint8 *pix = (Uint8 *)kelir.screen->pixels + y * kelir.screen->pitch + x*3;

  				/* Gack - slow, but endian correct */
				*(pix+kelir.screen->format->Rshift/8) = color>>kelir.screen->format->Rshift;
  				*(pix+kelir.screen->format->Gshift/8) = color>>kelir.screen->format->Gshift;
  				*(pix+kelir.screen->format->Bshift/8) = color>>kelir.screen->format->Bshift;
				*(pix+kelir.screen->format->Ashift/8) = color>>kelir.screen->format->Ashift;
			}
			break;
			case 2: { /* Probably 15-bpp or 16-bpp */
				*((Uint16 *)kelir.screen->pixels + y*kelir.screen->pitch/2 + x) = color;
			}
			break;
			case 1: { /* Assuming 8-bpp */
				*((Uint8 *)kelir.screen->pixels + y*kelir.screen->pitch + x) = color;
			}
			break;
    }
}


// Draw a point at the (x,y) position
void kPixel(Sint16 x, Sint16 y) {
    SPG_PixelBlend(kelir.screen, kX(x), kY(y), kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a line from (x1,y1) to (x2, y2)
void kLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2 ) {
    SPG_LineBlend(kelir.screen, kX(x1), kY(y1), kX(x2), kY(y2), kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a square with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kSquare(Sint16 x, Sint16 y, Sint16 d) {
    SPG_RectBlend(kelir.screen, kX(x), kY(y), kX(x+d), kY(y+d),
        kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Fill a square with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kFillSquare(Sint16 x, Sint16 y, Sint16 d) {
    SPG_RectFilledBlend(kelir.screen, kX(x), kY(y), kX(x+d), kY(y+d),
        kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a rectangle with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kRectangle(Sint16 x, Sint16 y, Sint16 dx, Sint16 dy) {
    SPG_RectBlend(kelir.screen, kX(x), kY(y), kX(x+dx), kY(y+dy),
        kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a filled rectangle with top left corner at (x1, y1)
void kFillRectangle(Sint16 x, Sint16 y, Sint16 dx, Sint16 dy) {
    SPG_RectFilledBlend(kelir.screen, kX(x), kY(y), kX(x+dx), kY(y+dy),
        kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a circle with the center at current position, and radius r
void kCircle(Sint16 x, Sint16 y, Sint16 r) {
    SPG_CircleBlend(kelir.screen, kX(x), kY(y), r, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a filled circle with the centar at current position, and radius r
void kFillCircle(Sint16 x, Sint16 y, Sint16 r) {
    SPG_CircleFilledBlend(kelir.screen, kX(x), kY(y), r, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw an ellipse with the center at x,y and radius rx, ry
void kEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry) {
    SPG_EllipseBlend(kelir.screen, kX(x), kY(y), rx, ry, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a filled ellipse with the centar at x,y and radius r
void kFillEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry) {
    SPG_EllipseFilledBlend(kelir.screen, kX(x), kY(y), rx, ry, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw an arch with the center at x,y and radius r
void kArc(Sint16 x, Sint16 y, Sint16 r, float a1, float a2) {
    SPG_ArcBlend(kelir.screen, kX(x), kY(y), r, -a1, -a2, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}

// Draw a filled arch with the center at x,y and radius r
void kFillArc(Sint16 x, Sint16 y, Sint16 r, float a1, float a2) {
    SPG_ArcFilledBlend(kelir.screen, kX(x), kY(y), r, -a1, -a2, kelir.fcolor, kelir.alpha);
    kAutoRefresh();
}


//---------------------------------------------------------------------
// Wayang functions
hWayang wCreate(int nstate, ... ) {
    hWayang w;
    w = (Wayang*) malloc(sizeof(Wayang));
    if (w == NULL) {
        logPrintf("wCreate: not enough memory\n");
        return NULL;
    }
    if (nstate > 0) {
        va_list argptr;
        va_start( argptr, nstate );
        w->citra = cvLoad(nstate, argptr);
        va_end( argptr );
        if (w->citra == NULL) {
            free(w);
            return NULL;
        }
        cUse(w->citra);
    }
    else {
        w->citra = NULL;
    }
    w->cache = NULL;
    w->state=0;
    w->mode=MODE_CENTER | MODE_MID;
    w->trail=0;
    w->x=kMinX() - 100;
    w->y=kMinY() + 100;
    w->angle = 0;
    w->scaleX = w->scaleY = 1.0;
    SDL_GetRGB(kelir.fcolor, kelir.screen->format, &w->r, &w->g, &w->b);
    w->a= 255;
    iInit((Item*)w);
    lAddLast(&kelir.wList, (Item*) w);
    return w;
}

//---------------------------------------------------------------------
// Membuat wayang dengan gambar series
// Misalkan nama file kuda0001.png, kuda0002.png, ... , kuda0032.png
// maka panggil
// wCreate("kuda", 32);
hWayang wCreate(char* fname, int nstate) {
    hWayang w;
    int i;
    w = (Wayang*) malloc(sizeof(Wayang));
    if (w == NULL) {
        logPrintf("wCreate: not enough memory\n");
        return NULL;
    }
    w->citra = csLoad(nstate, fname);
    if (w->citra == NULL) {
       free(w);
       return NULL;
    }
    cUse(w->citra);

    w->cache = NULL;
    w->state=0;
    w->mode=MODE_CENTER | MODE_MID;
    w->trail=0;
    w->x=kMinX() - 100;
    w->y=kMinY() + 100;
    w->angle = 0;
    w->scaleX = w->scaleY = 1.0;
    SDL_GetRGB(kelir.fcolor, kelir.screen->format, &w->r, &w->g, &w->b);
    w->a= 255;
    iInit((Item*)w);
    lAddLast(&kelir.wList, (Item*) w);
    return w;
}


hWayang wClone(hWayang w1) {
    hWayang w;
    w = (Wayang*) malloc(sizeof(Wayang));
    if (w == NULL) {
        logPrintf("wClone: not enough memory\n");
        return NULL;
    }
    if (w1->citra != NULL) {
        w->citra = cUse(w1->citra);
    } else {
        w->citra = NULL;
    }
    w->cache = NULL;
    w->state=0;
    w->mode=w1->mode;
    w->trail=w1->trail;
    w->x=w1->x;
    w->y=w1->y;
    w->angle = w1->angle;
    w->scaleX = w1->scaleX;
    w->scaleY = w1->scaleY;
    w->r = w1->r;
    w->g = w1->g;
    w->b = w1->b;
    w->a = w1->a;
    iInit((Item*)w);
    lAddLast(&kelir.wList, (Item*) w);
    return w;
}

void wDelete(hWayang w) {
    wHide(w);
    lCut(&kelir.wList, (Item*)w);
    if (w->cache != NULL) {
        SDL_FreeSurface(w->cache);
    }
    if (w->citra) {
        cFree(w->citra);
    }
    free(w);
    logPrintf("Wayang deleted\n");
    kAutoRefresh();
}

Sint16 wGetH(hWayang w) {
    if (w->cache != NULL) {
        return w->cache->h;
    }
    if (w->citra == NULL)return 0;
    SDL_Surface *img = cImage(w->citra, w->state);
    if (img == NULL) return 0;
    return img->h;
}

Sint16 wGetW(hWayang w) {
    if (w->cache != NULL) {
        return w->cache->w;
    }
    if (w->citra == NULL)return 0;
    SDL_Surface *img = cImage(w->citra, w->state);
    if (img == NULL) return 0;
    return img->w;
}

void wUpdateCache(hWayang w) {
    if (w->citra == NULL) return;
    if (w->cache != NULL) {
        SDL_FreeSurface(w->cache);
        w->cache = NULL;
    }
    if (between (w->angle,-0.01, 0.01) ) {
        //logPrintf("Pass1 %f\n", (float)w->angle);
        if (between (w->scaleX,0.99,1.01) ) {
            //logPrintf("Pass2 %f\n", (float)w->scaleX);
            if (between (w->scaleY,0.99,1.01) ) {
                //logPrintf("Pass3 %f\n", (float)w->scaleY);
                return;
            }
        }
    }
    SDL_Surface *img = cImage(w->citra, w->state);
    if (img == NULL) return;
    w->cache = SPG_Transform(img, 0x00FFFFFF, -w->angle, w->scaleX, w->scaleY, SPG_NONE);
    //logPrintf("UpdateCache %f %f %f %p\n", (float)w->angle, (float)w->scaleX, (float)w->scaleY, w->cache);
}

void wDraw(hWayang w, Sint16 x, Sint16 y, SDL_Surface* s)
{
    if (w->cache != NULL) {
        kBlitC(x, y, w->cache, s);
    }
    else {
        SDL_Surface* img = cImage(w->citra, w->state);
        if (img == NULL) return;
        kBlitC(x, y, img, s);
    }
}

void wDrawTrail(hWayang w, Sint16 x2, Sint16 y2) {
    if (w->trail <= 0) return;
    Uint32 color = SDL_MapRGB(kelir.screen->format, w->r, w->g, w->b);
    SPG_PushThickness(w->trail);
    SPG_LineBlend(kelir.screen, kX(w->x), kY(w->y), kX(x2), kY(y2), color, w->a);
    SPG_PopThickness();
}

void wRefresh(hWayang w) {
    // refresh if wayang is visible
    if (wIsVisible(w) || (w->trail > 0))
        kAutoRefresh();
}

// Draw the image
void wStamp(hWayang w) {
    wDraw(w, kX(w->x), kY(w->y), kelir.screen);
    kAutoRefresh();
}

void wSetState(hWayang w, int state) {
    w->state = (state % cMax(w->citra));
    wUpdateCache(w);
    wRefresh(w);
}

void wNextState(hWayang w) {
    wSetState(w, w->state+1);
}

void wTop(hWayang w) {
    if (lMoveLast(&kelir.wList, (Item*)w) )
        wRefresh(w);
}

void wBottom(hWayang w) {
    if (lMoveFirst(&kelir.wList, (Item*)w) )
        wRefresh(w);
}

void wUp(hWayang w, int order) {
    if (lMoveNext(&kelir.wList, (Item*)w) )
        wRefresh(w);
}

void wDown(hWayang w) {
    if (lMovePrev(&kelir.wList, (Item*)w) )
        wRefresh(w);
}

// Looks
void wShow(hWayang w) {
    w->mode = w->mode | MODE_SHOW;
    if (w->cache == NULL) wUpdateCache(w);
    wRefresh(w);
}

void wHide(hWayang w) {
    w->mode = w->mode & ~MODE_SHOW;
    wRefresh(w);
}

void wHideAll() {
    hWayang w;
    w = (Wayang*) kelir.wList.first;
    while( w != NULL ) {
        w->mode = w->mode & ~MODE_SHOW;
        w = (Wayang*)w->item.next;
    }
    kAutoRefresh();
}

void wShowAll() {
    hWayang w;
    w = (Wayang*) kelir.wList.first;
    while( w != NULL ) {
        w->mode = w->mode | MODE_SHOW;
        w = (Wayang*)w->item.next;
    }
    kAutoRefresh();
}


void wSetTrail(hWayang w, Sint8 s) {
    w->trail = s;
}

void wChangeTrail(hWayang w, Sint8 ds) {
    wSetTrail(w, w->trail+ds);
}

void wSetTrailColor(hWayang w, Uint32 color) {
    wSetTrailRGB(w, color & 0xFF, (color>>8) & 0xFF, (color>>16) & 0xFF);
}

void wSetTrailRGB(Wayang* w, Uint8 r, Uint8 g, Uint8 b) {
    w->r = r;
    w->g = g;
    w->b = b;
}

void wChangeTrailColor(Wayang* w, Sint16 dr, Sint16 dg, Sint16 db) {
    wSetTrailRGB(w, w->r+dr, w->g+dg, w->b+db);
}

void wSetTrailOpaque(Wayang* w, Uint8 a) {
    w->a = a;
}

void wChangeTrailOpaque(Wayang* w, Uint8 da) {
    wSetTrailOpaque(w, w->r+da);
}

void wScaleTo(hWayang w, double z) {
    w->scaleX = (w->scaleX < 0) ? -z : z;
    w->scaleY = (w->scaleY < 0) ? -z : z;
    wUpdateCache(w);
    wRefresh(w);
}

void wScaleHTo(hWayang w, double z) {
    //w->scaleX = (w->scaleX < 0) ? -z : z;
    w->scaleY = (w->scaleY < 0) ? -z : z;
    wUpdateCache(w);
    wRefresh(w);
}

void wScaleWTo(hWayang w, double z) {
    w->scaleX = (w->scaleX < 0) ? -z : z;
    //w->scaleY = (w->scaleY < 0) ? -z : z;
    wUpdateCache(w);
    wRefresh(w);
}

void wScale(hWayang w, double dz) {
    w->scaleX *= dz;
    w->scaleY *= dz;
    wUpdateCache(w);
    wRefresh(w);
}

void wScaleH(hWayang w, double dz) {
    //w->scaleX *= dz;
    w->scaleY *= dz;
    wUpdateCache(w);
    wRefresh(w);
}

void wScaleW(hWayang w, double dz) {
    w->scaleX *= dz;
    //w->scaleY *= dz;
    wUpdateCache(w);
    wRefresh(w);
}

void wFlipX(hWayang w) {
    w->scaleX = -w->scaleX;
    wUpdateCache(w);
    wRefresh(w);
}

void wFlipY(hWayang w) {
    w->scaleY = -w->scaleY;
    wUpdateCache(w);
    wRefresh(w);
}

// Moving
void wTurnTo(hWayang w, double degree) {
    w->angle = degree;
    wUpdateCache(w);
    wRefresh(w);
}

void wTurn(hWayang w, double degree) {
    wTurnTo(w, w->angle+degree);
}

void wJumpTo(hWayang w, Sint16 x, Sint16 y) {
    w->x = x;
    w->y = y;
    wRefresh(w);
}

void wJumpForward(hWayang w, int distance) {
    double dx, dy;
    double rad = radian(w->angle);
    if (w->scaleX * w->scaleY < 0) {
        rad += M_PI;
    }
    dx = (cos(rad) * distance );
    dy = (sin(rad) * distance );
    w->x += dx;
    w->y += dy;
    //printf("Jump %lf %lf\n", dx, dy);
    wRefresh(w);
}

void wJump(hWayang w, Sint16 dx, Sint16 dy) {
    wJumpTo(w, w->x+dx, w->y+dy);
}

void wMoveTo(hWayang w, Sint16 x, Sint16 y) {
    wDrawTrail(w, x, y);
    w->x = x;
    w->y = y;
    wRefresh(w);
}

void wMoveForward(hWayang w, Sint16 distance) {
    double dx, dy;
    double rad = radian(w->angle);
    if (w->scaleX * w->scaleY < 0) {
        rad += M_PI;
    }
    dy = sin(rad) * distance;
    dx = cos(rad) * distance;
    wDrawTrail(w, w->x+dx, w->y+dy);
    w->x += dx;
    w->y += dy;
    wRefresh(w);
}

void wMove(hWayang w, Sint16 dx, Sint16 dy) {
    wMoveTo(w, w->x+dx, w->y+dy);
}

void wBlink(hWayang w, int repeat, Uint32 delay) {
    while (repeat--) {
        wNextState(w);
        SDL_Delay(delay);
    }
}

void wStepForward(hWayang w, Sint16 distance, double speed) {
    double dx, dy, x2, y2, x1, y1, fd, fs;
    Uint32 twait;
    double rad = radian(w->angle);
    if (w->scaleX * w->scaleY < 0) {
        rad += M_PI;
    }
    fs = (double) speed / 20.0;  // bagi 20 karena delay=50
    fd = (double) distance;
    dy = sin(rad) * fd;
    dx = cos(rad) * fd;
    x2 = w->x + dx;
    y2 = w->y + dy;
    dy = dy / (fd/fs);
    dx = dx / (fd/fs);
    x1 = w->x;
    y1 = w->y;
    while(fd > -fs) { //(fd > fs)
        twait = SDL_GetTicks() + 50;
        wMoveTo(w, x1, y1);
        fd -= fs;
        x1 += dx;
        y1 += dy;
        while (SDL_GetTicks() < twait);
    }
    w->x = x2;
    w->y = y2;
    wRefresh(w);
}

void wStepTo(hWayang w, Sint16 x, Sint16 y, double speed) {
    double dx, dy, x1, y1, fs, fd;
    Uint32 twait;
    dx = x-w->x;
    dy = y-w->y;
    fs = (double) speed / 20.0;
    fd = sqrt((dx*dx) + (dy*dy));
    dx = dx / (fd/fs);
    dy = dy / (fd/fs);
    x1 = w->x;
    y1 = w->y;
    while(fd > fs) {
        twait = SDL_GetTicks() + 50;
        wMoveTo(w, x1, y1);
        fd -= fs;
        x1 += dx;
        y1 += dy;
        while (SDL_GetTicks() < twait);
    }
    wMoveTo(w, x, y);
}

void wStep(hWayang w, Sint16 dx, Sint16 dy, double speed) {
    wStepTo(w, w->x + dx, w->y+dy, speed);
}

Uint32 wSay(hWayang w, hUkoro p, Uint32 wait, char* fmt, ...) {
    SDL_Color c1;
    SDL_Rect r1;
    int dx, dy;
    Uint32 key;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(print_buffer, PRINT_MAX, fmt, ap);
    va_end(ap);

    printf("%s\n", print_buffer);

    SDL_Surface *s1 = TTF_RenderText_Blended(p->aksara->font, print_buffer, p->color);
    if (s1 == NULL) return 0;

    dy=5;
    dy = wGetH(w) / 2;

    r1.w = s1->w;
    r1.h = s1->h;
    r1.x = kDX(w->x - (r1.w / 2));
    r1.y = kDY(w->y + r1.h + dy + 30);

    SPG_ArcFilledBlend(kelir.device, kDX(w->x), kDY(w->y+dy), 20, -80, -110, kelir.bcolor, 200);
    SPG_RectRoundFilledBlend(kelir.device, r1.x-10, r1.y-10, r1.x+r1.w+20, r1.y+r1.h+10, 5,
        kelir.bcolor, 200);
    SDL_BlitSurface(s1, NULL, kelir.device, &r1);
    SDL_Flip(kelir.device);
    SDL_FreeSurface(s1);
    key = dPause(wait);
    kRefresh();
    return key;
}


//------------------------------------------
hUkoro uCreate(char* filename, int size) {
    Ukoro* p;
    p = (Ukoro*) malloc(sizeof(Ukoro));
    if (p == NULL) {
        logPrintf("pCreate: not enough memory\n");
        return NULL;
    }
    p->aksara = aUse(aLoad(filename, size));
    if (p->aksara == NULL) {
        free(p);
        return NULL;
    }
    SDL_GetRGB(kelir.fcolor, kelir.screen->format,
        &p->color.r, &p->color.g, &p->color.b);
    p->str[0] = '\0';
    p->cache = NULL;
    p->a = 255;
    p->mode = MODE_CENTER | MODE_MID;
    p->x = 0;
    p->y = 0;
    p->angle = 0;
    iInit((Item*)p);
    lAddLast(&kelir.uList, (Item*) p);
    return p;
}

void uUpdateCache(hUkoro u) {
    if (u->str[0] == '\0') {
        //logPrintf("Ukoro is empty\n");
        return;
    }
    SDL_Surface *s1 = TTF_RenderText_Blended(u->aksara->font, u->str, u->color );
    if (u->cache != NULL) {
        SDL_FreeSurface(u->cache);
    }
    u->cache = s1;
    if (outside (u->angle,-0.01, 0.01) ) {
        s1 = SPG_Transform(u->cache, 0x00FFFFFF, -u->angle, 1, 1, SPG_NONE);
        if (s1 != NULL) {
            SDL_FreeSurface(u->cache);
            u->cache=s1;
            //logPrintf("Ukoro cached %f\n", (float)u->angle);
            return;
        }
    }
    //logPrintf("Ukoro cached %p %p\n",u, u->cache);
}

hUkoro uClone(hUkoro p1) {
    Ukoro* p;
    p = (Ukoro*) malloc(sizeof(Ukoro));
    if (p == NULL) {
        logPrintf("uClone: not enough memory\n");
        return NULL;
    }
    p->aksara = aUse(p1->aksara);
    p->color = p1->color;
    strcpy(p->str, p1->str);
    p->cache = NULL;
    p->a = p1->a;
    p->mode = p1->mode;
    p->x = p1->x;
    p->y = p1->y;
    p->angle = p1->angle;
    iInit((Item*)p);
    lAddLast(&kelir.uList, (Item*) p);
    uUpdateCache(p);
    return p;
}

void uDelete(hUkoro u) {
    uHide(u);
    lCut(&kelir.uList, (Item*)u);
    if (u->cache != NULL) {
        SDL_FreeSurface(u->cache);
    }
    aFree(u->aksara);
    free(u);
    logPrintf("Ukoro deleted\n");
}

void uDraw(hUkoro u, Sint16 x, Sint16 y, SDL_Surface* s) {
    if (u->cache == NULL) return;
    if (u->mode & MODE_BOTTOM) {
        y += u->cache->h/2;
    }
    else if (u->mode & MODE_TOP) {
        y -= u->cache->h/2;
    }
    if (u->mode & MODE_LEFT) {
        logPrintf("uDrawL: %d,%d\n", x, y);
        kBlitL(x, y, u->cache, s);
    }
    else if (u->mode & MODE_RIGHT) {
        logPrintf("uDrawR: %d,%d\n", x, y);
        kBlitR(x, y, u->cache, s);
    }
    else {
        logPrintf("uDrawC: %d,%d\n", x, y);
        kBlitC(x, y, u->cache, s);
    }
}

void uRefresh(hUkoro u) {
    if (!(u->mode & MODE_SHOW)) return;
    if (u->cache == NULL) return;
    kAutoRefresh();
}

void uStamp(hUkoro u) {
    uDraw(u, kX(u->x), kY(u->y), kelir.screen);
    kAutoRefresh();
}

void uJumpTo(hUkoro u, Sint16 x, Sint16 y)
{
    u->x = x;
    u->y = y;
    uRefresh(u);
}

void uTurnTo(hUkoro u, double angle) {
    if (angle != u->angle) {
        uUpdateCache(u);
        u->angle = angle;
        uRefresh(u);
    }
}

void uSetMode(hUkoro u, Uint8 mode) {
    u->mode = mode | mode;
    uRefresh(u);
}

void uUnsetMode(hUkoro u, Uint8 mode) {
    u->mode = mode & (~mode);
    uRefresh(u);
}

void uShow(hUkoro u) {
    if (u->mode & MODE_SHOW) return;
    uSetMode(u, MODE_SHOW);
    uRefresh(u);
}

void uHide(hUkoro u) {
    if (u->mode & MODE_SHOW) {
        uUnsetMode(u, MODE_SHOW);
        kAutoRefresh();
    }
}

void uSetOpaque(hUkoro u, Uint8 a) {
    u->a = a;
    uRefresh(u);
}

void uSetRGB(hUkoro u, Uint8 r, Uint8 g, Uint8 b) {
    u->color.r = r;
    u->color.g = g;
    u->color.b = b;
    uUpdateCache(u);
    uRefresh(u);
}

void uSetColor(hUkoro u, Uint32 color) {
    uSetRGB(u, color & 0xFF, (color>>8) & 0xFF, (color>>16) & 0xFF);
}

Uint32 uGetColor(Ukoro* p) {
    return p->color.r | (p->color.g << 8) | (p->color.b << 16);
}

void uSetText(hUkoro u, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(u->str, PRINT_MAX, fmt, ap);
    va_end(ap);
    uUpdateCache(u);
    uRefresh(u);
}


void uPrintC(hUkoro u, Sint16 x, Sint16 y, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(print_buffer, PRINT_MAX, fmt, ap);
    va_end(ap);
    SDL_Surface *s1 = TTF_RenderText_Blended(u->aksara->font, print_buffer, u->color );
    if (s1 == NULL) return;
    kBlitC(kX(x),kY(y),s1,kelir.screen);
    SDL_FreeSurface(s1);
    kAutoRefresh();
}

void uPrintL(hUkoro u, Sint16 x, Sint16 y, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(print_buffer, PRINT_MAX, fmt, ap);
    va_end(ap);
    SDL_Surface *s1 = TTF_RenderText_Blended(u->aksara->font, print_buffer, u->color );
    if (s1 == NULL) return;
    kBlitL(kX(x),kY(y),s1,kelir.screen);
    SDL_FreeSurface(s1);
    kAutoRefresh();
}

void uPrintR(hUkoro u, Sint16 x, Sint16 y, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(print_buffer, PRINT_MAX, fmt, ap);
    va_end(ap);
    SDL_Surface *s1 = TTF_RenderText_Blended(u->aksara->font, print_buffer, u->color );
    if (s1 == NULL) return;
    kBlitR(kX(x),kY(y),s1,kelir.screen);
    SDL_FreeSurface(s1);
    kAutoRefresh();
}


//------------------------------------------------------
// Gamelan

hGamelan gCreate(int channel, int max, ...) {
    Gamelan* s1;
    s1 = (Gamelan*) malloc(sizeof(Gamelan));
    if (s1 == NULL) {
        logPrintf("gCreate: not enough memory\n");
        return NULL;
    }
    va_list ap;
    va_start(ap, max);
    s1->gending = gvLoad(max, ap);
    va_end(ap);
    if (s1->gending == NULL) {
        free(s1);
        return NULL;
    }
    gUse(s1->gending);
    s1->channel = channel;
    return s1;
}

hGamelan gClone(hGamelan g, int channel) {
    Gamelan* s1;
    s1 = (Gamelan*) malloc(sizeof(Gamelan));
    if (s1 == NULL) {
        logPrintf("gClone: not enough memory\n");
        return NULL;
    }
    s1->gending = gUse(g->gending);
    s1->channel = channel;
    return s1;
}

void gDelete(hGamelan g) {
    lCut(&kelir.gList, (Item*) g);
    if (g->gending) {
        gFree(g->gending);
    }
    free(g);
}

void gPlay(hGamelan g, int index, int loop) {
    Mix_PlayChannel(g->channel, gSound(g->gending,index), loop);
}

void gStop(hGamelan g) {
    Mix_HaltChannel(g->channel);
}


//--------------------------------------------------------
// Dalang
Uint16 dWaitKey(Uint16 key) {
    SDL_Event event;
    logPrintf("Wait key ... \n");
    for(;;) {
        if (SDL_PollEvent( &event )) {
            if( event.type == SDL_KEYDOWN ) {
                if (key == 0) break;
                if (event.key.keysym.sym == key) break;
            }
        }
        else SDL_Delay(10);
    };
    return event.key.keysym.sym;
}

Uint16 dPause(Uint32 t) {
    SDL_Event event;
    if (t <= 0) return dWaitKey(0);
    logPrintf("Pausing ... ");
    while (t>10) {
        if (SDL_PollEvent( &event )) {
            if( event.type == SDL_KEYDOWN ) {
                logPrintf("CUT\n");
                return event.key.keysym.sym;
            }
        }
        else {
            SDL_Delay(10);
            t -=10;
        }
    };
    SDL_Delay(t);
    logPrintf("OK\n");
    return 0;
}

void dDelay(Uint32 t) {
    SDL_Delay(t);
}

void dSetPeriode(Uint32 t) {
    dalang.periode = t;
}

Uint32 dGetPeriode() {
    return dalang.periode;
}

Uint32 dGetTicks() {
    return SDL_GetTicks() - dalang.startTick;
}

Uint32 dGetCount() {
    return dGetTicks() / dalang.periode;
}

void dStart(Uint32 periode) {
    dalang.playing = true;
    dalang.periode = periode;
    dalang.startTick = SDL_GetTicks();
    dalang.nextTick = dalang.startTick;
    dalang.event.type = SDL_NOEVENT;
    kSetRefresh(false);
}

bool dNext() {
    if (!dalang.playing) return false;
    if (SDL_PollEvent (&dalang.event)) {
        if (dalang.event.type == SDL_QUIT) {
            dBreak();
            return false;
        }
    }
    else {
        dalang.event.type = SDL_NOEVENT;
    }
    return true;
}

void dFinish() {
    kSetRefresh(true);
}

void dBreak() {
    dalang.playing = false;
}

bool dIsTime() {
    if (SDL_GetTicks() > dalang.nextTick) {
        kRefresh();
        dalang.nextTick += dalang.periode;
        dalang.keys = SDL_GetKeyState(NULL);
        return true;
    }
    return false;
}

int dEventType() {
    return dalang.event.type;
}

bool dIsKey() {
    return (dalang.event.type == SDL_KEYDOWN);
}

Uint32 dGetKey() {
    return dalang.event.key.keysym.sym;
}

bool dIsButton() {
    return (dalang.event.type == SDL_MOUSEBUTTONDOWN);
}

bool dIsButtonDown() {
    return (dalang.event.type == SDL_MOUSEBUTTONDOWN);
}

bool dIsButtonUp() {
    return (dalang.event.type == SDL_MOUSEBUTTONUP);
}


int dGetButton() {
    return dalang.event.button.button;
}

int dGetButtonX() {
    return dalang.event.button.x-kelir.xs;
}

int dGetButtonY() {
    return kelir.ys-dalang.event.button.y;
}

bool dIsMouse() {
    return (dalang.event.type == SDL_MOUSEMOTION);
}

int dGetMouseX() {
    return dalang.event.motion.x-kelir.xs;
}

int dGetMouseY() {
    return kelir.ys-dalang.event.motion.y;
}


