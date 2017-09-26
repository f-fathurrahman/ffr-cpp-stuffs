#include <iostream>

using namespace std;

int main() {
  
  int i;

  // not using the "=" sign
  unsigned int age[4] {29, 27, 25, 22};
  cout << "age array:" << endl;
  for(i = 0; i < 4; i++) {
    cout << i << " " << age[i] << endl;
  }

  // use empty braces to set all elements to 0
  unsigned int cnt[5] = {};
  cout << "cnt array:" << endl;
  for(i = 0; i < 4; i++) {
    cout << i << " " << cnt[i] << endl;
  }

  char name[4] {'f', 'f', 'r', '\0'}; // will give compiler error when the storage is less than 4
  cout << name << endl;

  // list-initialization protects against narrowing
  // char slifs[4] {'h', 'i', 1122011, '\0'};
  char tlifs[4] {'h', 'i', 112, '\0'};
  cout << tlifs << endl;

  return 0;
}

