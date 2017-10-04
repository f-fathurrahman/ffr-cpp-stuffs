#include <iostream>
#include <string>

using namespace std;

class Stock
{

private:
  string company;
  long shares;
  double share_val;
  double total_val;
  // this will automatically become inline function
  void set_tot()
  {
    total_val = shares*share_val;
  }

public:
  void acquire( const string &co, long n, double pr );
  void buy( long num, double price );
  void sell( long num, double price );
  void update( double price );
  void show();
  

};


//
// implementation of `Stock`'s member functions
//


void Stock::acquire( const string &co, long n, double pr )
{
  company = co;
  if( n < 0 ) {
    cout << "Number of shares can't be negative; "
              << company << " shares set to 0.\n";
  }
  else {
    shares = n;
  }
  share_val = pr;
  set_tot();
}


void Stock::buy( long num, double price )
{
  if( num < 0 ) {
    cout << "Number of shares purchased can't be negative."
         << "Transaction is aborted.\n";
  }
  else {
    shares = shares + num;
    share_val = price;
    set_tot();
  }
}


void Stock::sell( long num, double price )
{
  if( num < 0 ) {
    cout << "Number of shares sold can't be negative."
         << "Transaction is aborted\n";
  }
  else if( num > shares ) {
    cout << "You can't sell more than you have"
         << "Transaction is aborted.\n";
  }
  else {
    shares = shares - num;
    share_val = price;
    set_tot();
  }
}


void Stock::update( double price )
{
  share_val = price;
  set_tot();
}

void Stock::show()
{
  cout << "Company: " << company << endl
       << "  Shares: " << shares << endl
       << "  Share Price: $" << share_val << endl
       << "  Total worth: $" << total_val << endl;
}


//
// Main function to test `Stock`
//

int main()
{
  Stock ffr;

  ffr.acquire("FFR, Inc.", 100, 63);
  ffr.show();

  ffr.sell( 10, 80.0 );
  ffr.show();

  return 0;
}


