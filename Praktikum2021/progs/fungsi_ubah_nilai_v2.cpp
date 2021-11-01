#include <iostream>
using namespace std;

void tambah_satu(int &i)
{
  i = i + 1;
  cout << "Nilai variabel DI DALAM fungsi tambah_satu: " << i << endl;
  return;
}

int main()
{
  int a = 10;
  cout << "Nilai variabel SEBELUM fungsi tambah_satu dipanggil: " << a << endl;
  tambah_satu(a);
  cout << "Nilai variabel SETELAH fungsi tambah_satu dipanggil: " << a << endl;

  return 0;
}