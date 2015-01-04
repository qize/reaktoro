// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// Reaktor includes
#include <Reaktor/Common/Matrix.hpp>
#include <Reaktor/Optimization/Hessian.hpp>

namespace Reaktor {

/// A type that describes the state of an optimum solution
struct OptimumState
{
    /// The primal solution of the optimisation problem
    Vector x;

    /// The dual solution of the optimisation problem with respect to the equality constraints
    Vector y;

    /// The dual solution of the optimisation problem with respect to the bound constraints
    Vector z;

    /// The value of the objective function evaluated at the primal solution `x`
    double f;

    /// The gradient of the objective function evaluated at the primal solution `x`
    Vector g;

    /// The Hessian of the objective function evaluated at the primal solution `x`
    Hessian H;

    /// The value of the equality constraint function evaluated at the primal solution `x`
    Vector h;

    /// The gradient of the equality constraint function evaluated at the primal solution `x`
    Matrix A;
};

} // namespace Reaktor
