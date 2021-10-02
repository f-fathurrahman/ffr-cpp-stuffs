#include <iostream>

using namespace std;

#define HELLO_WORLD "Hello Dunia"

int main()
{

#ifdef HELLO_WORLD
    cout << "Dipanggil untuk pertama kalinya" << endl;
    cout << HELLO_WORLD << endl;
#endif

#undef HELLO_WORLD

#ifdef HELLO_WORLD
    cout << "Dipanggil untuk kedua kalinya" << endl;
    cout << HELLO_WORLD << endl;
#endif

}
