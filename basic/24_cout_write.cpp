// Test the following function:
//     basic_ostream& write( const char_type* s, std::streamsize count )
//

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  const char *city1 = "Pekanbaru";
  const char *city2 = "Bandung";
  const char *city3 = "Osaka";
  const char *city4 = "Jakarta";

// We will use only city3, other arrays are there just to provide data
// before and after the city3 array so that you can see what happens when the program
// miscodes access to city3

  cout << "length of city1: " << strlen(city1) << endl;
  cout << "length of city2: " << strlen(city2) << endl;
  cout << "length of city3: " << strlen(city3) << endl;
  cout << "length of city4: " << strlen(city4) << endl;

  int len = strlen(city3);

  int i;
  cout << "Increasing loop index:\n";
  for(i = 1; i<=len; i++) {
    cout << i << ": ";
    cout.write(city3,i);
    cout << endl;
  }

  // concatenate output
  cout << "Decreasing loop index:\n";
  for (i = len; i > 0; i--) {
    cout << i << ": ";
    // !!! We also can write it like this:
    cout.write(city3,i) << endl;
  }
  
  // exceed string length
  cout << "Exceeding string length:\n";
  cout.write(city3, len + 5) << endl;

  cout << "Minus string length:\n";
  cout.write(city3, len - 5) << endl;

// Note that the write() method doesn’t stop printing characters automatically
// when it reaches the null character. It simply prints how many characters you tell it to, even
// if that goes beyond the bounds of a particular string! In this case, the program brackets the
// string "Osaka" with two other strings so that adjacent memory locations would contain
// data.

  return 0;
}


