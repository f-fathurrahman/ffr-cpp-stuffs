#include <iostream>

using namespace std;

void print_pangkat3(float x)
{
  cout << "Bilangan " << x << " pangkat tiga adalah " << x*x*x << endl;
  return;
}

int main()
{
  print_pangkat3(2.1);
  print_pangkat3(3.7);
  return 0;
}