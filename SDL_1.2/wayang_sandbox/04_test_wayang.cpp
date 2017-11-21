#include <cstdlib>
#include <cstdio>

#include <ctime>
// atau include <time.h>

#include <string>
#include <cfloat>
#include <climits>

#include "sprig/sprig.h"
#include "wayang/wayang.h"

void gb2D()
{
  hWayang benda_langit;
  benda_langit = wCreate (3, "images/alam/bulan_01.png",
                             "images/alam/hujan.png",
                             "images/alam/matahari_01.png");
  wJumpTo(benda_langit,-100,200);
  wShow(benda_langit);
  dPause(10000);
  wNextState(benda_langit);
  dPause(10000);
  wNextState(benda_langit);
}

void animasi()
{
  hWayang ball = wCreate("images/animasi/ball",6);
  wJumpTo(ball, 0,0);
  wShow(ball);
  wBlink(ball,100,100);
}


int randInt(int min, int range) {
  return min + (rand() % range);
}

void drawbintang(hWayang w, int x, int y, int s){
  wJumpTo(w,x,y);
  for(int i=1;i<=5;i++){
    wMoveForward(w,s);
    wTurn(w,-144);
  }
}

void drawRandBintang()
{
  hWayang pencil=wCreate(1,"images/aktor/pencil.png");
  srand( time(NULL) );
  wJumpTo(pencil,0,0);
  wShow(pencil);
  wSetTrail(pencil,2);
  wSetTrailColor(pencil,YELLOW);
  for(int i = 0; i<10;i++) {
    drawbintang(pencil,randInt(-200,600), randInt(0,250), randInt(20,50));
  }
}


void drawsegi_n(int x, int y, int n, int sisi){
  hWayang w = wCreate(1,"images/aktor/pencil.png");
  wShow(w);
  wSetTrail(w,2);
  wSetTrailColor(w,GREEN);
  wJumpTo(w,x,y);
  float sudut = 360./n;
  for(int j=0;j<n;j++){
    wStepForward(w,sisi,50);
    wTurn(w,sudut);
  }
}


int main()
{

  kOpen(800, 600, "images/wayang/keraton.jpg");

  gb2D();

  animasi();  

  drawRandBintang();

  drawsegi_n(0, -200, 5, 100);

/*
  hWayang benda_langit;
  benda_langit = wCreate (3, "images/alam/bulan_01.png",
                             "images/alam/hujan.png",
                             "images/alam/matahari_01.png");

	wJumpTo(benda_langit, 0, 0); 
  wShow(benda_langit); 

  wShow(benda_langit);
  dPause(10000);
  wNextState(benda_langit);
  dPause(10000);
  wNextState(benda_langit);

	dDelay(1000);

	wJumpTo(benda_langit, 0, 100); 
  wNextState(benda_langit);
	dDelay(1000);

	wJumpTo(benda_langit, 100, 100); 
  wNextState(benda_langit);

  wBlink(benda_langit, 4); 
*/



	dPause(10000);

  kClose();

  return 0;
}

