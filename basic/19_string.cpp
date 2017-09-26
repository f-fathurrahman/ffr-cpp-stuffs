#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
  char fruit1[6] = {'a', 'p', 'p', 'l', 'e', '\0'};
  char fruit2[6] = {'m', 'a', 'n', 'g', 'g', 'o'};

  string str1 = "Fadjar Fathurrahman";

  cout << fruit1 << endl;
  printf("%s\n", fruit1);

  cout << fruit2 << endl;
  printf("%s\n", fruit2);

  cout << str1 << endl;
  printf("%s\n", str1.c_str());

  return 0;
}
