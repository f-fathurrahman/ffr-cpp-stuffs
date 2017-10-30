/*
 * Wayang.h
 *
 * (c) Eko Mursito Budi, 2010
 */

 /*********************************************************************
 *  This library is free software; you can redistribute it and/or    *
 *  modify it under the terms of the GNU Library General Public      *
 *  License as published by the Free Software Foundation; either     *
 *  version 2 of the License, or (at your option) any later version. *
 *********************************************************************/

#ifndef _WAYANG_H_INCLUDED
#define _WAYANG_H_INCLUDED

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
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#ifndef _SPRIG_H__
#include "../sprig/sprig.h"
#endif
#include "list.h"

/*
#ifndef bool
#define bool int
#define true 1
#define false 0
#endif
*/

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

#define TRANSPARANT 0
#define OPAQUE 255

#define BLACK   0x000000
#define GRAY    0x7F7F7F
#define WHITE   0xFFFFFF
#define RED     0x0000FF
#define GREEN   0x00FF00
#define BLUE    0xFF0000
#define YELLOW  0x00FFFF
#define CYAN    0xFFFF00
#define VIOLET  0xFF00FF

#define MODE_SHOW   0x01
#define MODE_HIDE   0x00
#define MODE_FIXED  0x02
#define MODE_LEFT   0x04
#define MODE_RIGHT  0x08
#define MODE_CENTER 0x00
#define MODE_TOP    0x40
#define MODE_BOTTOM 0x80
#define MODE_MID    0x00

#define PRINT_MAX 255

// Shared Resources
// Loading & freeing resources
typedef struct {
    int count, max;
    SDL_Surface* images[1];
} Citra;

typedef struct {
    int count, size;
    TTF_Font* font;
} Aksara;

typedef struct {
    int count, max;
    Mix_Chunk* chunks[1];
} Gending;

extern char* image_path;
extern char* font_path;
extern char* sound_path;
extern bool enable_log;
void logPrintf(char *fmt, ...);

Citra* cLoad(char *filename);
void cFree(Citra *g);
Citra* cUse(Citra *g);
static inline SDL_Surface* cImage(Citra* g, int i)
    {return g->images[i];}
static inline int cMax(Citra* g)
    {return g->max;}

Aksara* aLoad(char *filename, int size);
void aFree(Aksara* i);
Aksara* fUse(Aksara *i);

Gending* gLoad(char *filename);
void gFree(Gending *i);
Gending* gUse(Gending *i);
static inline Mix_Chunk* gSound(Gending* t, int i)
    {return t->chunks[i];}
static inline int gMax(Gending* t)
    {return t->max;}

// Second Layer
// Devices
typedef struct Kelir {
    SDL_Surface* screen;
    SDL_Surface* device;
    //SDL_Surface* image;
    bool autoRefresh;
    Sint16 xs, ys;
    Sint16 xd, yd;
    Uint32 fcolor;
    Uint32 bcolor;
    Uint8 alpha;
    Sint16 thickness;
    List wList;
    List uList;
    List gList;
} Kelir;

extern Kelir kelir;

int kOpen(int width, int height, char *filename, Uint16 mode=MODE_CENTER|MODE_MID);
void kClose();
int kGetHeight();
int kGetWidth();
int kMinX();
int kMinY();
int kMaxX();
int kMaxY();

int kWorldMinX();
int kWorldMinY();
int kWorldMaxX();
int kWorldMaxY();
int kWorldX();
int kWorldY();

void kScrollTo(int x, int y);
void kScrollX(int dx);
void kScrollY(int dy);
void kSetScroll(Uint16 mode);

void kSetCaption(const char* caption);
void kSetImage(char *fname, Uint16 mode=MODE_CENTER|MODE_MID);
void kSetThickness(Uint16 t);
void kSetOpaque(Uint8 a);
void kSetColor(Uint32 color);
void kSetRGB(Uint8 r, Uint8 g, Uint8 b);
void kSetBackground(Uint32 color);
void kSetBackRGB(Uint8 r, Uint8 g, Uint8 b);

