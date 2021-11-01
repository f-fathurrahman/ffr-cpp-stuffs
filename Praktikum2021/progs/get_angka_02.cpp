#include <iostream>

using namespace std;

float get_angka()
{
  float angka;
  cout << "Masukkan bilangan real: ";
  cin >> angka;
  return angka;
}

int main() {
  float angka;
  angka = get_angka(); // inisialisasi
  while(true)
  {
    if(angka < 0) {
      cout << "Anda memasukkan angka negatif" << endl;
      break;
    }
    cout << "Anda memasukkan angka: " << angka << endl;
    angka = get_angka();
  }
  return 0;
}
