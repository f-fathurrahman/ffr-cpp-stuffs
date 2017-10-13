#include <iostream>

using namespace std;

int main()
{
  cout.fill('*');

  // array of cstring
  const char *staff[2] = {"efefer", "ffr"};
  long bonus[2] = {800, 1200};

  int i;
  for( i = 0; i < 2; i++ ) {
    cout << staff[i] << ": $";
    cout.width(7);
    cout << bonus[i] << endl;
  }

  return 0;
}

