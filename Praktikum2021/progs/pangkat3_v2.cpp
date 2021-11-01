#include <iostream>

using namespace std;

float hitung_pangkat3(float x)
{
  return x*x*x;
}

int main()
{
  float x = 2.1;
  cout << "Bilangan " << x << " pangkat tiga adalah " << hitung_pangkat3(x) << endl;

  float y = 3.7;
  cout << "Bilangan " << y << " pangkat tiga adalah " << hitung_pangkat3(y) << endl;

  return 0;
}