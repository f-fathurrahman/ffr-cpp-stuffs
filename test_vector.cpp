#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<double> v;
  // insert data
  v.push_back(5.6);
  v.push_back(3.1);
  v.push_back(3.2);
  v.push_back(4.3);
  v.push_back(0.1);

  // access the element via an iterator
  vector<double>::iterator i;

  cout << "Content of v (unsorted)" << endl;
  for( i = v.begin(); i != v.end(); i++ ) {
    cout << *i << endl; // iterator's pointer hold the value
  }

  // sort the vector
  sort( v.begin(), v.end() );

  cout << "Content of v (sorted)" << endl;
  for( i = v.begin(); i != v.end(); i++ ) {
    cout << *i << endl;
  }

  return 0;
}

