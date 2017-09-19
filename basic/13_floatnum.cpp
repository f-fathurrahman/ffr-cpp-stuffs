#include <iostream>

using namespace std;

int main()
{
  cout.setf( ios_base::fixed, ios_base::floatfield );

  float a = 11.0 / 3.0;
  double b = 11.0 / 3.0;
  long double c = 11.0 / 3.0;

  cout << a*3.0 << endl;
  cout << b*3.0 << endl;
  cout << c*3.0 << endl;

  return 0;
}

