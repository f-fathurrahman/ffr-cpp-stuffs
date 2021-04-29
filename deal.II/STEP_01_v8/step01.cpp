// Fundamental class: the Triangulation class
#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>

// Some function to generate standard grids
#include <deal.II/grid/grid_generator.h>

#include <deal.II/grid/manifold_lib.h>

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
    int Nrefine = 1;
    GridGenerator::hyper_cube(triangulation);
    triangulation.refine_global(Nrefine);

    // Write a graphical representation of the mesh to an output file.
    std::ofstream out("IMG_grid-1.eps");
    GridOut grid_out;
    grid_out.write_eps(triangulation, out);
    std::cout << "Grid written to IMG_grid-1.eps" << std::endl;

    return;
}


void create_second_grid()
{
    Triangulation<2> triangulation;

    const Point<2> center(1, 0);
    const double inner_radius = 0.5, outer_radius = 1.0;

    GridGenerator::hyper_shell(triangulation, center, inner_radius, outer_radius, 10);
    
    const SphericalManifold<2> manifold_description(center);
    triangulation.set_manifold(0, manifold_description);
    triangulation.set_all_manifold_ids(0);

    for(unsigned int step = 0; step < 5; step++)
    {
        Triangulation<2>::active_cell_iterator cell = triangulation.begin_active();
        Triangulation<2>::active_cell_iterator endc = triangulation.end();
        for(; cell != endc; cell++)
        {
            for(unsigned int v = 0; v < GeometryInfo<2>::vertices_per_cell; v++)
            {
                const double distance_from_center = center.distance(cell->vertex(v));
                if(std::fabs(distance_from_center - inner_radius) < 1e-10)
                {
                    cell->set_refine_flag();
                    break;
                }
            }
        }
        triangulation.execute_coarsening_and_refinement();
    }

    std::ofstream out("IMG_grid-2.eps");
    GridOut grid_out;
    grid_out.write_eps(triangulation, out);

    std::cout << "Grid written to IMG_grid-2.eps" << std::endl;

}


int main()
{
    create_first_grid();
    create_second_grid();

    return 0;
}