# Subprogram

Subprogram adalah bagian program yang terpisah dari program utama.
Subprogram biasanya memiliki tugas atau kegunaan tertentu.
Dalam bahasa pemrograman C++, kita dapat membagi subprogram menjadi
dua yaitu:

- fungsi: subprogram yang mengembalikan nilai
- prosedur/subrutin: subprogram yang tidak mengembalikan
  nilai

Dalam beberapa literatur keduanya dapat dianggap sama, namun ada
baiknya kita melakukan pembagian subprogram menjadi dua seperti
di atas.

Sintaks dari fungsi dan subrutin adalah sebagai berikut:
```c++
tipe_keluaran nama_subprogram(tipe1 arg1, tipe2 arg2, ...)
{
  // bada subprogram
}
```

Suatu subprogram dapat memiliki nol, satu atau lebih argumen atau input.
Untuk subrutin, `tipe_keluaran` adalah `void`.
Untuk funsi, `tipe_keluaran` dapat adalah tipe data dari keluaran, misalnya
`int`, `float`, atau tipe data lain (bisa juga berupa tipe data turunan).

## Contoh: menghitung pangkat 3 dari bilangan `float`

Perhatikan program berikut ini.

```c++
#include <iostream>
using namespace std;

int main()
{
  float x = 2.1;
  cout << "Bilangan " << x << " pangkat tiga adalah " << x*x*x << endl;

  float y = 3.7;
  cout << "Bilangan " << y << " pangkat tiga adalah " << y*y*y << endl;

  return 0;
}
```

Misalnya kita ingin membuat sebuah fungsi yang dapat menghitung nilai
pangkat tiga dari suatu bilangan. Untuk keperluan ini kita dapat
membuat spesifikasi sebagai berikut:

- Nama fungsi adalah `pangkat3` (misalnya)
- Input atau *argumen* dari fungsi adalah bilangan dengan tipe `float`, misalkan
dengan nama `x`.
- Output dari fungsi adalah nilai `x` yang sudah dipangkatkan
dengan tiga.

Kita dapat mendeklarasikan fungsi tersebut sebagai berikut:
```c++
float hitung_pangkat3(float x)
{
  return x*x*x;
}
```

Program dapat ditulis menjadi:
```c++
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
```

Perhatikan bahwa nama variabel `x` pada fungsi `hitung_pangkat3` juga dapat
diganti dengan nama variabel lain. Misalnya:
```c++
float hitung_pangkat3(float a)
{
  return a*a*a;
}
```
Variabel `a` di sini hanya merupakan nama argumen dari fungsi saja dan
hanya terdefinisi pada fungsi yang bersangkutan. Ketika kita memanggil
fungsi `hitung_pangkat3` sebagai berikut (misalnya):
```c++
float b = 3.1
cout << "b pangkat 3 adalah " << hitung_pangkat3(b);
```
maka nilai argumen `x` pada definisi fungsi `hitung_pangkat3` akan digantikan
dengan nilai dari variabel `b` yaitu `3.1`.

Fungsi `hitung_pangkat3` mengembalikan sebuah nilai, karena itu kita juga
dapat memberikan nilainya ke suatu variabel. Contoh:
```c++
// ... sama dengan sebelumnya
int main()
{
  float hasil;

  float x = 2.1;
  hasil = hitung_pangkat3(x);
  cout << "Bilangan " << x << " pangkat tiga adalah " << hasil << endl;

  float y = 3.7;
  hasil = hitung_pangkat3(y);
  cout << "Bilangan " << x << " pangkat tiga adalah " << hasil << endl;

  return 0;
}
```


## Contoh subrutin

Perhatikan program berikut ini.

```c++
#include <iostream>
using namespace std;
int main()
{
  
  string nama1 = "Jojo";
  cout << "Halo " << nama1 << "!" << endl;
  cout << "Senang berkenalan dengan Anda!" << endl;

  string nama2 = "Dudun";
  cout << "Halo " << nama2 << "!" << endl;
  cout << "Senang berkenalan dengan Anda!" << endl;
  
  return 0;
}
```

Jika kita perhatikan program di atas, ada beberapa baris yang dapat
melakukan tugas yang sama, yaitu:

- menampilkan pesan "Halo" dan diikuti dengan suatu nama
- kemudian menampilkan pesang "Senang berkenalan dengan Anda!"

Kita dapat "membungkus" tugas tersebut dalam suatu subrutin (fungsi
yang tidak memberikan nilai keluaran). Subrutin tidak mengembalikan suatu
nilai, pada contoh di atas program hanyak menampilkan sesuatu ke
layar. Spefisikasi subrutin:

- Input atau argumen adalah `nama` dengan tipe string
- Keluaran tidak ada. Subrutin hanya menampilkan suatu teks ke layar.

Subrutin:
```c++
void print_nama(string nama)
{
  cout << "Halo " << nama << "!" << endl;
  cout << "Senang berkenalan dengan Anda!" << endl;
  return; // opsional, dapat dihilangkan atau tidak ditulis
}
```


Program menjadi sebagai berikut.
```c++
#include <iostream>
using namespace std;

void print_nama(string nama)
{
  cout << "Halo " << nama << "!" << endl;
  cout << "Senang berkenalan dengan Anda!" << endl;
  return;
}

int main()
{
  string nama1 = "Jojo";
  print_nama(nama1);

  string nama2 = "Dudun";
  print_nama(nama2);
  
  return 0;
}
```

## Program pangkat 3 menggunakan subrutin

Anda dapat menggunakan fungsi ataupun subrutin sesuai dengan
keperluan maupun preferensi Anda.
Misalkan, kita juga dapat mengimplementasikan program pangkat 3
sebelumnya dengan menggunakan subrutin (fungsi dengan tipe kembalian
void):
```c++
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
```


## Pass-by-value dan Pass-by-reference

Secara default, input pada suatu fungsi menggunakan
pass-by-value, artinya hanya nilai dari variabel saja
yang dimasukkan ke dalam fungsi. Jika terjadi perubahan
pada variabel yang diberikan maka perubahan tersebut hanya
dalam fungsi atau subrutin saja.

Perhatikan program berikut. Tebaklah apa keluarannya
dan coba juga pada komputer.
```c++
#include <iostream>
using namespace std;

void tambah_satu(int i)
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
```

Untuk mengubah nilai pada suatu fungsi, kita perlu
mengunakan pass-by-reference. Hal ini dapat dilakukan dengan
menambahkan tanda `&` pada nama variabel atau tipe data
pada dideklarasi fungsi.

Mari kita coba dengan mengubah deklarasi fungsi `tambah_satu`
menjadi sebagai berikut.
```c++
void tambah_satu(int& i)
{
  i = i + 1;
  cout << "Nilai variabel DI DALAM fungsi tambah_satu: " << i << endl;
  return;
}
```

Bandingkan hasilnya dengan program sebelumnya.

# Beberapa penggunaan pass-by-reference

Teknik *pass-by-reference* ini dapat digunakan jika Anda ingin
mensimulasikan fungsi yang mengembalikan lebih dari dua nilai
dengan menggunakan subrutin. Misalkan kita ingin
membuat suatu fungsi yang menghitung hasil kali
dan bagi dari suatu bilangan.
```c++
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
```




Anda juga dapat menggunakan *pass-by-reference* ini
untuk mengambil beberapa input dari pengguna. Contoh:
```c++
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
```


# Tugas

Tinjau kembali program untuk menghitung akar-akar persamaan
kuadrat. Modifikasi program ini sehingga dapat menggunakan
fungsi dan/atau subrutin.
