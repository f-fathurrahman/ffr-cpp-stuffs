#include <iostream>

using namespace std;

int main()
{
  const int N = 20;
  char name[N];
  char dessert[N];

  cout << "Enter your name:\n";
  cin.getline(name, N);

  cout << "Enter your favorite dessert:\n";
  cin.getline(dessert, N);

  cout << "Hello " << name << endl;
  cout << "Your favorite dessert is " << dessert << endl;

  return 0;
}

