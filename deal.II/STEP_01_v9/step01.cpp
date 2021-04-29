// Needed for Triangulation class
#include <deal.II/grid/tria.h>

// Need for loop over cells and/or faces
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>

// Needed for some functions to generate standard grids
#include <deal.II/grid/grid_generator.h>

// Needed for output of grids in various graphics formats
#include <deal.II/grid/grid_out.h>

#include <iostream>
#include <fstream>
#include <cmath>

using namespace dealii;

void create_first_grid()
{
  // Triangulation for two-dimensional domain
  Triangulation<2> triangulation;

  GridGenerator::hyper_cube(triangulation);
  triangulation.refine_global(2);

  std::ofstream out("IMG_grid_1.svg");
  GridOut grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid is written to IMG_grid_1.svg" << std::endl;
}

int main()
{
  create_first_grid();
}
