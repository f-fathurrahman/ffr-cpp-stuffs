#include <iostream>

using namespace std;

int main() {
  float angka;

  cout << "Masukkan bilangan real: ";
  cin >> angka;

  while(true)
  {
    if(angka < 0) {
      cout << "Anda memasukkan angka negatif" << endl;
      break;
    }
    cout << "Anda memasukkan angka: " << angka << endl;

    cout << "Masukkan bilangan real: ";
    cin >> angka;

  }
  return 0;
}
