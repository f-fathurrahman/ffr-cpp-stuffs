#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>

// Needed for output of grids in various graphics formats
#include <deal.II/grid/grid_out.h>

#include <deal.II/dofs/dof_handler.h>

#include <deal.II/fe/fe_q.h>
#include <deal.II/dofs/dof_tools.h>

#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
#include <deal.II/dofs/dof_renumbering.h>

#include <fstream>

using namespace dealii;


void make_grid(Triangulation<2> &triangulation)
{
  const Point<2> center(1.0, 0.0);
  const double inner_radius = 0.5, outer_radius = 1.0;

  unsigned int Ncells = 5;
  GridGenerator::hyper_shell(triangulation, center, inner_radius, outer_radius, Ncells);
  
  for(unsigned int step = 0; step < 3; ++step)
  {
    for(auto &cell: triangulation.active_cell_iterators())
    {
      for(unsigned int v = 0; v < GeometryInfo<2>::vertices_per_cell; ++v)
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
  std::ofstream out("IMG_grid_1.svg");
  GridOut grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid is written to IMG_grid_1.svg" << std::endl;

  std::ofstream out2("IMG_grid_1.eps");
  GridOut grid_out2;
  grid_out2.write_eps(triangulation, out2);
  std::cout << "Grid is written to IMG_grid_1.eps" << std::endl;

}

void distribute_dofs(DoFHandler<2> &dof_handler)
{
  const FE_Q<2> finite_element(2); // quadratic shape function
  dof_handler.distribute_dofs(finite_element);
  DynamicSparsityPattern dynamic_sparsity_pattern(
    dof_handler.n_dofs(), dof_handler.n_dofs());
  DoFTools::make_sparsity_pattern(dof_handler, dynamic_sparsity_pattern);
  SparsityPattern sparsity_pattern;
  sparsity_pattern.copy_from(dynamic_sparsity_pattern);

  std::ofstream out("IMG_sparsity_pattern.svg");
  sparsity_pattern.print_svg(out);
}

void renumber_dofs(DoFHandler<2> &dof_handler)
{
  DoFRenumbering::Cuthill_McKee(dof_handler);
  DynamicSparsityPattern dynamic_sparsity_pattern(
    dof_handler.n_dofs(), dof_handler.n_dofs());
  DoFTools::make_sparsity_pattern(dof_handler, dynamic_sparsity_pattern);
  SparsityPattern sparsity_pattern;
  sparsity_pattern.copy_from(dynamic_sparsity_pattern);

  std::ofstream out("IMG_sparsity_pattern2.svg");
  sparsity_pattern.print_svg(out);
}

int main()
{
  Triangulation<2> triangulation;
  make_grid(triangulation);

  DoFHandler<2> dof_handler(triangulation);
  distribute_dofs(dof_handler);
  renumber_dofs(dof_handler);
}
