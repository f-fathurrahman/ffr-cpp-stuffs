#include <iostream>
#include <iomanip>

using namespace std;

//
void test1()
{
  cout.precision(16);
  cout << 10.0/3.1 << endl;

  cout.precision(6); // reset
  cout << 10.0/3.1 << endl;
}

//
void test2()
{
  cout << setprecision(16) << 10.0/3.1 << endl;

  // reset
  cout << setprecision(6) << 10.0/3.1 << endl;
}


int main()
{
  test1();
  test2();
  return 0;
}
