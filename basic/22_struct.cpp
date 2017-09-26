#include <iostream>

using namespace std;

const int N_NAMA = 30;
const int N_ALAMAT = 100;

struct Warga
{
  char nama[N_NAMA];
  char alamat[N_ALAMAT];
};

int main()
{
  Warga w1 = {
    "Fadjar Fathurrahman",
    "Jalan Ganesha 10, Bandung"
  };

  cout << "Nama warga: " << w1.nama << endl;
  cout << "Alamat warga: " << w1.alamat << endl;

  return 0;
}
