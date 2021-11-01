#include <iostream>
using namespace std;

void input_dua_angka(float& x, float &y)
{
  cout << "Masukkan angka pertama: ";
  cin >> x;
  cout << "Masukkan angka kedua: ";
  cin >> y;
  return;
}

int main()
{
  float x, y;
  input_dua_angka(x, y);
  cout << "Angka pertama: " << x << endl;
  cout << "Angka kedua  : " << y << endl;
  return 0;
}