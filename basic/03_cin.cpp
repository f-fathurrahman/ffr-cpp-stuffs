#include <iostream>
#include <string>

using namespace std;

void cin_double()
{
  double a, b;

  cout << "Enter a value: " << endl;
  cin >> a;
  cin >> b;

  cout << "Read values: " << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
}

void cin_string()
{
  cout << "\n\ncin_string begin ...\n";
  string str1, str2;

  cin >> str1;
  cin >> str2;

  cout << "str1 = " << str1 << endl;
  cout << "str2 = " << str2 << endl;
}

int main()
{
  cin_string();
  return 0;
}

