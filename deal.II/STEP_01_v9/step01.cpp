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
  int Nrefine = 2;
  triangulation.refine_global(Nrefine);

  std::ofstream out("IMG_grid_1.svg");
  GridOut grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid is written to IMG_grid_1.svg" << std::endl;
}



void create_second_grid()
{
  Triangulation<2> triangulation;

  // We then fill it with a ring domain. The center of the ring shall be the point (1,0),
  // and inner and outer radius shall be 0.5 and 1. The number of circumferential cells
  // could be adjusted automatically by this function, but we choose to set it explicitly
  // to 10 as the last argument:
  const Point<2> center(1,0);
  const double inner_radius = 0.5, outer_radius = 1.0;
  int Ncells = 10;
  GridGenerator::hyper_shell(
    triangulation, center, inner_radius, outer_radius, Ncells
  );

  int Nrefine = 0;
  triangulation.refine_global(Nrefine);
  //
  std::ofstream out("IMG_grid_2.svg");
  GridOut grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid is written to IMG_grid_2.svg" << std::endl;

}


void create_third_grid()
{
  Triangulation<2> triangulation;

  const Point<2> center(1,0);
  const double inner_radius = 0.5, outer_radius = 1.0;
  int Ncells = 10;
  GridGenerator::hyper_shell(
    triangulation, center, inner_radius, outer_radius, Ncells
  );


  for(unsigned int step=0; step < 5; ++step)
  {
    for(auto &cell: triangulation.active_cell_iterators())
    {
      for(unsigned int v = 0; v < GeometryInfo<2>::vertices_per_cell; ++v)
      {
        const double distance_from_center = center.distance(cell->vertex(v));
        if (std::fabs(distance_from_center - inner_radius) < 1e-10)
        {
          cell->set_refine_flag();
          break;
        }
      }
    }
    triangulation.execute_coarsening_and_refinement();
  }

  std::ofstream out("IMG_grid_3.svg");
  GridOut grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid is written to IMG_grid_3.svg" << std::endl;

}

int main()
{
  create_first_grid();
  create_second_grid();
  create_third_grid();
}