void kSetRefresh(bool r);
void kRefresh();
void kAutoRefresh();

// Get the color value of a pixel at x,y
Uint32 kGetPixel(Sint16 x, Sint16 y);
void kSetPixelRGB(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b);
void kSetPixelRGBA(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Draw a point at the (x,y) position
void kPixel(Sint16 x, Sint16 y);

// Draw a line from (x1,y1) to (x2, y2)
void kLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2 );

// Draw a square with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kSquare(Sint16 x, Sint16 y, Sint16 d);

// Fill a square with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kFillSquare(Sint16 x, Sint16 y, Sint16 d);

// Draw a rectangle with top left corner at (x1, y1) and bottom right corner at (x2, y2)
void kRectangle(Sint16 x, Sint16 y, Sint16 dx, Sint16 dy);

// Draw a filled rectangle with top left corner at (x1, y1)
void kFillRectangle(Sint16 x, Sint16 y, Sint16 dx, Sint16 dy);

// Draw a circle with the center at current position, and radius r
void kCircle(Sint16 x, Sint16 y, Sint16 r);

// Draw a filled circle with the centar at current position, and radius r
void kFillCircle(Sint16 x, Sint16 y, Sint16 r);

// Draw an ellipse with the center at x,y and radius rx, ry
void kEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry);

// Draw a filled ellipse with the centar at x,y and radius r
void kFillEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry);

// Draw an arc with the center at x,y and radius r
void kArc(Sint16 x, Sint16 y, Sint16 r, float a1, float a2);

// Draw a filled arc with the center at x,y and radius r
void kFillArc(Sint16 x, Sint16 y, Sint16 r, float a1, float a2);

// Third Layer
// The Players
typedef struct {
    Item item;
    Aksara* aksara;
    char str[PRINT_MAX];
    SDL_Surface* cache;
    Uint8 a;
    Uint8 mode;
    double x, y;
    double angle;
    SDL_Color color;
} Ukoro;

typedef struct Wayang {
    Item item;
    Citra* citra;
    SDL_Surface* cache;
    int state;
    Uint8 mode;
    double x, y;
    double angle;
    double scaleX, scaleY;
    Sint16 trail;
    Uint8 r,g,b,a;
} Wayang;

// define pointer as handle for newbie friendliness :)
typedef Ukoro* hUkoro;
typedef Wayang* hWayang;

#define radian(a) (a / 180.0 * M_PI)
#define degree(r) (r * M_PI / 180.0)

// Wayang functions
hWayang wCreate(int nstate, ... );
hWayang wCreate(char* fname, int nstate);
hWayang wClone(hWayang w);
void wDelete(hWayang w);
void wRefresh(hWayang w);
void wTop(hWayang w);
void wBottom(hWayang w);
void wUp(hWayang w, int order);
void wDown(hWayang w, int order);
// Looks
void wShow(hWayang w);
void wHide(hWayang w);
void wHideAll();
void wShowAll();

void wSetState(hWayang, int state);
void wNextState(hWayang);
void wBlink(hWayang, int repeat, Uint32 delay=500);

// Draw the Citra
void wStamp(hWayang w);
void wSetTrail(hWayang w, Sint8 s);
void wChangeTrail(hWayang w, Sint8 ds);
void wSetTrailColor(Wayang* w, Uint32 color);
void wSetTrailRGB(Wayang* w, Uint8 r, Uint8 g, Uint8 b);
void wChangeTrailRGB(Wayang* w, Sint16 dr, Sint16 dg, Sint16 db);
void wSetTrailOpaque(Wayang* w, Uint8 a);
void wChangeTrailOpaque(Wayang* w, Uint8 da);
void wScaleTo(hWayang w, double z);
void wScaleHTo(hWayang w, double z);
void wScaleWTo(hWayang w, double z);
void wScale(hWayang w, double dz);
void wScaleH(hWayang w, double dz);
void wScaleW(hWayang w, double dz);
void wFlipX(hWayang w);
void wFlipY(hWayang w);

