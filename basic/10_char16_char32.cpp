#include <iostream>

using namespace std;

int main()
{
  char16_t ch1 = u'q';
  char32_t ch2 = U'\U0000222B';

  cout << ch1 << endl;
  cout << ch2 << endl;

  return 0;
}

