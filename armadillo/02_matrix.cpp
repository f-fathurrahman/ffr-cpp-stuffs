#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main( int argc, char** argv )
{
    mat A(3,4);

    cout << "A.n_rows: " << A.n_rows << endl;
    cout << "A.n_cols: " << A.n_cols << endl;

    // Indexing starts at 0

    // access an element
    A(1,2) = 111;

    cout << "Using cout: " << endl;
    cout << A << endl;

    A.print("A: ");

    // scalars are treated as 1x1 matrix
    A = 77.0; 
    cout << "A.n_rows = " << A.n_rows << endl;
    cout << "A.n_cols = " << A.n_cols << endl;
    A.print("A: ");

    // Change the size (data is not preserved)
    A.set_size(4,5);
    cout << "A.n_rows = " << A.n_rows << endl;
    cout << "A.n_cols = " << A.n_cols << endl;
    A.print("A: ");

    // Set all elements for a particular value
    A.fill(5.0);
    A.print("A: ");

    // Using endr
    // endr indicates "end of row"
    A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
      << 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
      << 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
      << 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
      << 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;    
    A.print("A: ");

    // Calculate determinant
    cout << "det(A) = " << det(A) << endl;

    // Inverse
    cout << "inv(A) = " << endl;
    cout << inv(A) << endl;

    return 0;
}