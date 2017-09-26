#include <iostream>

using namespace std;

int main()
{
  double r[] = {1.2, 3.3, 3.4, 2.1};
  int i;
  
  for(i = 0; i < 4; i++){
    cout << i << " " << r[i] << endl;
  }

  // how about accessing non-existent index?
  for(i = 0; i < 5; i++){
    cout << i << " " << r[i] << endl;
  }

  return 0;
}

