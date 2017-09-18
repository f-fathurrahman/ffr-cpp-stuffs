#include <iostream>

using namespace std;

void uninitialized_int()
{
  int a;  // uninitialized value
  int b = 45;

  // display these values
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
}

void uninitialized_double()
{
  double a;  // uninitialized value
  double b = 45.1;

  // display these values
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
}


int main()
{
  uninitialized_int();
  uninitialized_double();
  return 0;

}
