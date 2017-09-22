// from Prata

#include <iostream>

using namespace std;

int main()
{
  int yams[3];
  yams[0] = 7;
  yams[1] = 6;
  yams[2] = 5;

  int yamcosts[3] = {20, 30, 5};

  cout << "Total yams = ";
  cout << yams[0] + yams[1] + yams[2] << endl;

  cout << "The package with " << yams[1] << " yams costs ";
  cout << yamcosts[1] << " cents per yam.\n";

  int total = yams[0]*yamcosts[0] + yams[1]*yamcosts[1] + yams[2]*yamcosts[2];
  cout << "Total yam expense is " << total << " cents.\n";

  cout << "Size of the array   = " << sizeof(yams)    << " bytes\n";
  cout << "Size of one element = " << sizeof(yams[0]) << " bytes\n";

  return 0;
}