// Moving
void wTurnTo(hWayang w, double degree);
void wTurn(hWayang w, double degree);
void wJumpTo(hWayang w, Sint16 x, Sint16 y);
void wJumpForward(hWayang w, int distance);
void wJump(hWayang w, Sint16 dx, Sint16 dy);
void wMoveTo(hWayang w, Sint16 x, Sint16 y);
void wMoveForward(hWayang w, Sint16 distance);
void wMove(hWayang w, Sint16 dx, Sint16 dy);
void wStepTo(hWayang w, Sint16 x, Sint16 y, double speed);
void wStepForward(hWayang w, Sint16 distance, double speed);
void wStep(hWayang w, Sint16 dx, Sint16 dy, double speed);

Uint32 wSay(hWayang w, hUkoro p, Uint32 pause, char* fmt, ...);

static inline bool wIsHidden(hWayang w) {return !(w->mode & MODE_SHOW);}
static inline bool wIsVisible(hWayang w) {return w->mode & MODE_SHOW;}

static inline Sint16 wGetX(hWayang w) { return w->x; }
static inline Sint16 wGetY(hWayang w) { return w->y; }
static inline Sint16 wGetAngle(hWayang w) { return w->angle; }
static inline Sint16 wGetState(hWayang w) { return w->state; }
static inline Sint16 wGetStateNum(hWayang w) { return w->citra->max; }
Sint16 wGetH(hWayang w);
Sint16 wGetW(hWayang w);

// Ukoro
hUkoro uCreate(char* filename, int size);
hUkoro uClone(hUkoro u);
void uDelete(hUkoro u);
void uJumpTo(hUkoro u, Sint16 x, Sint16 y);
//void uTurnTo(hUkoro u, double angle);
void uSetMode(hUkoro u, Uint8 mode);
void uUnsetMode(hUkoro u, Uint8 mode);
void uShow(hUkoro p);
void uHide(hUkoro p);
void uSetOpaque(hUkoro u, Uint8 a);
void uSetRGB(hUkoro u, Uint8 r, Uint8 g, Uint8 b);
void uSetColor(hUkoro p, Uint32 c);
void uSetText(hUkoro p, char *txt, ...);

void uPrintL(hUkoro p, Sint16 x, Sint16 y, const char *str, ...);
void uPrintR(hUkoro p, Sint16 x, Sint16 y, const char *str, ...);
void uPrintC(hUkoro p, Sint16 x, Sint16 y, const char *str, ...);

void uRefresh(hUkoro u);

static inline bool uIsVisible(hUkoro u) {return u->mode & MODE_SHOW;}
static inline Sint16 uGetX(hUkoro u) { return u->x; }
static inline Sint16 uGetY(hUkoro u) { return u->y; }

// Gamelan
typedef struct Gamelan {
    Item item;
    Gending* gending;
    int state;
    int channel;
} Gamelan;
typedef Gamelan* hGamelan;

hGamelan gCreate(int channel, int max, ...);
hGamelan gClone(int channel);
void gDelete(hGamelan g);
void gPlay(hGamelan g, int index, int loop);
void gStop(hGamelan g);

// Layer 4
// The one and only one controller
// Fourth Layer
// Controller
typedef struct Dalang {
    bool playing;
    Uint32 periode;
    Uint32 startTick;
    Uint32 nextTick;
    SDL_Event event;
    Uint8 *keys;
} Dalang;

// Global variables
extern Dalang dalang;

Uint32 dGetTicks();
Uint16 dWaitKey(Uint16 key);
Uint16 dPause(Uint32 mseconds);
void dDelay(Uint32 mseconds);

void dSetPeriode(Uint32 t);
void dStart(Uint32 periode);
bool dNext();
void dFinish();
void dBreak();

bool dIsTime();
#define dIsPressed(key) (dalang.keys[key])

int dEventType();

bool dIsKey();
Uint32 dGetKey();

bool dIsButton();
bool dIsButtonDown();
bool dIsButtonUp();
int dGetButton();
int dGetButtonX();
int dGetButtonY();

bool dIsMouse();
int dGetMouseX();
int dGetMouseY();

#endif
