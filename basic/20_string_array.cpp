#include <iostream>
#include <cstring>  // for strlen()

using namespace std;

int main()
{
  const int SIZE = 40;

  char name1[SIZE];
  char name2[SIZE] = "efefer";

  cout << "Hello, I am " << name2 << endl;
  cout << "What is your name?" << endl;
  
  //cin >> name1;
  string tmp1;
  getline(cin, tmp1);
  
  cout << "tmp1 = " << tmp1 << endl;

  copy(tmp1.begin(), tmp1.end(), name1);
  name1[tmp1.size()] = '\0';

  //cout << "Your name is " << tmp1 << endl;
  cout << "Your name is " << name1 << endl;
  cout << "Your name has " << strlen(name1) << " ";
  cout << "characters and is stored in " << sizeof(name1) << " ";
  cout << "bytes." << endl;

  return 0;
}
