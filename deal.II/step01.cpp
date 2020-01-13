// Fundamental class: the Triangulation class
#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>

// Some function to generate standard grids
#include <deal.II/grid/grid_generator.h>

// output of grids in various graphics formats
#include <deal.II/grid/grid_out.h>

#include <iostream>
#include <fstream>
#include <cmath>

using namespace dealii;

void create_first_grid()
{
    // Ab object for a triangulation of a 2d domain
    Triangulation<2> triangulation;

    // Fill the triangulation with a single cell for a square domain.
    // The triangulation is the refined four times, to yield $4^4=256$
    // cells in total
    GridGenerator::hyper_cube(triangulation);
    triangulation.refine_global(4);

    // Write a graphical representation of the mesh to an output file.
    std::ofstream out("IMG_grid-1.eps");
    GridOut grid_out;
    grid_out.write_eps(triangulation, out);
    std::cout << "Grid written to IMG_grid-1.eps" << std::endl;

    return;
}

int main()
{
    create_first_grid();

    return 0;
}