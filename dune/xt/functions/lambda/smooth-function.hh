// This file is part of the dune-xt-functions project:
//   https://github.com/dune-community/dune-xt-functions
// Copyright 2009-2018 dune-xt-functions developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2013 - 2017)
//   Rene Milk       (2013 - 2016, 2018)
//   Sven Kaulmann   (2013)
//   Tobias Leibner  (2014, 2017)

#ifndef DUNE_XT_FUNCTIONS_LAMBDA_SMOOTH_FUNCTION_HH
#define DUNE_XT_FUNCTIONS_LAMBDA_SMOOTH_FUNCTION_HH

#include <functional>

#include <dune/xt/common/memory.hh>

#include <dune/xt/functions/interfaces/smooth-function.hh>

namespace Dune {
namespace XT {
namespace Functions {


/**
 * Smooth function you can pass lambda expressions to that gets evaluated.
 *
 * \example LambdaType lambda(1, [](const auto& x, const auto& mu = {}) { return x;});
 */
template <size_t domainDim, size_t rangeDim = 1, size_t rangeDimCols = 1, class RangeFieldImp = double>
class SmoothLambdaFunction : public SmoothFunctionInterface<domainDim, rangeDim, rangeDimCols, RangeFieldImp>
{
  using BaseType = SmoothFunctionInterface<domainDim, rangeDim, rangeDimCols, RangeFieldImp>;

public:
  using BaseType::d;
  using typename BaseType::DomainType;
  using typename BaseType::RangeType;
  using typename BaseType::DerivativeRangeType;

  using OrderLambdaType = std::function<int(const Common::Parameter&)>;
  using EvaluateLambdaType = std::function<RangeType(const DomainType&, const Common::Parameter&)>;
  using JacobianLambdaType = std::function<DerivativeRangeType(const DomainType&, const Common::Parameter&)>;
  using DerivativeLambdaType =
      std::function<DerivativeRangeType(const std::array<size_t, d>&, const DomainType&, const Common::Parameter&)>;

  SmoothLambdaFunction(OrderLambdaType order_lambda,
                       EvaluateLambdaType evaluate_lambda = default_evaluate_lambda(),
                       const std::string nm = "smooth_lambda_function",
                       const Common::ParameterType& param_type = {},
                       JacobianLambdaType jacobian_lambda = default_jacobian_lambda(),
                       DerivativeLambdaType derivative_lambda = default_derivative_lambda())
    : order_lambda_(order_lambda)
    , evaluate_lambda_(evaluate_lambda)
    , jacobian_lambda_(jacobian_lambda)
    , derivative_lambda_(derivative_lambda)
    , parameter_type_(param_type)
    , name_(nm)
  {
  }

  SmoothLambdaFunction(int ord,
                       EvaluateLambdaType evaluate_lambda = default_evaluate_lambda(),
                       const std::string nm = "smooth_lambda_function",
                       const Common::ParameterType& param_type = {},
                       JacobianLambdaType jacobian_lambda = default_jacobian_lambda(),
                       DerivativeLambdaType derivative_lambda = default_derivative_lambda())
    : order_lambda_([=](const auto& /*param*/) { return ord; })
    , evaluate_lambda_(evaluate_lambda)
    , jacobian_lambda_(jacobian_lambda)
    , derivative_lambda_(derivative_lambda)
    , parameter_type_(param_type)
    , name_(nm)
  {
  }

  /**
   * \name ´´These methods are required by XT::Common::ParametricInterface.''
   * \{
   */

  bool is_parametric() const override final
  {
    return !parameter_type_.empty();
  }

  const Common::ParameterType& parameter_type() const override final
  {
    return parameter_type_;
  }

  /**
   * \}
   * \name ´´These methods are required by SmoothFunctionInterface.''
   * \{
   */

  int order(const Common::Parameter& mu = {}) const override final
  {
    return order_lambda_(this->parse_and_check(mu));
  }

  RangeType evaluate(const DomainType& xx, const Common::Parameter& mu = {}) const override final
  {
    return evaluate_lambda_(xx, this->parse_and_check(mu));
  }

  DerivativeRangeType jacobian(const DomainType& xx, const Common::Parameter& mu = {}) const override final
  {
    return jacobian_lambda_(xx, this->parse_and_check(mu));
  }

  virtual DerivativeRangeType derivative(const std::array<size_t, d>& alpha,
                                         const DomainType& xx,
                                         const Common::Parameter& mu = {}) const override final
  {
    return derivative_lambda_(alpha, xx, this->parse_and_check(mu));
  }

  std::string type() const override final
  {
    return "smooth_lambda_function";
  }

  std::string name() const override final
  {
    return name_;
  }

  /**
   * \}
   * \name ´´These methods may be used to provide defaults on construction.''
   * \{
   */

  static EvaluateLambdaType default_evaluate_lambda()
  {
    return [](const DomainType& /*xx*/, const Common::Parameter& /*mu*/ = {}) {
      DUNE_THROW(NotImplemented,
                 "This SmoothLambdaFunction does not provide evaluations, provide an evaluate_lambda on construction!");
      return RangeType();
    };
  }

  static JacobianLambdaType default_jacobian_lambda()
  {
    return [](const DomainType& /*xx*/, const Common::Parameter& /*mu*/ = {}) {
      DUNE_THROW(NotImplemented,
                 "This SmoothLambdaFunction does not provide jacobian evaluations, provide a "
                 "jacobian_lambda on construction!");
      return DerivativeRangeType();
    };
  }

  static DerivativeLambdaType default_derivative_lambda()
  {
    return [](const std::array<size_t, d>& /*alpha*/, const DomainType& /*xx*/, const Common::Parameter& /*mu*/ = {}) {
      DUNE_THROW(NotImplemented,
                 "This SmoothLambdaFunction does not provide derivative evaluations, provide a "
                 "derivative_lambda on construction!");
      return DerivativeRangeType();
    };
  }

  /**
   * \}
   */

  const OrderLambdaType order_lambda_;
  const EvaluateLambdaType evaluate_lambda_;
  const JacobianLambdaType jacobian_lambda_;
  const DerivativeLambdaType derivative_lambda_;
  const Common::ParameterType parameter_type_;
  const std::string name_;
}; // class SmoothLambdaFunction


} // namespace Functions
} // namespace XT
} // namespace Dune

#endif // DUNE_XT_FUNCTIONS_LAMBDA_SMOOTH_FUNCTION_HH
