#include <cstdlib>
#include <cstdio>

#include <ctime>
// atau include <time.h>

#include <string>
#include <cfloat>
#include <climits>

#include <iostream>

#include "sprig/sprig.h"
#include "wayang/wayang.h"

using namespace std;

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

int randInt(int min, int range) {
  return min + (rand() % range);
}


int main()
{

  kOpen(800, 600, "images/wayang/keraton.jpg");

  cout << "randInt(300,200) = " << randInt(300, 200) << endl;

  kClose();

  return 0;
}

