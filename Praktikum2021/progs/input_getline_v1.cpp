#include <iostream>
#include <string>

using namespace std;

int main()
{
    string inputStr;

    cout << "Masukkan bilangan bulat" << endl;

    getline(cin, inputStr);

    int inputInt = stoi(inputStr);
    cout << "inputInt = " << inputInt << endl;

    return 0;
}