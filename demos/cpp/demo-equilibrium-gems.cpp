// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2015 Allan Leal
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

#include <Reaktoro/Reaktoro.hpp>
using namespace Reaktoro;

/// **Note:**
/// This demo should be executed from the root directory of the binaries produced after compilation.
/// Example:
/// ~~~
/// cmake .
/// make -j
/// ./bin/demo-equilibrium-gems
/// ~~~
int main()
{
    // Use an exported project file from GEMS to initialize a Gems object,
    Gems gems("demos/resources/gems/CalciteBC-dat.lst");

    // and then use it to construct the ChemicalSystem object.
    ChemicalSystem system = gems;

    // Create a ChemicalState object that contains the temperature, pressure,
    // and amounts of species stored in the exported GEMS file.
    EquilibriumState state = gems.state(system);

    // Change the temperature of the chemical state,
    state.setTemperature(50, "celsius");

    // and then equilibrate the modified chemical state using Reaktoro's methods.
    equilibrate(state);

    // Output the updated equilibrium state to a file.
    state.output("state.txt");
}
