#include "config.h"

#if HAVE_DUNE_PYBINDXI

#include <string>
#include <vector>

#include <dune/pybindxi/pybind11.h>
//#include <dune/pybindxi/stl_bind.h> // <- see dune/xt/common/bindings.cc

#include <dune/xt/common/configuration.pbh>
#include <dune/xt/common/fvector.pbh>

#include <dune/xt/grid/grids.hh>

#include "interfaces.pbh"
#include "constant.pbh"
#include "checkerboard.pbh"
#include "expression.pbh"
#include "spe10.pbh"

namespace py = pybind11;
using namespace pybind11::literals;


PYBIND11_PLUGIN(functions)
{
  py::module m("functions", "dune-xt-functions");

  py::module::import("common");
  py::module::import("grid");

  typedef Dune::ALUGrid<2, 2, Dune::simplex, Dune::conforming> G;
  const std::string grid_id = "2d_simplex_aluconform";

  auto i_1_1 = Dune::XT::Functions::bind_LocalizableFunctionInterface<G, 1, 1>(m, grid_id);
  auto i_2_1 = Dune::XT::Functions::bind_LocalizableFunctionInterface<G, 2, 1>(m, grid_id);
  auto i_3_1 = Dune::XT::Functions::bind_LocalizableFunctionInterface<G, 3, 1>(m, grid_id);
  auto i_4_1 = Dune::XT::Functions::bind_LocalizableFunctionInterface<G, 4, 1>(m, grid_id);

  auto i_2_2 = Dune::XT::Functions::bind_LocalizableFunctionInterface<G, 2, 2>(m, grid_id);

  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::difference, 1, 1, 1, 1>(m,
                                                                                                               grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::difference,
                                                       1,
                                                       1,
                                                       1,
                                                       1>(i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::difference, 2, 1, 2, 1>(m,
                                                                                                               grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::difference,
                                                       2,
                                                       1,
                                                       2,
                                                       1>(i_2_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::difference, 3, 1, 3, 1>(m,
                                                                                                               grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::difference,
                                                       3,
                                                       1,
                                                       3,
                                                       1>(i_3_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::difference, 4, 1, 4, 1>(m,
                                                                                                               grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::difference,
                                                       4,
                                                       1,
                                                       4,
                                                       1>(i_4_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::difference, 2, 2, 2, 2>(m,
                                                                                                               grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::difference,
                                                       2,
                                                       2,
                                                       2,
                                                       2>(i_2_2);


  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::sum, 1, 1, 1, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G, Dune::XT::Functions::internal::Combination::sum, 1, 1, 1, 1>(
          i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::sum, 2, 1, 2, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G, Dune::XT::Functions::internal::Combination::sum, 2, 1, 2, 1>(
          i_2_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::sum, 3, 1, 3, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G, Dune::XT::Functions::internal::Combination::sum, 3, 1, 3, 1>(
          i_3_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::sum, 4, 1, 4, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G, Dune::XT::Functions::internal::Combination::sum, 4, 1, 4, 1>(
          i_4_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::sum, 2, 2, 2, 2>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G, Dune::XT::Functions::internal::Combination::sum, 2, 2, 2, 2>(
          i_2_2);

  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::product, 1, 1, 1, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::product,
                                                       1,
                                                       1,
                                                       1,
                                                       1>(i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::product, 1, 1, 2, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::product,
                                                       1,
                                                       1,
                                                       2,
                                                       1>(i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::product, 1, 1, 3, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::product,
                                                       1,
                                                       1,
                                                       3,
                                                       1>(i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::product, 1, 1, 4, 1>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::product,
                                                       1,
                                                       1,
                                                       4,
                                                       1>(i_1_1);
  Dune::XT::Functions::
      bind_combined_LocalizableFunction<G, Dune::XT::Functions::internal::Combination::product, 1, 1, 2, 2>(m, grid_id);
  Dune::XT::Functions::
      addbind_LocalizableFunctionInterface_combined_op<G,
                                                       Dune::XT::Functions::internal::Combination::product,
                                                       1,
                                                       1,
                                                       2,
                                                       2>(i_1_1);

  Dune::XT::Functions::bind_ConstantFunction<G, 1, 1>(m, grid_id);
  Dune::XT::Functions::bind_ConstantFunction<G, 2, 1>(m, grid_id);
  Dune::XT::Functions::bind_ConstantFunction<G, 3, 1>(m, grid_id);
  Dune::XT::Functions::bind_ConstantFunction<G, 4, 1>(m, grid_id);
  Dune::XT::Functions::bind_ConstantFunction<G, 2, 2>(m, grid_id);

  Dune::XT::Functions::bind_CheckerboardFunction<G, 1, 1>(m, grid_id);
  //  Dune::XT::Functions::bind_CheckerboardFunction<G, 2, 1>(m, grid_id);
  //  Dune::XT::Functions::bind_CheckerboardFunction<G, 3, 1>(m, grid_id);
  //  Dune::XT::Functions::bind_CheckerboardFunction<G, 4, 1>(m, grid_id);

  Dune::XT::Functions::bind_ExpressionFunction<G, 1, 1>(m, grid_id);
  Dune::XT::Functions::bind_ExpressionFunction<G, 2, 1>(m, grid_id);
  Dune::XT::Functions::bind_ExpressionFunction<G, 3, 1>(m, grid_id);
  Dune::XT::Functions::bind_ExpressionFunction<G, 4, 1>(m, grid_id);

  Dune::XT::Functions::bind_Spe10Model1Function<G, 1, 1>(m, grid_id);

  return m.ptr();
}


#endif // HAVE_DUNE_PYBINDXI
