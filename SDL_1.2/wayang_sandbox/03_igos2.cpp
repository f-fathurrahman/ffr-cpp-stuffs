#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <cfloat>
#include <climits>

#include "sprig/sprig.h"
#include "wayang/wayang.h"

void data_types()
{
  printf("%-14s %4s %20s %20s\n", "type", "size", "min", "max");
  printf("%-16s %2d %20d %20d\n", "char", sizeof(char), CHAR_MIN, CHAR_MAX);
  printf("%-16s %2d %20d %20d\n", "short", sizeof(short), SHRT_MIN, SHRT_MAX);
  printf("%-16s %2d %20d %20d\n", "int", sizeof(int), INT_MIN, INT_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned char", sizeof(unsigned char), 0, UCHAR_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned short", sizeof(unsigned short), 0, USHRT_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned int", sizeof(unsigned int), 0, UINT_MAX);
  printf("%-16s %2d %20e %20e\n", "float", sizeof(float), FLT_MIN, FLT_MAX);
  printf("%-16s %2d %20le %20le\n", "double", sizeof(double), DBL_MIN, DBL_MAX);
  printf("%-16s %2d %20lle %20lle\n", "long double", sizeof(long double), LDBL_MIN, LDBL_MAX);
}

int main()
{
  data_types();
  return 0;
}
