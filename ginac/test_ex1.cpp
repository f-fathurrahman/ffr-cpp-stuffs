#include <iostream>
#include <ginac/ginac.h>
using namespace std;
using namespace GiNaC;

int main()
{
  symbol x("x");
  symbol y("y");
  symbol z("z");

  ex MyEx1 = 5*x + 2*pow(x,2) + 3.1*x + 3*y;
  ex MyEx2 = MyEx1/(5*z);

  cout << latex;
  cout << MyEx1 << endl;
  cout << MyEx2 << endl;

  return 0;
}
