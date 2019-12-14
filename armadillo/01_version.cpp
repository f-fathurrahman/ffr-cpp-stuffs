#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main( int argc, char** argv )
{
    cout << "Armadillo version: " << arma_version::as_string() << endl;

    return 0;
}