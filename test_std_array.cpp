#include <array>
#include <iostream>

using namespace std;

int main()
{
  const int N = 5;
  array<int,N> a = {7, 3, 4};

  for( int i=0; i<N; i++ ) {
    cout << i << " " << a[i] << endl;
  }

  cout << a.data() << endl;

  return 0;
}

