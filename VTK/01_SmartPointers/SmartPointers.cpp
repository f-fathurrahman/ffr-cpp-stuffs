#include <cstdio>
#include <vtkFloatArray.h>
#include <vtkSmartPointer.h>
 
void WithSmartPointers();
void WithoutSmartPointers();
 
int main(int argc, char *argv[])
{
  WithSmartPointers();
  WithoutSmartPointers();
 
  printf("This is before the end\n");

  return 0;
}
 
void WithSmartPointers()
{
  vtkSmartPointer<vtkFloatArray> Distances = vtkSmartPointer<vtkFloatArray>::New();
}
 
void WithoutSmartPointers()
{
  vtkFloatArray* Distances = vtkFloatArray::New();
  Distances->Delete();
}
