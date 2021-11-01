#include <iostream>
using namespace std;

void hitung_kali_bagi(float& x, float& y, float& kali, float& bagi)
{
  kali = x*y;
  bagi = x/y;
  return;
}

int main()
{
  float x = 2;
  float y = 3;
  float kali, bagi;

  hitung_kali_bagi(x, y, kali, bagi);
  cout << "kali = " << kali << endl;
  cout << "bagi = " << bagi << endl;

  return 0;
}