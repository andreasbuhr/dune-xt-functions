// This file is part of the dune-xt-functions project:
//   https://github.com/dune-community/dune-xt-functions
// Copyright 2009-2017 dune-xt-functions developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2017)

#include <dune/xt/common/test/main.hxx>

#include <dune/grid/common/rangegenerators.hh>

#include <dune/xt/grid/grids.hh>
#include <dune/xt/grid/gridprovider/cube.hh>
#include <dune/xt/functions/expression/parametric.hh>
#include <dune/xt/functions/interfaces.hh>

#include "functions.hh"

using namespace Dune;
using namespace Dune::XT;


struct ExpressionFunctionTest : public FunctionTest<TESTFUNCTIONTYPE>
{
  void check() const
  {
    auto grid = XT::Grid::make_cube_grid<GRIDTYPE>();
    auto leaf_view = grid.leaf_view();

    TESTFUNCTIONTYPE func("x", std::make_pair("_t", 1), {"x[0]+_t"});
    for (auto&& entity : elements(leaf_view)) {
      auto local_function = func.local_function(entity);
      auto xx_global = entity.geometry().center();
      auto xx = entity.geometry().local(xx_global);
      ASSERT_EQ(xx_global[0] + 1., local_function->evaluate(xx, /*_t=*/1.0)[0]);
    }
  }
};


TEST_F(ExpressionFunctionTest, creation_and_evalution)
{
  this->check();
}
