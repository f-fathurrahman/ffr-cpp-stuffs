#include <iostream>

using namespace std;

void test1()
{
  const int N = 10;
  
  double arr1[N];
  arr1[0] = 0.0;
  
  // check whether all other values are zeros
  // FIXME: Other ways to do this ?
  int i;
  for(i = 0; i < N; i++) {
    cout << "arr1[" << i << "] = " << arr1[i] << endl;
  }
}


void test2()
{
  const int N = 10;

  // initialize all elements to zero
  double r[N] = {0.0};
  
  // initialize the first two element to 1.2 and 1.0, all others are zero
  double p[N] = {1.2, 1.0};

  int i;
  for(i = 0; i < N; i++) {
    cout << r[i] << " " << p[i] << endl;
  }
}


int main()
{
  //test1();
  test2();
  return 0;
}

